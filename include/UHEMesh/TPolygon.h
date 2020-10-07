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
		using H = HEMeshTriats_H<Traits>;

	public:
		H* const HalfEdge() { return halfEdge; }
		const H* const HalfEdge() const { return const_cast<TPolygon*>(this)->HalfEdge(); }

		void SetHalfEdge(H* he) { halfEdge = he; }

		static bool IsBoundary(const P* p) { return p == nullptr; }
		size_t Degree() const { return static_cast<int>(const_cast<TPolygon*>(this)->AdjHalfEdges().size()); }

		const std::vector<H*> AdjHalfEdges() { return HalfEdge()->NextLoop(); }
		const std::vector<const H*> AdjHalfEdges() const { return Const(const_cast<TPolygon*>(this)->AdjHalfEdges()); }

		const std::vector<E*> AdjEdges();
		const std::vector<const E*> AdjEdges() const { return Const(const_cast<TPolygon*>(this)->AdjEdges()); }

		const std::vector<V*> AdjVertices();
		const std::vector<const V*> AdjVertices() const { return Const(const_cast<TPolygon*>(this)->AdjVertices()); }

		const std::vector<P*> AdjPolygons();
		const std::vector<const V*> AdjPolygons() const { return Const(const_cast<TPolygon*>(this)->AdjPolygons()); }

	private:
		H* halfEdge = nullptr;
	};

}

#include "detail/TPolygon.inl"
