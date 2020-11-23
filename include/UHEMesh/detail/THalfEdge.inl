#pragma once

namespace Ubpa {
	template<typename Traits>
	HEMeshTraits_H<Traits>* THalfEdge<Traits>::Pre() noexcept {
		auto* he = this;
		auto* next = he->Next();
		do {
			he = next;
			next = he->Next();
		} while (next != this);
		return he->This();
	}

	template<typename Traits>
	void THalfEdge<Traits>::Init(H* next, H* pair, V* v, E* e, P* p) noexcept {
		assert(next != nullptr && pair != nullptr && v != nullptr && e != nullptr);
		this->next = next;
		this->pair = pair;
		origin = v;
		edge = e;
		polygon = p;
	}

	template<typename Traits>
	HEMeshTraits_H<Traits>* THalfEdge<Traits>::FindFreeIncident(H* begin, H* end) {
		assert(begin->End() == end->End());

		for (auto* he = begin; he != end; he = he->Next()->Pair()) {
			if (he->IsFree())
				return he->This();
		}

		return nullptr;
	}

	template<typename Traits>
	bool THalfEdge<Traits>::MakeAdjacent(H* inHE, H* outHE) {
		assert(inHE->End() == outHE->Origin());

		if (inHE->Next() == outHE)
			return true;

		auto* freeIn = FindFreeIncident(outHE->Pair(), inHE);
		if (freeIn == nullptr)
			return false;

		auto* inNext = inHE->Next();
		auto* outPre = outHE->Pre();
		auto* freeInNext = freeIn->Next();

		inHE->SetNext(outHE);
		freeIn->SetNext(inNext);
		outPre->SetNext(freeInNext);

		return true;
	}

	template<typename Traits>
	std::vector<HEMeshTraits_H<Traits>*> THalfEdge<Traits>::NextBetween(H* begin, H* end) {
		std::vector<H*> hes;
		auto* he = begin;
		do {
			hes.push_back(he);
			he = he->Next();
		} while (he != end);
		return hes;
	}

	template<typename Traits>
	std::vector<HEMeshTraits_H<Traits>*> THalfEdge<Traits>::RotateNextBetween(H* begin, H* end) {
		std::vector<H*> hes;
		auto* he = begin;
		do {
			hes.push_back(he);
			he = he->RotateNext();
		} while (he != end);
		return hes;
	}
}
