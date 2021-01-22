#pragma once

namespace Ubpa {
	template<typename Traits>
	bool TVertex<Traits>::IsOnBoundary() const noexcept {
		if (IsIsolated())
			return true;

		for (auto* he : HalfEdge()->NextLoop()) {
			if (he->IsOnBoundary())
				return true;
		}

		return false;
	}

	template<typename Traits>
	HalfEdgeRotateNextView<false, Traits> TVertex<Traits>::OutHalfEdges() {
		if (IsIsolated())
			return {};

		return { HalfEdge(), HalfEdge() };
	}

	template<typename Traits>
	HalfEdgeRotateNextView<true, Traits> TVertex<Traits>::OutHalfEdges() const {
		return reinterpret_cast<HalfEdgeRotateNextView<true, Traits>&&>(const_cast<TVertex*>(this)->OutHalfEdges());
	}

	template<typename Traits>
	std::size_t TVertex<Traits>::Degree() const noexcept {
		std::size_t cnt = 0;
		for (auto* he : OutHalfEdges())
			++cnt;
		return cnt;
	}

	template<typename Traits>
	HEMeshTraits_H<Traits>* TVertex<Traits>::FindFreeIncident() noexcept {
		if (IsIsolated())
			return nullptr;

		auto* begin = HalfEdge()->Pair();
		auto* he = begin;
		do {
			if (he->IsFree())
				return he;
			he = he->Next()->Pair();
		} while (he != begin);

		return nullptr;
	}

	template<typename Traits>
	HEMeshTraits_H<Traits>* TVertex<Traits>::HalfEdgeTo(V* end) noexcept {
		if (IsIsolated())
			return nullptr;

		auto* begin = HalfEdge();
		auto* he = begin;
		do {
			if (he->End() == end)
				return he;
			he = he->RotateNext();
		} while (he != begin);

		return nullptr;
	}

	template<typename Traits>
	HEMeshTraits_E<Traits>* TVertex<Traits>::EdgeWith(V* v) noexcept {
		auto* he = HalfEdgeTo(v);
		if (!he)
			return nullptr;

		return he->Edge();
	}
}
