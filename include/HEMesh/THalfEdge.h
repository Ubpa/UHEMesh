#pragma once
#ifndef _UBPA_HEMESH_THALFEDGE_H_
#define _UBPA_HEMESH_THALFEDGE_H_

#include "ForwardDecl.h"

namespace Ubpa {
	template<typename V, typename E, typename P>
	class THalfEdge {
	private:
		// internal use
		using HE = THalfEdge<V, E, P>;

	public:
		HE* const Next() { return next; }
		HE* const Pair() { return pair; }
		V* const Origin() { return origin; }
		E* const Edge() { return edge; }
		P* const Polygon() { return polygon; }
		V* const End() { return Pair()->Origin(); }
		HE* const Pre();
		HE* const RotateNext() { return Pair()->Next(); }
		HE* const RotatePre() { return Pre()->Pair(); }

		const HE* const Next() const { return const_cast<HE*>(this)->Next(); }
		const HE* const Pair() const { return const_cast<HE*>(this)->Pair(); }
		const V* const Origin() const { return const_cast<HE*>(this)->Origin(); }
		const E* const Edge() const { return const_cast<HE*>(this)->Edge(); }
		const P* const Polygon() const { return const_cast<HE*>(this)->Polygon(); }
		const V* const End() const { return const_cast<HE*>(this)->End(); }
		const HE* const Pre() const { return const_cast<HE*>(this)->Pre(); }
		const HE* const RotateNext() const { return const_cast<HE*>(this)->RotateNext(); }
		const HE* const RotatePre() const { return const_cast<HE*>(this)->RotatePre(); }

		void SetNext(HE* he) { next = he; }
		void SetPair(HE* he) { pair = he; }
		void SetOrigin(V* v) { origin = v; }
		void SetEdge(E* e) { edge = e; }
		void SetPolygon(P* p) { polygon = p; }
		void Init(HE* next, HE* pair, V* v, E* e, P* p);

		bool IsFree() const { return !polygon; }
		bool IsBoundary() const { return !polygon; }

		static HE* const FindFreeIncident(HE* begin, HE* end);

		static bool MakeAdjacent(HE* inHE, HE* outHE);

		// [begin, end), if begin == end, return a loop
		static const std::vector<HE*> NextBetween(HE* begin, HE* end);
		// [begin, end), if begin == end, return a loop
		static const std::vector<HE*> RotateNextBetween(HE* begin, HE* end);
		// [this, end), NextBetween(this, end);
		const std::vector<HE*> NextTo(HE* end) { return NextBetween(this, end); }
		// [this, end), RotateNextBetween(this, end);
		const std::vector<HE*> RotateNextTo(HE* end) { return RotateNextBetween(this, end); }
		// NextBetween(this, this), a loop from this to this
		const std::vector<HE*> NextLoop() { return NextBetween(this, this); }
		// RotateNextBetween(this, this), a loop from this to this
		const std::vector<HE*> RotateNextLoop() { return RotateNextBetween(this, this); }

	private:
		HE* next = nullptr;
		HE* pair = nullptr;

		V* origin = nullptr;
		E* edge = nullptr;
		P* polygon = nullptr;
	};
}

#include "THalfEdge.inl"

#endif // !_UBPA_HEMESH_THALFEDGE_H_
