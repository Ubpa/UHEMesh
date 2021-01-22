#pragma once

#include "detail/ForwardDecl.h"

#include <concepts>

namespace Ubpa {
	template<bool IsConst, typename Traits>
	class HalfEdgeNextView {
	public:
		using H = HEMeshTraits_H<Traits>;
		using Data = std::conditional_t<IsConst, const H*, H*>;

		class Iterator {
		public:
			using value_type = Data;
			using difference_type = std::ptrdiff_t;
			using pointer = std::add_pointer_t<value_type>;
			using reference = std::add_lvalue_reference_t<std::add_const_t<value_type>>;
			using iterator_category = std::forward_iterator_tag;

			constexpr Iterator(value_type he, bool is_begin) noexcept : he{ he }, is_begin{ is_begin } {}
			constexpr Iterator() noexcept : he{ nullptr }, is_begin{ false } {}
			constexpr bool operator==(const Iterator& rhs) const noexcept { return he == rhs.he && is_begin == rhs.is_begin; }
			value_type operator->() const noexcept { return he; }
			reference operator*() const noexcept { return he; }
			Iterator& operator++() noexcept { he = he->Next(); is_begin = false; return *this; }
			Iterator operator++(int) noexcept { Iterator rst = *this; this->operator++(); return rst; }
		private:
			value_type he;
			bool is_begin;
		};

		constexpr HalfEdgeNextView(Data begin_halfedge, Data end_halfedge) noexcept :
			begin_halfedge{ begin_halfedge }, end_halfedge{ end_halfedge } { assert(begin_halfedge->Polygon() == end_halfedge->Polygon()); }
		constexpr HalfEdgeNextView() noexcept :
			begin_halfedge{ nullptr }, end_halfedge{ nullptr }{}

		Iterator begin() const noexcept { return begin_halfedge ? Iterator{ begin_halfedge, true } : Iterator{}; }
		Iterator end() const noexcept { return { end_halfedge, false }; }

	private:
		Data begin_halfedge;
		Data end_halfedge;
	};

	template<bool IsConst, typename Traits>
	class HalfEdgeRotateNextView {
	public:
		using H = HEMeshTraits_H<Traits>;
		using Data = std::conditional_t<IsConst, const H*, H*>;

		class Iterator {
		public:
			using value_type = Data;
			using difference_type = std::ptrdiff_t;
			using pointer = std::add_pointer_t<value_type>;
			using reference = std::add_lvalue_reference_t<std::add_const_t<value_type>>;
			using iterator_category = std::forward_iterator_tag;

			constexpr Iterator(value_type he, bool is_begin) noexcept : he{ he }, is_begin{ is_begin } {}
			constexpr Iterator() noexcept : he{ nullptr }, is_begin{ false } {}
			constexpr bool operator==(const Iterator& rhs) const noexcept { return he == rhs.he && is_begin == rhs.is_begin; }
			value_type operator->() const noexcept { return he; }
			reference operator*() const noexcept { return he; }
			Iterator& operator++() noexcept { he = he->RotateNext(); is_begin = false; return *this; }
			Iterator operator++(int) noexcept { Iterator rst = *this; this->operator++(); return rst; }
		private:
			value_type he;
			bool is_begin;
		};

		constexpr HalfEdgeRotateNextView(Data begin_halfedge, Data end_halfedge) noexcept :
			begin_halfedge{ begin_halfedge }, end_halfedge{ end_halfedge } { assert(begin_halfedge->Polygon() == end_halfedge->Polygon()); }
		constexpr HalfEdgeRotateNextView() noexcept :
			begin_halfedge{ nullptr }, end_halfedge{ nullptr }{}

		Iterator begin() const noexcept { return begin_halfedge? Iterator{ begin_halfedge, true } : Iterator{}; }
		Iterator end() const noexcept { return { end_halfedge, false }; }

	private:
		Data begin_halfedge;
		Data end_halfedge;
	};

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

		// [begin, end), begin == end <=> loop
		static constexpr HalfEdgeNextView<false, Traits> NextBetween(H* begin, H* end) { return { begin, end }; }
		// [this, end), NextBetween(this, end);
		constexpr HalfEdgeNextView<false, Traits> NextTo(H* end) { return NextBetween(This(), end); }
		// NextBetween(this, this), a loop from this to this
		constexpr HalfEdgeNextView<false, Traits> NextLoop() { return NextTo(This()); }

		// [begin, end), begin == end <=> loop
		static constexpr HalfEdgeNextView<true, Traits> NextBetween(const H* begin, const H* end) { return { begin, end }; }
		// [this, end), NextBetween(this, end);
		constexpr HalfEdgeNextView<true, Traits> NextTo(const H* end) const { return NextBetween(This(), end); }
		// NextBetween(this, this), a loop from this to this
		constexpr HalfEdgeNextView<true, Traits> NextLoop() const { return NextTo(This()); }

		// [begin, end), begin == end <=> loop
		static constexpr HalfEdgeRotateNextView<false, Traits> RotateNextBetween(H* begin, H* end) { return { begin, end }; }
		// [this, end), RotateNextBetween(this, end);
		constexpr HalfEdgeRotateNextView<false, Traits> RotateNextTo(H* end) { return RotateNextBetween(This(), end); }
		// RotateNextBetween(this, this), a loop from this to this
		constexpr HalfEdgeRotateNextView<false, Traits> RotateNextLoop() { return RotateNextTo(This()); }

		// [begin, end), begin == end <=> loop
		static constexpr HalfEdgeRotateNextView<true, Traits> RotateNextBetween(const H* begin, const H* end) { return { begin, end }; }
		// [this, end), RotateNextBetween(this, end);
		constexpr HalfEdgeRotateNextView<true, Traits> RotateNextTo(const H* end) const { return RotateNextBetween(This(), end); }
		// RotateNextBetween(this, this), a loop from this to this
		constexpr HalfEdgeRotateNextView<true, Traits> RotateNextLoop() const { return RotateNextTo(This()); }

		std::size_t PolygonDegree() const noexcept;

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
