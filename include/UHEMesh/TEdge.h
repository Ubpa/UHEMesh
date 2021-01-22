#pragma once

#include "detail/ForwardDecl.h"

namespace Ubpa {
	template<typename Traits>
	class TEdge {
	public:
		using V = HEMeshTraits_V<Traits>;
		using E = HEMeshTraits_E<Traits>;
		using P = HEMeshTraits_P<Traits>;
		using H = HEMeshTraits_H<Traits>;

	public:
		H* HalfEdge() noexcept { return halfEdge; }
		const H* HalfEdge() const noexcept { return const_cast<TEdge*>(this)->HalfEdge(); }

		void SetHalfEdge(H* he) noexcept { halfEdge = he; }

		// edge is on boundary == any halfedge is on boundary
		bool IsOnBoundary() const noexcept { return HalfEdge()->IsOnBoundary() || HalfEdge()->Pair()->IsOnBoundary(); }

		// clockwise
		// + [he.RotateNext, he.RotateNext.RotateNext, ..., he)
		// + [he.pair, he.pair.RotateNext, ..., he.pair)
		std::vector<H*> AdjOutHalfEdges();

		// { halfedge.End() for halfedge in OutHalfEdges() }
		std::set<V*> AdjVertices();

		// { halfedge.Edge() for halfedge in OutHalfEdges() }
		std::vector<E*> AdjEdges();

	private:
		friend HEMesh<Traits>;
		bool IsFree() const noexcept { return HalfEdge()->IsFree() && HalfEdge()->Pair()->IsFree(); }

		H* halfEdge{ nullptr };
	};
}

#include "detail/TEdge.inl"
