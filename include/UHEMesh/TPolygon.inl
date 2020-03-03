#pragma once
#ifndef _UBPA_HEMESH_TPOLYGON_INL_
#define _UBPA_HEMESH_TPOLYGON_INL_

namespace Ubpa {
	template<typename V, typename E, typename P>
	const std::vector<E*> TPolygon<V, E, P>::BoundaryEdges() {
		std::vector<E*> edges;
		for (auto he : BoundaryHEs())
			edges.push_back(he->Edge());
		return edges;
	}

	template<typename V, typename E, typename P>
	const std::vector<V*> TPolygon<V, E, P>::BoundaryVertice() {
		std::vector<V*> vertices;
		for (auto he : BoundaryHEs())
			vertices.push_back(he->Origin());
		return vertices;
	}
}

#endif// !_UBPA_HEMESH_TPOLYGON_INL_
