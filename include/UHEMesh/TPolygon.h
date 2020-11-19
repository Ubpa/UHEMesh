#pragma once

#include "detail/ForwardDecl.h"

namespace Ubpa {
	template<typename Traits>
	class TPolygon {
	public:
		using V = HEMeshTraits_V<Traits>;
		using E = HEMeshTraits_E<Traits>;
		using P = HEMeshTraits_P<Traits>;
		using H = HEMeshTraits_H<Traits>;

	public:
		H* HalfEdge() noexcept { return halfEdge; }
		const H* HalfEdge() const noexcept { return const_cast<TPolygon*>(this)->HalfEdge(); }

		void SetHalfEdge(H* he) noexcept { halfEdge = he; }

		// p == nullptr
		static bool IsBoundary(const P* p) noexcept { return p == nullptr; }

		// number of edges/vertices
		size_t Degree() const noexcept;

		// halfedges : [ he, he.Next(), he.Next().Next(), ..., he)
		std::vector<H*> AdjHalfEdges() { return HalfEdge()->NextLoop(); }

		// edges : { halfedge.Edge() for halfedge in AdjHalfEdges() }
		std::vector<E*> AdjEdges();

		// vertices : { halfedge.Origin() for halfedge in AdjHalfEdges() }
		std::vector<V*> AdjVertices();

		// adjacent polygons : { halfedge.Pair().Polygon() for halfedge in AdjHalfEdges() }
		// maybe contains boundary polygon (nullptr)
		// use IsBoundary() to find it
		std::vector<P*> AdjPolygons();

	private:
		friend HEMesh<Traits>;

		H* halfEdge{ nullptr };
	};

}

#include "detail/TPolygon.inl"
