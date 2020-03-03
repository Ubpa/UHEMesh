#pragma once
#ifndef _UBPA_HEMESH_TEDGE_INL_
#define _UBPA_HEMESH_TEDGE_INL_

namespace Ubpa {
	template<typename V, typename E, typename P>
	const std::vector<THalfEdge<V, E, P>*> TEdge<V, E, P>::OutHEs() {
		std::vector<THalfEdge<V, E, P>*> hes;
		auto he01 = HalfEdge(); // v0 => v1
		for (auto he = he01->RotateNext(); he != he01; he = he->RotateNext())
			hes.push_back(he);
		for (auto he = he01->Next(); he != he01->Pair(); he = he->RotateNext())
			hes.push_back(he);
		return hes;
	}

	template<typename V, typename E, typename P>
	const std::set<V*> TEdge<V, E, P>::AdjVertices() {
		std::set<V*> vertices;
		for (auto e : OutHEs())
			vertices.insert(e->End());
		return vertices;
	}

	template<typename V, typename E, typename P>
	const std::vector<E*> TEdge<V, E, P>::AdjEdges() {
		std::vector<E*> edges;
		for (auto he : OutHEs())
			edges.push_back(he->Edge());
		return edges;
	}
}

#endif // !_UBPA_HEMESH_TEDGE_INL_
