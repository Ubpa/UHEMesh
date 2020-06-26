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

	template<typename V_, typename E_, typename P_, typename H_>
	struct HEMeshTriats {
		using V = V_;
		using E = E_;
		using P = P_;
		using H = H_;
		using Mesh = HEMesh<HEMeshTriats>;

		static constexpr bool IsValid() noexcept {
			return std::is_base_of_v<TVertex<HEMeshTriats>, V>
				&& std::is_base_of_v<TEdge<HEMeshTriats>, E>
				&& std::is_base_of_v<TPolygon<HEMeshTriats>, P>
				&& std::is_base_of_v<THalfEdge<HEMeshTriats>, H>;
		}
	};

	template<typename Traits>
	using HEMeshTriats_V = typename Traits::V;

	template<typename Traits>
	using HEMeshTriats_E = typename Traits::E;

	template<typename Traits>
	using HEMeshTriats_P = typename Traits::P;

	template<typename Traits>
	using HEMeshTriats_H = typename Traits::H;

	template<typename Traits>
	using HEMeshTriats_Mesh = typename Traits::Mesh;
}
