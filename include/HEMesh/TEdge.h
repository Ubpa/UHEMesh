#pragma once
#ifndef _UBPA_HEMESH_TEDGE_H_
#define _UBPA_HEMESH_TEDGE_H_

#include "ForwardDecl.h"

namespace Ubpa {
	template<typename V, typename E, typename P = EmptyP<V, E>>
	class TEdge {
	private:
		// internal use
		using HE = THalfEdge<V, E, P>;
		template<typename T>
		using ptr = HEMesh_ptr<T, HEMesh<V>>;
		template<typename T>
		using ptrc = ptr<const T>;

	public:
		// external use
		using Ptr = ptr<E>;
		using PtrC = ptrc<E>;

	public:
		const ptr<HE> HalfEdge() { return halfEdge; }
		const ptrc<HE> HalfEdge() const { return const_cast<TEdge*>(this)->HalfEdge(); }

		void SetHalfEdge(ptr<HE> he) { halfEdge = he; }

		bool IsBoundary() const { return HalfEdge()->IsBoundary() || HalfEdge()->Pair()->IsBoundary(); }
		bool IsFree() const { return HalfEdge()->IsFree() && HalfEdge()->Pair()->IsFree(); }

		// clockwise
		// + [he.RotateNext, he.RotateNext.RotateNext, ..., he)
		// + [he.next, he.next.RotateNext, ..., he.pair)
		const std::vector<ptr<HE>> OutHEs();
		const std::set<ptr<V>> AdjVertices();
		const std::vector<ptr<E>> AdjEdges();

		void Clear() { halfEdge = nullptr; }

	private:
		ptr<HE> halfEdge;
	};
}

#include "TEdge.inl"

#endif // !_UBPA_HEMESH_TEDGE_H_
