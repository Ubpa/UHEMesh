#pragma once 

namespace Ubpa {
	template<typename Traits>
	class THalfEdge;
	template<typename Traits>
	class TVertex;
	template<typename Traits>
	class TEdge;
	template<typename Traits>
	class TPolygon;

	template<typename Traits>
	class HEMesh;

	template<typename V_, typename E_, typename P_>
	struct HEMeshTriats {
		using V = V_;
		using E = E_;
		using P = P_;
		using HE = THalfEdge<HEMeshTriats>;
		using Mesh = HEMesh<HEMeshTriats>;
	};

	template<typename Traits>
	using HEMeshTriats_V = typename Traits::V;

	template<typename Traits>
	using HEMeshTriats_E = typename Traits::E;

	template<typename Traits>
	using HEMeshTriats_P = typename Traits::P;

	template<typename Traits>
	using HEMeshTriats_HE = typename Traits::HE;

	template<typename Traits>
	using HEMeshTriats_Mesh = typename Traits::Mesh;
}
