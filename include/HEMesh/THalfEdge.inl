#pragma once
#ifndef _UBPA_HEMESH_THALFEDGE_INL_
#define _UBPA_HEMESH_THALFEDGE_INL_

namespace Ubpa {
	template<typename V, typename E, typename P>
	const HEMesh_ptr<THalfEdge<V, E, P>, HEMesh<V>> THalfEdge<V, E, P>::Pre() {
		auto self = Self();
		auto he = self;
		auto next = he->Next();
		do {
			he = next;
			next = he->Next();
		} while (next != self);
		return he;
	}

	template<typename V, typename E, typename P>
	void THalfEdge<V, E, P>::Init(ptr<HE> next, ptr<HE> pair, ptr<V> v, ptr<E> e, ptr<P> p) {
		this->next = next;
		this->pair = pair;
		this->origin = v;
		this->edge = e;
		this->polygon = p;
	}

	template<typename V, typename E, typename P>
	const HEMesh_ptr<THalfEdge<V, E, P>, HEMesh<V>> THalfEdge<V, E, P>::FindFreeIncident(ptr<HE> begin, ptr<HE> end) {
		assert(begin->End() == end->End());

		for (auto he = begin; he != end; he = he->Next()->Pair()) {
			if (he->IsFree())
				return he;
		}

		return nullptr;
	}

	template<typename V, typename E, typename P>
	bool THalfEdge<V, E, P>::MakeAdjacent(ptr<HE> inHE, ptr<HE> outHE) {
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
	const std::vector<HEMesh_ptr<THalfEdge<V, E, P>, HEMesh<V>>> THalfEdge<V, E, P>::NextBetween(ptr<HE> begin, ptr<HE> end) {
		std::vector<ptr<HE>> hes;
		auto he = begin;
		do {
			hes.push_back(he);
			he = he->Next();
		} while (he != end);
		return hes;
	}

	template<typename V, typename E, typename P>
	const std::vector<HEMesh_ptr<THalfEdge<V, E, P>, HEMesh<V>>> THalfEdge<V, E, P>::RotateNextBetween(ptr<HE> begin, ptr<HE> end) {
		std::vector<ptr<HE>> hes;
		auto he = begin;
		do {
			hes.push_back(he);
			he = he->RotateNext();
		} while (he != end);
		return hes;
	}

	template<typename V, typename E, typename P>
	void THalfEdge<V, E, P>::Clear() {
		next = nullptr;
		pair = nullptr;
		origin = nullptr;
		edge = nullptr;
		polygon = nullptr;
	}
}

#endif // !_UBPA_HEMESH_THALFEDGE_INL_
