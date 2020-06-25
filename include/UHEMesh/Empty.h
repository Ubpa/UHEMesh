#pragma once

#include "THalfEdge.h"
#include "TVertex.h"
#include "TEdge.h"
#include "TPolygon.h"

namespace Ubpa {
	template <typename E, typename P> using HEMeshTriats_EmptyV = HEMeshTriats<EmptyV<E, P>, E, P>;
	template <typename V, typename P> using HEMeshTriats_EmptyE = HEMeshTriats<V, EmptyE<V, P>, P>;
	template <typename V, typename E> using HEMeshTriats_EmptyP = HEMeshTriats<V, E, EmptyP<V, E>>;

	template <typename E, typename P> class EmptyV : public TVertex<HEMeshTriats_EmptyV<E, P>> {};
	template <typename V, typename P> class EmptyE : public TEdge<HEMeshTriats_EmptyE<V, P>> {};
	template <typename V, typename E> class EmptyP : public TPolygon<HEMeshTriats_EmptyP<V, E>> {};

	template <typename P> using HEMeshTriats_EmptyVE = HEMeshTriats<EmptyVE_V<P>, EmptyVE_E<P>, P>;
	template <typename E> using HEMeshTriats_EmptyVP = HEMeshTriats<EmptyVP_V<E>, E, EmptyVP_P<E>>;
	template <typename V> using HEMeshTriats_EmptyEP = HEMeshTriats<V, EmptyEP_E<V>, EmptyEP_P<V>>;

	template <typename P> class EmptyVE_V : public TVertex<HEMeshTriats_EmptyVE<P>> {};
	template <typename P> class EmptyVE_E : public TEdge<HEMeshTriats_EmptyVE<P>> {};
	template <typename E> class EmptyVP_V : public TVertex<HEMeshTriats_EmptyVP<E>> {};
	template <typename E> class EmptyVP_P : public TPolygon<HEMeshTriats_EmptyVP<E>> {};
	template <typename V> class EmptyEP_E : public TEdge<HEMeshTriats_EmptyEP<V>> {};
	template <typename V> class EmptyEP_P : public TPolygon<HEMeshTriats_EmptyEP<V>> {};

	using HEMeshTriats_EmptyVEP = HEMeshTriats<EmptyVEP_V, EmptyVEP_E, EmptyVEP_P>;

	class EmptyVEP_V : public TVertex<HEMeshTriats_EmptyVEP> {};
	class EmptyVEP_E : public TEdge<HEMeshTriats_EmptyVEP> {};
	class EmptyVEP_P : public TPolygon<HEMeshTriats_EmptyVEP> {};
}
