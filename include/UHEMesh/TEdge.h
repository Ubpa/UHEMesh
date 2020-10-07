#pragma once

#include "detail/ForwardDecl.h"

namespace Ubpa {
	template<typename Traits>
	class TEdge {
	public:
		using V = HEMeshTriats_V<Traits>;
		using E = HEMeshTriats_E<Traits>;
		using P = HEMeshTriats_P<Traits>;
		using H = HEMeshTriats_H<Traits>;

	public:
		H* const HalfEdge() { return halfEdge; }
		const H* const HalfEdge() const { return const_cast<TEdge*>(this)->HalfEdge(); }

		void SetHalfEdge(H* he) { halfEdge = he; }

		bool IsBoundary() const { return HalfEdge()->IsBoundary() || HalfEdge()->Pair()->IsBoundary(); }
		bool IsFree() const { return HalfEdge()->IsFree() && HalfEdge()->Pair()->IsFree(); }

		// clockwise
		// + [he.RotateNext, he.RotateNext.RotateNext, ..., he)
		// + [he.next, he.next.RotateNext, ..., he.pair)
		const std::vector<H*> AdjOutHalfEdges();

		const std::set<V*> AdjVertices();

		const std::vector<E*> AdjEdges();

	private:
		friend class HEMesh<Traits>;

		H* halfEdge{ nullptr };
	};
}

#include "detail/TEdge.inl"
