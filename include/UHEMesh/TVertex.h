#pragma once

#include "detail/ForwardDecl.h"

namespace Ubpa {
	template<typename Traits>
	class TVertex {
	public:
		using V = HEMeshTriats_V<Traits>;
		using E = HEMeshTriats_E<Traits>;
		using P = HEMeshTriats_P<Traits>;
		using H = HEMeshTriats_H<Traits>;

	public:
		H* const HalfEdge() noexcept { return halfEdge; }
		const H* const HalfEdge() const noexcept { return const_cast<TVertex*>(this)->HalfEdge(); }

		void SetHalfEdge(H* he) noexcept { halfEdge = he; }

		// halfedge == nullptr
		bool IsIsolated() const noexcept { return !halfEdge; }

		// vertex is boundary == any adjacent polygon is boundary (nullptr)
		bool IsBoundary() const noexcept;

		// number of adjacent edges
		size_t Degree() const noexcept;

		// outward halfedges : [he, he.RotateNext(), he.RotateNext().RotateNext(), ..., he)
		const std::vector<H*> OutHalfEdges()
		{ return IsIsolated() ? std::vector<H*>() : HalfEdge()->RotateNextLoop(); }

		// adjacent edges : { halfedge.Edge() for halfedge in OutHalfEdges() }
		const std::vector<E*> AdjEdges();

		// adjacent vertices : { halfedge.End() for halfedge in OutHalfEdges() }
		const std::vector<V*> AdjVertices();

		// adjacent polygons : { halfedge.End() for halfedge in OutHalfEdges() }
		// if IsBoundary(), result contains nullptr
		// use P::IsBoundary() to find it
		const std::set<P*> AdjPolygons();

		// find halfedge (this -> end)
		// nullptr if no exist
		H* const HalfEdgeTo(V* end) noexcept;
		const H* const HalfEdgeTo(const V* end) const noexcept
		{ return const_cast<TVertex*>(this)->HalfEdgeTo(const_cast<V*>(end)); }

		// find halfedge (origin -> end)
		// nullptr if no exist
		static H* const HalfEdgeAlong(V* origin, V* end) noexcept { return origin->HalfEdgeTo(end); }
		static const H* const HalfEdgeAlong(const V* origin, const V* end) noexcept
		{ return HalfEdgeAlong(const_cast<V*>(origin), const_cast<V*>(end)); }

		// find edge (this -> v)
		// nullptr if no exist
		E* const EdgeWith(V* v) noexcept;
		const E* const EdgeWith(const V* v) const noexcept { return const_cast<TVertex*>(this)->EdgeWith(const_cast<V*>(v)); }

		// find edge (v0 <-> v1)
		// nullptr if no exist
		static E* const EdgeBetween(V* v0, V* v1) noexcept { return v0->EdgeWith(v1); }
		static const E* const EdgeBetween(const V* v0, const V* v1) noexcept
		{ return EdgeBetween(const_cast<V*>(v0), const_cast<V*>(v1)); }

		// true if exist edge (this <-> v1)
		bool IsConnectedWith(const V* v) const noexcept { return EdgeWith(v); }
		// true if exist edge (v0 <-> v1)
		static bool IsConnected(const V* v0, const V* v1) noexcept { return v0->IsConnectedWith(v1); }

	private:
		friend HEMesh<Traits>;
		H* const FindFreeIncident() noexcept;

		H* halfEdge{ nullptr };
	};
}

#include "detail/TVertex.inl"
