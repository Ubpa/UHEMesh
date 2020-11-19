#pragma once

#include "Empty.h"

#include "detail/random_set.h"
#include <UContainer/Pool.h>

namespace Ubpa {
	// nullptr Polygon is a boundary
	template<typename Traits = HEMeshTriats_EmptyVEPH>
	class HEMesh {
		static_assert(Traits::IsValid());

	public:
		using V = HEMeshTriats_V<Traits>;
		using E = HEMeshTriats_E<Traits>;
		using P = HEMeshTriats_P<Traits>;
		using H = HEMeshTriats_H<Traits>;

	public:
		HEMesh() = default;
		HEMesh(const std::vector<std::vector<size_t>>& polygons) { Init(polygons); }
		HEMesh(const std::vector<size_t>& polygons, size_t sides) { Init(polygons, sides); }

	public:
		const std::vector<V*>& Vertices() noexcept { return vertices.vec(); }
		const std::vector<E*>& Edges() noexcept { return edges.vec(); }
		const std::vector<P*>& Polygons() noexcept { return polygons.vec(); }
		const std::vector<H*>& HalfEdges() noexcept { return halfEdges.vec(); }
		/*
		* ordered boundary == std::vector<H*>
		* boundaries == std::vector<ordered boundary>
		* there maybe several boundaries in a mesh
		*/
		std::vector<std::vector<H*>> Boundaries();

		size_t NumVertices() const noexcept { return vertices.size(); }
		size_t NumEdges() const noexcept { return edges.size(); }
		size_t NumPolygons() const noexcept { return polygons.size(); }
		size_t NumHalfEdges() const noexcept { return halfEdges.size(); }
		size_t NumBoundaries() const noexcept { return const_cast<HEMesh*>(this)->Boundaries().size(); }

		// index is useless after changing the topology
		size_t Index(V* v) const { return vertices.idx(v); }
		size_t Index(E* e) const { return edges.idx(e); }
		size_t Index(P* p) const { return polygons.idx(p); }
		std::vector<size_t> Indices(P* p) const;

		bool IsValid() const;
		bool IsTriMesh() const;
		// vertices empty => halfedges, edges and polygons empty
		bool IsEmpty() const noexcept { return vertices.empty(); }
		bool HaveIsolatedVertices() const noexcept;
		bool HaveBoundary() const noexcept;

		// min is 0
		bool Init(const std::vector<std::vector<size_t>>& polygons);
		bool Init(const std::vector<size_t>& polygons, size_t sides);
		void Clear() noexcept;
		void Reserve(size_t n);
		std::vector<std::vector<size_t>> Export() const;

		// -----------------
		//  basic mesh edit
		// -----------------

		template<typename... Args>
		V* AddVertex(Args&&... args) { return New<V>(std::forward<Args>(args)...); }
		// e's halfedge is form v0 to v1
		template<typename... Args>
		E* AddEdge(V* v0, V* v1, Args&&... args);
		// polygon's halfedge is heLoop[0]
		template<typename... Args>
		P* AddPolygon(const std::vector<H*>& heLoop, Args&&... args);
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
		template<typename... Args>
		V* AddEdgeVertex(E* e, Args&&... args);

		// connect he0.origin and he1.origin in he0/he1.polygon
		// [require] he0.polygon == he1.polygon, he0.origin != he1.origin
		// [return] edge with halfedge form he0.origin to he1.origin
		template<typename... Args>
		E* ConnectVertex(H* he0, H* he1, Args&&... args);

		// counter-clock, remain e in container, won't break iteration
		bool FlipEdge(E* e);

		// delete e
		template<typename... Args>
		V* SplitEdge(E* e, Args&&... args);

		bool IsCollapsable(E* e) const;
		// won't collapse in unsafe situation, return nullptr
		template<typename... Args>
		V* CollapseEdge(E* e, Args&&... args);

	private:
		template<typename T> struct MemVarOf;
		template<typename T>
		friend struct MemVarOf;
		// new and insert
		template<typename T, typename... Args>
		T* New(Args&&... args);

		// clear and erase
		template<typename T>
		void Delete(T* elem);

	private:
		random_set<H*> halfEdges;
		random_set<V*> vertices;
		random_set<E*> edges;
		random_set<P*> polygons;

		Pool<H> poolHE;
		Pool<V> poolV;
		Pool<E> poolE;
		Pool<P> poolP;

		// =============================

		template<>
		struct MemVarOf<H> {
			static auto& pool(HEMesh* mesh) { return mesh->poolHE; }
			static auto& set(HEMesh* mesh) { return mesh->halfEdges; }
		};
		template<>
		struct MemVarOf<V> {
			static auto& pool(HEMesh* mesh) { return mesh->poolV; }
			static auto& set(HEMesh* mesh) { return mesh->vertices; }
		};
		template<>
		struct MemVarOf<E> {
			static auto& pool(HEMesh* mesh) { return mesh->poolE; }
			static auto& set(HEMesh* mesh) { return mesh->edges; }
		};
		template<>
		struct MemVarOf<P> {
			static auto& pool(HEMesh* mesh) { return mesh->poolP; }
			static auto& set(HEMesh* mesh) { return mesh->polygons; }
		};
	};
}

#include "detail/HEMesh.inl"
