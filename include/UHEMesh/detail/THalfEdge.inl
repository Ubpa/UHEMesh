#pragma once

namespace Ubpa {
	template<typename Traits>
	HEMeshTriats_HE<Traits>* const THalfEdge<Traits>::Pre() {
		auto he = this;
		auto next = he->Next();
		do {
			he = next;
			next = he->Next();
		} while (next != this);
		return he;
	}

	template<typename Traits>
	void THalfEdge<Traits>::Init(HE* next, HE* pair, V* v, E* e, P* p) {
		assert(next != nullptr && pair != nullptr && v != nullptr && e != nullptr);
		this->next = next;
		this->pair = pair;
		origin = v;
		edge = e;
		polygon = p;
	}

	template<typename Traits>
	HEMeshTriats_HE<Traits>* const THalfEdge<Traits>::FindFreeIncident(HE* begin, HE* end) {
		assert(begin->End() == end->End());

		for (auto he = begin; he != end; he = he->Next()->Pair()) {
			if (he->IsFree())
				return he;
		}

		return nullptr;
	}

	template<typename Traits>
	bool THalfEdge<Traits>::MakeAdjacent(HE* inHE, HE* outHE) {
		assert(inHE->End() == outHE->Origin());

		if (inHE->Next() == outHE)
			return true;

		auto freeIn = FindFreeIncident(outHE->Pair(), inHE);
		if (freeIn == nullptr)
			return false;

		auto inNext = inHE->Next();
		auto outPre = outHE->Pre();
		auto freeInNext = freeIn->Next();

		inHE->SetNext(outHE);
		freeIn->SetNext(inNext);
		outPre->SetNext(freeInNext);

		return true;
	}

	template<typename Traits>
	const std::vector<HEMeshTriats_HE<Traits>*> THalfEdge<Traits>::NextBetween(HE* begin, HE* end) {
		std::vector<HE*> hes;
		auto he = begin;
		do {
			hes.push_back(he);
			he = he->Next();
		} while (he != end);
		return hes;
	}

	template<typename Traits>
	const std::vector<HEMeshTriats_HE<Traits>*> THalfEdge<Traits>::RotateNextBetween(HE* begin, HE* end) {
		std::vector<HE*> hes;
		auto he = begin;
		do {
			hes.push_back(he);
			he = he->RotateNext();
		} while (he != end);
		return hes;
	}
}
