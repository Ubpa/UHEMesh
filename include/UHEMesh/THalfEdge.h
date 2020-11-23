#pragma once

#include "detail/ForwardDecl.h"

namespace Ubpa {
	template<typename Traits>
	class THalfEdge {
	public:
		using V = HEMeshTraits_V<Traits>;
		using E = HEMeshTraits_E<Traits>;
		using P = HEMeshTraits_P<Traits>;
		using H = HEMeshTraits_H<Traits>;

	public:
		H* Next() noexcept { return next; }
		H* Pair() noexcept { return pair; }
		V* Origin() noexcept { return origin; }
		E* Edge() noexcept { return edge; }
		P* Polygon() noexcept { return polygon; }
		V* End() noexcept { return Next()->Origin(); }
		H* Pre() noexcept;
		H* RotateNext() noexcept { return Pair()->Next(); }
		H* RotatePre() noexcept { return Pre()->Pair(); }

		const H* Next() const noexcept { return const_cast<H*>(This())->Next(); }
		const H* Pair() const noexcept { return const_cast<H*>(This())->Pair(); }
		const V* Origin() const noexcept { return const_cast<H*>(This())->Origin(); }
		const E* Edge() const noexcept { return const_cast<H*>(This())->Edge(); }
		const P* Polygon() const noexcept { return const_cast<H*>(This())->Polygon(); }
		const V* End() const noexcept { return const_cast<H*>(This())->End(); }
		const H* Pre() const noexcept { return const_cast<H*>(This())->Pre(); }
		const H* RotateNext() const noexcept { return const_cast<H*>(This())->RotateNext(); }
		const H* RotatePre() const noexcept { return const_cast<H*>(This())->RotatePre(); }

		void SetNext(H* he) noexcept { next = he; }
		void SetPair(H* he) noexcept { pair = he; }
		void SetOrigin(V* v) noexcept { origin = v; }
		void SetEdge(E* e) noexcept { edge = e; }
		void SetPolygon(P* p) noexcept { polygon = p; }

		// next, pair, v, e can't be nullptr
		// p can be nullptr
		void Init(H* next, H* pair, V* v, E* e, P* p) noexcept;

		// polygon == nullptr
		bool IsOnBoundary() const noexcept { return !polygon; }

		// [begin, end), if begin == end, return a loop
		static std::vector<H*> NextBetween(H* begin, H* end);

		// [this, end), NextBetween(this, end);
		std::vector<H*> NextTo(H* end) { return NextBetween(This(), end); }

		// NextBetween(this, this), a loop from this to this
		std::vector<H*> NextLoop() { return NextTo(This()); }

		// [begin, end), if begin == end, return a loop
		static std::vector<H*> RotateNextBetween(H* begin, H* end);

		// [this, end), RotateNextBetween(this, end);
		std::vector<H*> RotateNextTo(H* end) { return RotateNextBetween(This(), end); }

		// RotateNextBetween(this, this), a loop from this to this
		std::vector<H*> RotateNextLoop() { return RotateNextTo(This()); }

	private:
		friend HEMesh<Traits>;
		friend TVertex<Traits>;

		bool IsFree() const noexcept { return !polygon; }
		static bool MakeAdjacent(H* inHE, H* outHE);
		static H* FindFreeIncident(H* begin, H* end);

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
