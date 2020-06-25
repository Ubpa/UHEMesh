#pragma once

#include "detail/ForwardDecl.h"

namespace Ubpa {
	template<typename Traits>
	class TPolygon {
		friend class HEMesh<Traits>;
	public:
		using V = HEMeshTriats_V<Traits>;
		using E = HEMeshTriats_E<Traits>;
		using P = HEMeshTriats_P<Traits>;
		using HE = HEMeshTriats_HE<Traits>;

	public:
		HE* const HalfEdge() { return halfEdge; }
		const HE* const HalfEdge() const { return const_cast<TPolygon*>(this)->HalfEdge(); }

		void SetHalfEdge(HE* he) { halfEdge = he; }

		static bool IsBoundary(const P* p) { return p == nullptr; }
		size_t Degree() const { return static_cast<int>(const_cast<TPolygon*>(this)->BoundaryHEs().size()); }

		const std::vector<HE*> BoundaryHEs() { return HalfEdge()->NextLoop(); }
		const std::vector<const HE*> BoundaryHEs() const { return Const(const_cast<TPolygon*>(this)->BoundaryHEs()); }

		const std::vector<E*> BoundaryEdges();
		const std::vector<const E*> BoundaryEdges() const { return Const(const_cast<TPolygon*>(this)->BoundaryEdges()); }

		const std::vector<V*> BoundaryVertice();
		const std::vector<const V*> BoundaryVertice() const { return Const(const_cast<TPolygon*>(this)->BoundaryVertice()); }

	private:
		HE* halfEdge = nullptr;
	};

}

#include "detail/TPolygon.inl"
