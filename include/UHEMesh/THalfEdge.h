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
		H* const Next() noexcept { return next; }
		H* const Pair() noexcept { return pair; }
		V* const Origin() noexcept { return origin; }
		E* const Edge() noexcept { return edge; }
		P* const Polygon() noexcept { return polygon; }
		V* const End() noexcept { return Next()->Origin(); }
		H* const Pre() noexcept;
		H* const RotateNext() noexcept { return Pair()->Next(); }
		H* const RotatePre() noexcept { return Pre()->Pair(); }

		const H* const Next() const noexcept { return const_cast<H*>(This())->Next(); }
		const H* const Pair() const noexcept { return const_cast<H*>(This())->Pair(); }
		const V* const Origin() const noexcept { return const_cast<H*>(This())->Origin(); }
		const E* const Edge() const noexcept { return const_cast<H*>(This())->Edge(); }
		const P* const Polygon() const noexcept { return const_cast<H*>(This())->Polygon(); }
		const V* const End() const noexcept { return const_cast<H*>(This())->End(); }
		const H* const Pre() const noexcept { return const_cast<H*>(This())->Pre(); }
		const H* const RotateNext() const noexcept { return const_cast<H*>(This())->RotateNext(); }
		const H* const RotatePre() const noexcept { return const_cast<H*>(This())->RotatePre(); }

		void SetNext(H* he) noexcept { next = he; }
		void SetPair(H* he) noexcept { pair = he; }
		void SetOrigin(V* v) noexcept { origin = v; }
		void SetEdge(E* e) noexcept { edge = e; }
		void SetPolygon(P* p) noexcept { polygon = p; }
		// next, pair, v, e can't be nullptr
		// p can be nullptr
		void Init(H* next, H* pair, V* v, E* e, P* p) noexcept;

		// polygon == nullptr
		bool IsBoundary() const noexcept { return !polygon; }

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
		friend HEMesh<Traits>;
		friend TVertex<Traits>;

		bool IsFree() const noexcept { return !polygon; }
		static bool MakeAdjacent(H* inHE, H* outHE);
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
