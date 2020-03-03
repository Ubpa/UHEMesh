#pragma once
#ifndef _UBPA_HEMESH_TEDGE_H_
#define _UBPA_HEMESH_TEDGE_H_

#include "ForwardDecl.h"

namespace Ubpa {
	template<typename V, typename E, typename P = EmptyP<V, E>>
	class TEdge {
	private:
		// internal use
		using HE = THalfEdge<V, E, P>;

	public:
		HE* const HalfEdge() { return halfEdge; }
		const HE* const HalfEdge() const { return const_cast<TEdge*>(this)->HalfEdge(); }

		void SetHalfEdge(HE* he) { halfEdge = he; }

		bool IsBoundary() const { return HalfEdge()->IsBoundary() || HalfEdge()->Pair()->IsBoundary(); }
		bool IsFree() const { return HalfEdge()->IsFree() && HalfEdge()->Pair()->IsFree(); }

		// clockwise
		// + [he.RotateNext, he.RotateNext.RotateNext, ..., he)
		// + [he.next, he.next.RotateNext, ..., he.pair)
		const std::vector<HE*> OutHEs();
		const std::vector<const HE*> AdjOutHEs() const { return Const(const_cast<TEdge*>(this)->AdjOutHEs()); }

		const std::set<V*> AdjVertices();
		const std::set<const V*> AdjVertices() const { return Const(const_cast<TEdge*>(this)->AdjVertices()); }

		const std::vector<E*> AdjEdges();
		const std::vector<const E*> AdjEdges() const { return Const(const_cast<TEdge*>(this)->AdjEdges()); }

	private:
		HE* halfEdge = nullptr;
	};
}

#include "TEdge.inl"

#endif // !_UBPA_HEMESH_TEDGE_H_
