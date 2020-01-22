#pragma once
#ifndef _UBPA_HEMESH_TVERTEX_INL_
#define _UBPA_HEMESH_TVERTEX_INL_

namespace Ubpa {
	template<typename V, typename E, typename P>
	bool TVertex<V, E, P>::IsBoundary() const {
		if (IsIsolated())
			return true;

		auto begin = HalfEdge();
		auto he = begin;
		do {
			if (he->IsBoundary())
				return true;
			he = he->RotateNext();
		} while (he != begin);

		return false;
	}

	template<typename V, typename E, typename P>
	const std::vector<E*> TVertex<V, E, P>::AdjEdges() {
		std::vector<E*> edges;
		for (auto he : OutHEs())
			edges.push_back(he->Edge());
		return edges;
	}

	template<typename V, typename E, typename P>
	const std::vector<V*> TVertex<V, E, P>::AdjVertices() {
		std::vector<V*> adjVs;
		for (auto he : OutHEs())
			adjVs.push_back(he->End());
		return adjVs;
	}

	template<typename V, typename E, typename P>
	THalfEdge<V,E,P>* const TVertex<V, E, P>::FindFreeIncident() {
		if (IsIsolated())
			return nullptr;

		auto begin = HalfEdge()->Pair();
		auto he = begin;
		do {
			if (he->IsFree())
				return he;
			he = he->Next()->Pair();
		} while (he != begin);

		return nullptr;
	}

	template<typename V, typename E, typename P>
	THalfEdge<V, E, P>* const TVertex<V, E, P>::HalfEdgeTo(V* end) {
		if (IsIsolated())
			return nullptr;

		auto begin = HalfEdge();
		auto he = begin;
		do {
			if (he->End() == end)
				return he;
			he = he->RotateNext();
		} while (he != begin);

		return nullptr;
	}

	template<typename V, typename E, typename P>
	E* const TVertex<V, E, P>::EdgeWith(V* v) {
		auto he = HalfEdgeTo(v);
		if (!he)
			return nullptr;

		return he->Edge();
	}
}

#endif// !_UBPA_HEMESH_TVERTEX_INL_
