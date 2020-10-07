#pragma once

#include "detail/ForwardDecl.h"

namespace Ubpa {
	template<typename Traits>
	class TVertex {
	public:
		using V = HEMeshTriats_V<Traits>;
		using E = HEMeshTriats_E<Traits>;
		using P = HEMeshTriats_P<Traits>;
		using H = HEMeshTriats_H<Traits>;

	public:
		H* const HalfEdge() { return halfEdge; }
		const H* const HalfEdge() const { return const_cast<TVertex*>(this)->HalfEdge(); }

		void SetHalfEdge(H* he) { halfEdge = he; }

		bool IsIsolated() const { return !halfEdge; }
		bool IsBoundary() const;
		size_t Degree() const { return const_cast<TVertex*>(this)->OutHalfEdges().size(); }

		const std::vector<H*> OutHalfEdges() { return IsIsolated() ? std::vector<H*>() : HalfEdge()->RotateNextLoop(); }

		const std::vector<E*> AdjEdges();

		const std::vector<V*> AdjVertices();

		const std::set<P*> AdjPolygons();

		H* const HalfEdgeTo(V* end);
		const H* const HalfEdgeTo(const V* end) const { return const_cast<TVertex*>(this)->HalfEdgeTo(const_cast<V*>(end)); }

		static H* const HalfEdgeAlong(V* origin, V* end) { return origin->HalfEdgeTo(end); }
		static const H* const HalfEdgeAlong(const V* origin, const V* end) { return HalfEdgeAlong(const_cast<V*>(origin), const_cast<V*>(end)); }

		E* const EdgeWith(V* v);
		const E* const EdgeWith(const V* v) const { return const_cast<TVertex*>(this)->EdgeWith(const_cast<V*>(v)); }

		static E* const EdgeBetween(V* v0, V* v1) { return v0->EdgeWith(v1); }
		static const E* const EdgeBetween(const V* v0, const V* v1) { return EdgeBetween(const_cast<V*>(v0), const_cast<V*>(v1)); }

		bool IsConnectedWith(const V* v) const { return EdgeWith(v); }
		static bool IsConnected(const V* v0, const V* v1) { return v0->IsConnectedWith(v1); }

	private:
		friend class HEMesh<Traits>;
		H* const FindFreeIncident();

		H* halfEdge{ nullptr };
	};
}

#include "detail/TVertex.inl"
