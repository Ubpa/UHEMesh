#pragma once

#include "THalfEdge.h"
#include "TVertex.h"
#include "TEdge.h"
#include "TPolygon.h"

namespace Ubpa {
	template <typename E, typename P>
	class EmptyV : public TVertex<EmptyV<E, P>, E, P> {};
	template <typename V, typename E>
	class EmptyP : public TPolygon<V, E, EmptyP<V, E>> {};
	template <typename V, typename P>
	class EmptyE : public TEdge<V, EmptyE<V, P>, P> {};

	template <typename V>
	class EmptyEP_E : public TEdge<V, EmptyEP_E<V>, EmptyEP_P<V>> {};
	template <typename V>
	class EmptyEP_P : public TPolygon<V, EmptyEP_E<V>, EmptyEP_P<V>> {};

	class AllEmpty : public TVertex<AllEmpty, EmptyEP_E<AllEmpty>, EmptyEP_P<AllEmpty>> {};
}
