#pragma once

namespace Ubpa {
	template<typename Traits>
	const std::vector<HEMeshTriats_E<Traits>*> TPolygon<Traits>::BoundaryEdges() {
		std::vector<E*> edges;
		for (auto he : BoundaryHEs())
			edges.push_back(he->Edge());
		return edges;
	}

	template<typename Traits>
	const std::vector<HEMeshTriats_V<Traits>*> TPolygon<Traits>::BoundaryVertice() {
		std::vector<V*> vertices;
		for (auto he : BoundaryHEs())
			vertices.push_back(he->Origin());
		return vertices;
	}
}
