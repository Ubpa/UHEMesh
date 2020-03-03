#pragma once
#ifndef _UBPA_HEMESH_HEMESH_H_
#define _UBPA_HEMESH_HEMESH_H_

#include "THalfEdge.h"
#include "TVertex.h"
#include "TEdge.h"
#include "TPolygon.h"

#include "detail/random_set.h"
#include "detail/pool.h"

#include <set>
#include <string>
#include <algorithm>
#include <iterator>
#include <unordered_map>

#include <assert.h>

namespace Ubpa {
	template <typename E, typename P>
	class EmptyV : public TVertex<EmptyV<E, P>, E, P> {};
	template <typename V, typename E>
	class EmptyP : public TPolygon<V, E, EmptyP<V, E>> {};
	template <typename V, typename P>
	class EmptyE : public TEdge<V, EmptyE<V, P>, P> {};

	template <typename V>
	class EmptyEP_E : public TEdge<V, EmptyEP_E<V>, EmptyEP_P<V>> {};
	template <typename V>
	class EmptyEP_P : public TPolygon<V, EmptyEP_E<V>, EmptyEP_P<V>> {};

	class AllEmpty : public TVertex<AllEmpty, EmptyEP_E<AllEmpty>, EmptyEP_P<AllEmpty>> {};

	template<typename V>
	class _enable_HEMesh {
	private:
		using E = typename V::_E;
		using P = typename V::_P;
	public:
		template<typename = std::enable_if_t<std::is_base_of_v<TVertex<V, E, P>, V>>,
			typename = std::enable_if_t<std::is_base_of_v<TEdge<V, E, P>, E>>,
			typename = std::enable_if_t<std::is_base_of_v<TPolygon<V, E, P>, P>> >
			class type {};
	};
	template<typename V>
	using _enable_HEMesh_t = typename _enable_HEMesh<V>::template type<>;

	// nullptr Polygon is a boundary
	template<typename _V = AllEmpty>
	class HEMesh : private _enable_HEMesh_t<_V> {
	public:
		using V = _V;
		using E = typename V::_E;
		using P = typename V::_P;
		using HE = THalfEdge<V, E, P>;

	public:
		HEMesh() = default;
		HEMesh(const std::vector<std::vector<size_t>>& polygons) { Init(polygons); }
		HEMesh(const std::vector<size_t>& polygons, size_t sides) { Init(polygons, sides); }

	public:
		const std::vector<V*>& Vertices() { return vertices.vec(); }
		const std::vector<HE*>& HalfEdges() { return halfEdges.vec(); }
		const std::vector<E*>& Edges() { return edges.vec(); }
		const std::vector<P*>& Polygons() { return polygons.vec(); }
		const std::vector<std::vector<HE*>> Boundaries();

		size_t NumVertices() const { return vertices.size(); }
		size_t NumEdges() const { return edges.size(); }
		size_t NumPolygons() const { return polygons.size(); }
		size_t NumHalfEdges() const { return halfEdges.size(); }
		size_t NumBoundaries() const { return const_cast<HEMesh*>(this)->Boundaries().size(); }

		size_t Index(V* v) const { return vertices.idx(v); }
		size_t Index(E* e) const { return edges.idx(e); }
		size_t Index(P* p) const { return polygons.idx(p); }
		const std::vector<size_t> Indices(P* p) const;

		bool IsValid() const;
		bool IsTriMesh() const;
		// vertices empty => halfedges, edges and polygons empty
		bool IsEmpty() const { return vertices.empty(); }
		bool HaveIsolatedVertices() const;
		bool HaveBoundary() const;

		// min is 0
		bool Init(const std::vector<std::vector<size_t>>& polygons);
		bool Init(const std::vector<size_t>& polygons, size_t sides);
		void Clear();
		void Reserve(size_t n);
		const std::vector<std::vector<size_t>> Export() const;

		// -----------------
		//  basic mesh edit
		// -----------------

		template<typename ...Args>
		V* const AddVertex(Args&& ... args) { return New<V>(std::forward<Args>(args)...); }
		// e's halfedge is form v0 to v1
		template<typename ...Args>
		E* const AddEdge(V* v0, V* v1, Args&& ... args);
		// polygon's halfedge is heLoop[0]
		template<typename ...Args>
		P* const AddPolygon(const std::vector<HE*> heLoop, Args&& ... args);
		void RemovePolygon(P* polygon);
		void RemoveEdge(E* e);
		void RemoveVertex(V* v);

		// ----------------------
		//  high-level mesh edit
		// ----------------------

		// RemoveVertex and AddPolygon
		const P* EraseVertex(V* v);

		// edge's halfedge : v0=>v1
		// nweV's halfedge : newV => v1
		template<typename ...Args>
		V* const AddEdgeVertex(E* e, Args&& ... args);

		// connect he0.origin and he1.origin in he0/he1.polygon
		// [require] he0.polygon == he1.polygon, he0.origin != he1.origin
		// [return] edge with halfedge form he0.origin to he1.origin
		template<typename ...Args>
		E* const ConnectVertex(HE* he0, HE* he1, Args&& ... args);

		// counter-clock, remain e in container, won't break iteration
		bool FlipEdge(E* e);

		// delete e
		template<typename ...Args>
		V* const SpiltEdge(E* e, Args&& ... args);

		// won't collapse in unsafe situation, return nullptr
		template<typename ...Args>
		V* const CollapseEdge(E* e, Args&& ... args);

	private:
		// new and insert
		template<typename T, typename ... Args>
		T * const New(Args&& ... args) {
			T* elem = traits<T>::pool(this).request();
			new (elem) T(std::forward<Args>(args)...);
			traits<T>::set(this).insert(elem);
			return elem;
		}

		// clear and erase
		template<typename T>
		void Delete(T * elem) {
			traits<T>::pool(this).recycle(elem);
			traits<T>::set(this).erase(elem);
		}

	private:
		random_set<HE*> halfEdges;
		random_set<V*> vertices;
		random_set<E*> edges;
		random_set<P*> polygons;

		pool<HE> poolHE;
		pool<V> poolV;
		pool<E> poolE;
		pool<P> poolP;

		// ------------------------------

		template<typename T>
		struct traits;
		template<typename T>
		friend struct traits;
		template<>
		struct traits<HE> {
			static auto& pool(HEMesh* mesh) { return mesh->poolHE; }
			static auto& set(HEMesh* mesh) { return mesh->halfEdges; }
		};
		template<>
		struct traits<V> {
			static auto& pool(HEMesh* mesh) { return mesh->poolV; }
			static auto& set(HEMesh* mesh) { return mesh->vertices; }
		};
		template<>
		struct traits<E> {
			static auto& pool(HEMesh* mesh) { return mesh->poolE; }
			static auto& set(HEMesh* mesh) { return mesh->edges; }
		};
		template<>
		struct traits<P> {
			static auto& pool(HEMesh* mesh) { return mesh->poolP; }
			static auto& set(HEMesh* mesh) { return mesh->polygons; }
		};
	};
}

#include "detail/HEMesh.inl"

#endif // !_UBPA_HEMESH_HEMESH_H_
