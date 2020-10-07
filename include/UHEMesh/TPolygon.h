#pragma once

#include "detail/ForwardDecl.h"

namespace Ubpa {
	template<typename Traits>
	class TPolygon {
	public:
		using V = HEMeshTriats_V<Traits>;
		using E = HEMeshTriats_E<Traits>;
		using P = HEMeshTriats_P<Traits>;
		using H = HEMeshTriats_H<Traits>;

	public:
		H* const HalfEdge() noexcept { return halfEdge; }
		const H* const HalfEdge() const noexcept { return const_cast<TPolygon*>(this)->HalfEdge(); }

		void SetHalfEdge(H* he) noexcept { halfEdge = he; }

		static bool IsBoundary(const P* p) noexcept { return p == nullptr; }
		size_t Degree() const noexcept;

		const std::vector<H*> AdjHalfEdges() { return HalfEdge()->NextLoop(); }

		const std::vector<E*> AdjEdges();

		const std::vector<V*> AdjVertices();

		const std::vector<P*> AdjPolygons();

	private:
		friend HEMesh<Traits>;

		H* halfEdge{ nullptr };
	};

}

#include "detail/TPolygon.inl"
