#pragma once

#include "detail/ForwardDecl.h"

namespace Ubpa {
	template<typename Traits>
	class TVertex {
		friend class HEMesh<Traits>;
	public:
		using V = HEMeshTriats_V<Traits>;
		using E = HEMeshTriats_E<Traits>;
		using P = HEMeshTriats_P<Traits>;
		using HE = HEMeshTriats_HE<Traits>;

	public:
		HE* const HalfEdge() { return halfEdge; }
		const HE* const HalfEdge() const { return const_cast<TVertex*>(this)->HalfEdge(); }

		void SetHalfEdge(HE* he) { halfEdge = he; }

		bool IsIsolated() const { return !halfEdge; }
		bool IsBoundary() const;
		size_t Degree() const { return OutHEs().size(); }

		const std::vector<HE*> OutHEs() { return IsIsolated() ? std::vector<HE*>() : HalfEdge()->RotateNextLoop(); }
		const std::vector<const HE*> OutHEs() const { return Const(const_cast<TVertex*>(this)->OutHEs()); }

		const std::vector<E*> AdjEdges();
		const std::vector<const HE*> AdjEdges() const { return Const(const_cast<TVertex*>(this)->AdjEdges()); }

		const std::vector<V*> AdjVertices();
		const std::vector<const V*> AdjVertices() const { return Const(const_cast<TVertex*>(this)->AdjVertices()); }

		const std::set<P*> AdjPolygons();
		const std::set<const P*> AdjPolygons() const { return Const(const_cast<TVertex*>(this)->AdjPolygons()); }

		HE* const FindFreeIncident();
		const HE* const FindFreeIncident() const { return const_cast<TVertex*>(this)->FindFreeOutHE(); }

		HE* const HalfEdgeTo(V* end);
		const HE* const HalfEdgeTo(const V* end) const { return const_cast<TVertex*>(this)->HalfEdgeTo(const_cast<V*>(end)); }

		static HE* const HalfEdgeAlong(V* origin, V* end) { return origin->HalfEdgeTo(end); }
		static const HE* const HalfEdgeAlong(const V* origin, const V* end) { return HalfEdgeAlong(const_cast<V*>(origin), const_cast<V*>(end)); }

		E* const EdgeWith(V* v);
		const E* const EdgeWith(const V* v) const { return const_cast<TVertex*>(this)->EdgeWith(const_cast<V*>(v)); }

		static E* const EdgeBetween(V* v0, V* v1) { return v0->EdgeWith(v1); }
		static const E* const EdgeBetween(const V* v0, const V* v1) { return EdgeBetween(const_cast<V*>(v0), const_cast<V*>(v1)); }

		bool IsConnectedWith(const V* v) const { return EdgeWith(v); }
		static bool IsConnected(const V* v0, const V* v1) { return v0->IsConnectedWith(v1); }

	private:
		HE* halfEdge = nullptr;
	};
}

#include "detail/TVertex.inl"
