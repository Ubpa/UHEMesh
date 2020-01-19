#pragma once
#ifndef _UBPA_HEMESH_THALFEDGE_H_
#define _UBPA_HEMESH_THALFEDGE_H_

#include <HEMesh/ForwardDecl.h>

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
		const ptr<HE> Next() { return next; }
		const ptr<HE> Pair() { return pair; }
		const ptr<V> Origin() { return origin; }
		const ptr<E> Edge() { return edge; }
		const ptr<P> Polygon() { return polygon; }
		const ptr<V> End() { return pair->Origin(); }
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

		void SetNext(ptr<HE> he) { next = he; }
		void SetPair(ptr<HE> he) { pair = he; }
		void SetOrigin(ptr<V> v) { origin = v; }
		void SetEdge(ptr<E> e) { edge = e; }
		void SetPolygon(ptr<P> p) { polygon = p; }
		void Init(ptr<HE> next, ptr<HE> pair, ptr<V> v, ptr<E> e, ptr<P> p);

		bool IsFree() const { return polygon == nullptr; }
		bool IsBoundary() const { return polygon == nullptr; }

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

		void Clear();

	private:
		const ptr<HE> Self() { return Pair()->Pair(); }
		const ptrc<HE> Self() const { return const_cast<HE*>(this)->Self(); }

	private:
		ptr<HE> next;
		ptr<HE> pair;

		ptr<V> origin;
		ptr<E> edge;
		ptr<P> polygon;
	};
}

#include <HEMesh/THalfEdge.inl>

#endif // !_UBPA_HEMESH_THALFEDGE_H_
