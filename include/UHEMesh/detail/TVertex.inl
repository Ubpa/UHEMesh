#pragma once

namespace Ubpa {
	template<typename Traits>
	bool TVertex<Traits>::IsBoundary() const {
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

	template<typename Traits>
	const std::vector<HEMeshTriats_E<Traits>*> TVertex<Traits>::AdjEdges() {
		std::vector<E*> edges;
		for (auto he : OutHalfEdges())
			edges.push_back(he->Edge());
		return edges;
	}

	template<typename Traits>
	const std::vector<HEMeshTriats_V<Traits>*> TVertex<Traits>::AdjVertices() {
		std::vector<V*> adjVs;
		for (auto he : OutHalfEdges())
			adjVs.push_back(he->End());
		return adjVs;
	}

	template<typename Traits>
	const std::set<HEMeshTriats_P<Traits>*> TVertex<Traits>::AdjPolygons() {
		std::set<P*> adjPs;
		for (auto he : OutHalfEdges())
			adjPs.insert(he->Polygon());
		return adjPs;
	}

	template<typename Traits>
	HEMeshTriats_H<Traits>* const TVertex<Traits>::FindFreeIncident() {
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

	template<typename Traits>
	HEMeshTriats_H<Traits>* const TVertex<Traits>::HalfEdgeTo(V* end) {
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

	template<typename Traits>
	HEMeshTriats_E<Traits>* const TVertex<Traits>::EdgeWith(V* v) {
		auto he = HalfEdgeTo(v);
		if (!he)
			return nullptr;

		return he->Edge();
	}
}
