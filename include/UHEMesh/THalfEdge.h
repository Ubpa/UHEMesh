#pragma once

#include "detail/ForwardDecl.h"

namespace Ubpa {
	template<typename Traits>
	class THalfEdge {
	public:
		using V = HEMeshTriats_V<Traits>;
		using E = HEMeshTriats_E<Traits>;
		using P = HEMeshTriats_P<Traits>;
		using H = HEMeshTriats_H<Traits>;

	public:
		H* const Next() { return next; }
		H* const Pair() { return pair; }
		V* const Origin() { return origin; }
		E* const Edge() { return edge; }
		P* const Polygon() { return polygon; }
		V* const End() { return Next()->Origin(); }
		H* const Pre();
		H* const RotateNext() { return Pair()->Next(); }
		H* const RotatePre() { return Pre()->Pair(); }

		const H* const Next() const { return const_cast<H*>(This())->Next(); }
		const H* const Pair() const { return const_cast<H*>(This())->Pair(); }
		const V* const Origin() const { return const_cast<H*>(This())->Origin(); }
		const E* const Edge() const { return const_cast<H*>(This())->Edge(); }
		const P* const Polygon() const { return const_cast<H*>(This())->Polygon(); }
		const V* const End() const { return const_cast<H*>(This())->End(); }
		const H* const Pre() const { return const_cast<H*>(This())->Pre(); }
		const H* const RotateNext() const { return const_cast<H*>(This())->RotateNext(); }
		const H* const RotatePre() const { return const_cast<H*>(This())->RotatePre(); }

		void SetNext(H* he) { next = he; }
		void SetPair(H* he) { pair = he; }
		void SetOrigin(V* v) { origin = v; }
		void SetEdge(E* e) { edge = e; }
		void SetPolygon(P* p) { polygon = p; }
		void Init(H* next, H* pair, V* v, E* e, P* p);

		bool IsFree() const { return !polygon; }
		bool IsBoundary() const { return !polygon; }

		static bool MakeAdjacent(H* inHE, H* outHE);

		// [begin, end), if begin == end, return a loop
		static const std::vector<H*> NextBetween(H* begin, H* end);

		// [this, end), NextBetween(this, end);
		const std::vector<H*> NextTo(H* end) { return NextBetween(This(), end); }

		// NextBetween(this, this), a loop from this to this
		const std::vector<H*> NextLoop() { return NextTo(This()); }

		// [begin, end), if begin == end, return a loop
		static const std::vector<H*> RotateNextBetween(H* begin, H* end);

		// [this, end), RotateNextBetween(this, end);
		const std::vector<H*> RotateNextTo(H* end) { return RotateNextBetween(This(), end); }

		// RotateNextBetween(this, this), a loop from this to this
		const std::vector<H*> RotateNextLoop() { return RotateNextTo(This()); }

	private:
		friend class HEMesh<Traits>;

		static H* const FindFreeIncident(H* begin, H* end);

		H* This() noexcept { return static_cast<H*>(this); }
		const H* This() const noexcept { return static_cast<const H*>(this); }

		H* next{ nullptr };
		H* pair{ nullptr };

		V* origin{ nullptr };
		E* edge{ nullptr };
		P* polygon{ nullptr };
	};
}

#include "detail/THalfEdge.inl"
