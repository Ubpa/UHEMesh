#pragma once
#ifndef _UBPA_HEMESH_THALFEDGE_INL_
#define _UBPA_HEMESH_THALFEDGE_INL_

namespace Ubpa {
	template<typename V, typename E, typename P>
	THalfEdge<V, E, P>* const THalfEdge<V, E, P>::Pre() {
		auto he = this;
		auto next = he->Next();
		do {
			he = next;
			next = he->Next();
		} while (next != this);
		return he;
	}

	template<typename V, typename E, typename P>
	void THalfEdge<V, E, P>::Init(HE* next, HE* pair, V* v, E* e, P* p) {
		assert(next != nullptr && pair != nullptr && v != nullptr && e != nullptr);
		this->next = next;
		this->pair = pair;
		origin = v;
		edge = e;
		polygon = p;
	}

	template<typename V, typename E, typename P>
	THalfEdge<V, E, P>* const THalfEdge<V, E, P>::FindFreeIncident(HE* begin, HE* end) {
		assert(begin->End() == end->End());

		for (auto he = begin; he != end; he = he->Next()->Pair()) {
			if (he->IsFree())
				return he;
		}

		return nullptr;
	}

	template<typename V, typename E, typename P>
	bool THalfEdge<V, E, P>::MakeAdjacent(HE* inHE, HE* outHE) {
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

	template<typename V, typename E, typename P>
	const std::vector<THalfEdge<V, E, P>*> THalfEdge<V, E, P>::NextBetween(HE* begin, HE* end) {
		std::vector<HE*> hes;
		auto he = begin;
		do {
			hes.push_back(he);
			he = he->Next();
		} while (he != end);
		return hes;
	}

	template<typename V, typename E, typename P>
	const std::vector<THalfEdge<V, E, P>*> THalfEdge<V, E, P>::RotateNextBetween(HE* begin, HE* end) {
		std::vector<HE*> hes;
		auto he = begin;
		do {
			hes.push_back(he);
			he = he->RotateNext();
		} while (he != end);
		return hes;
	}
}

#endif // !_UBPA_HEMESH_THALFEDGE_INL_
