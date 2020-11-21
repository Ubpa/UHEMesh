#pragma once

namespace Ubpa {
	template<typename Traits>
	std::vector<HEMeshTraits_H<Traits>*> TEdge<Traits>::AdjOutHalfEdges() {
		std::vector<H*> hes;
		auto he01 = HalfEdge(); // v0 => v1
		for (auto he = he01->RotateNext(); he != he01; he = he->RotateNext())
			hes.push_back(he);
		for (auto he = he01->Next(); he != he01->Pair(); he = he->RotateNext())
			hes.push_back(he);
		return hes;
	}

	template<typename Traits>
	std::set<HEMeshTraits_V<Traits>*> TEdge<Traits>::AdjVertices() {
		std::set<V*> vertices;
		for (auto he : AdjOutHalfEdges())
			vertices.insert(he->End());
		return vertices;
	}

	template<typename Traits>
	std::vector<HEMeshTraits_E<Traits>*> TEdge<Traits>::AdjEdges() {
		std::vector<E*> edges;
		for (auto he : AdjOutHalfEdges())
			edges.push_back(he->Edge());
		return edges;
	}
}
