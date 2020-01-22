#pragma once
#ifndef _UBPA_HEMESH_TPOLYGON_H_
#define _UBPA_HEMESH_TPOLYGON_H_

#include "ForwardDecl.h"

namespace Ubpa {
	template<typename V, typename E, typename P>
	class TPolygon {
	private:
		// internal use
		using HE = THalfEdge<V, E, P>;

	public:
		HE* const HalfEdge() { return halfEdge; }
		const HE* const HalfEdge() const { return const_cast<TPolygon*>(this)->HalfEdge(); }

		void SetHalfEdge(HE* he) { halfEdge = he; }

		static bool IsBoundary(P* p) { return p == nullptr; }
		size_t Degree() const { return static_cast<int>(const_cast<TPolygon*>(this)->BoundaryHEs().size()); }

		const std::vector<HE*> BoundaryHEs() { return HalfEdge()->NextLoop(); }
		const std::vector<E*> BoundaryEdges();
		const std::vector<V*> BoundaryVertice();

	private:
		HE* halfEdge = nullptr;
	};

}

#include "TPolygon.inl"

#endif // !_UBPA_HEMESH_TPOLYGON_H_
