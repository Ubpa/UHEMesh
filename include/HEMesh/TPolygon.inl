#pragma once
#ifndef _UBPA_HEMESH_TPOLYGON_INL_
#define _UBPA_HEMESH_TPOLYGON_INL_

namespace Ubpa {
	template<typename V, typename E, typename P>
	const std::vector<HEMesh_ptr<E, HEMesh<V>>> TPolygon<V, E, P>::BoundaryEdges() {
		std::vector<ptr<E>> edges;
		for (auto he : BoundaryHEs())
			edges.push_back(he->Edge());
		return edges;
	}

	template<typename V, typename E, typename P>
	const std::vector<HEMesh_ptr<V, HEMesh<V>>> TPolygon<V, E, P>::BoundaryVertice() {
		std::vector<ptr<V>> vertices;
		for (auto he : BoundaryHEs())
			vertices.push_back(he->Origin());
		return vertices;
	}
}

#endif// !_UBPA_HEMESH_TPOLYGON_INL_
