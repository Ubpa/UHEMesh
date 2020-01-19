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
		template<typename T>
		using ptr = HEMesh_ptr<T, HEMesh<V>>;
		template<typename T>
		using ptrc = ptr<const T>;

	public:
		// external use
		using Ptr = ptr<HE>;
		using PtrC = ptrc<HE>;

	public:
		const ptr<HE> Next() { return ptr<HE>(next, mesh); }
		const ptr<HE> Pair() { return ptr<HE>(pair, mesh); }
		const ptr<V> Origin() { return ptr<V>(origin, mesh); }
		const ptr<E> Edge() { return ptr<E>(edge, mesh); }
		const ptr<P> Polygon() { return ptr<P>(polygon, mesh); }
		const ptr<V> End() { return Pair()->Origin(); }
		const ptr<HE> Pre();
		const ptr<HE> RotateNext() { return Pair()->Next(); }
		const ptr<HE> RotatePre() { return Pre()->Pair(); }

		const ptrc<HE> Next() const { return const_cast<HE*>(this)->Next(); }
		const ptrc<HE> Pair() const { return const_cast<HE*>(this)->Pair(); }
		const ptrc<V> Origin() const { return const_cast<HE*>(this)->Origin(); }
		const ptrc<E> Edge() const { return const_cast<HE*>(this)->Edge(); }
		const ptrc<P> Polygon() const { return const_cast<HE*>(this)->Polygon(); }
		const ptrc<V> End() const { return const_cast<HE*>(this)->End(); }
		const ptrc<HE> Pre() const { return const_cast<HE*>(this)->Pre(); }
		const ptrc<HE> RotateNext() const { return const_cast<HE*>(this)->RotateNext(); }
		const ptrc<HE> RotatePre() const { return const_cast<HE*>(this)->RotatePre(); }

		void SetNext(ptr<HE> he) { next = he.idx; }
		void SetPair(ptr<HE> he) { pair = he.idx; }
		void SetOrigin(ptr<V> v) { origin = v.idx; }
		void SetEdge(ptr<E> e) { edge = e.idx; }
		void SetPolygon(ptr<P> p) { polygon = p.idx; }
		void Init(ptr<HE> next, ptr<HE> pair, ptr<V> v, ptr<E> e, ptr<P> p);

		bool IsFree() const { return polygon == -1; }
		bool IsBoundary() const { return polygon == -1; }

		static const ptr<HE> FindFreeIncident(ptr<HE> begin, ptr<HE> end);

		static bool MakeAdjacent(ptr<HE> inHE, ptr<HE> outHE);

		// [begin, end), if begin == end, return a loop
		static const std::vector<ptr<HE>> NextBetween(ptr<HE> begin, ptr<HE> end);
		// [begin, end), if begin == end, return a loop
		static const std::vector<ptr<HE>> RotateNextBetween(ptr<HE> begin, ptr<HE> end);
		// [this, end), NextBetween(this, end);
		const std::vector<ptr<HE>> NextTo(ptr<HE> end) { return NextBetween(Self(), end); }
		// [this, end), RotateNextBetween(this, end);
		const std::vector<ptr<HE>> RotateNextTo(ptr<HE> end) { return RotateNextBetween(Self(), end); }
		// NextBetween(this, this), a loop from this to this
		const std::vector<ptr<HE>> NextLoop() { return NextBetween(Self(), Self()); }
		// RotateNextBetween(this, this), a loop from this to this
		const std::vector<ptr<HE>> RotateNextLoop() { return RotateNextBetween(Self(), Self()); }

	private:
		const ptr<HE> Self() { return Pair()->Pair(); }
		const ptrc<HE> Self() const { return const_cast<HE*>(this)->Self(); }

	private:
		friend class HEMesh<V>;
		HEMesh<V>* mesh = nullptr;

		int next = -1;
		int pair = -1;

		int origin = -1;
		int edge = -1;
		int polygon = -1;
	};
}

#include "THalfEdge.inl"

#endif // !_UBPA_HEMESH_THALFEDGE_H_
