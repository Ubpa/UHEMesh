#pragma once

#include "THalfEdge.h"
#include "TVertex.h"
#include "TEdge.h"
#include "TPolygon.h"

namespace Ubpa {
	template <typename E, typename P, typename H> using HEMeshTriats_EmptyV = HEMeshTriats<EmptyV<E, P, H>, E, P, H>;
	template <typename V, typename P, typename H> using HEMeshTriats_EmptyE = HEMeshTriats<V, EmptyE<V, P, H>, P, H>;
	template <typename V, typename E, typename H> using HEMeshTriats_EmptyP = HEMeshTriats<V, E, EmptyP<V, E, H>, H>;
	template <typename V, typename E, typename P> using HEMeshTriats_EmptyH = HEMeshTriats<V, E, P, EmptyH<V, E, P>>;

	template <typename P, typename H> using HEMeshTriats_EmptyVE = HEMeshTriats<EmptyVE_V<P, H>, EmptyVE_E<P, H>, P, H>;
	template <typename E, typename H> using HEMeshTriats_EmptyVP = HEMeshTriats<EmptyVP_V<E, H>, E, EmptyVP_P<E, H>, H>;
	template <typename E, typename P> using HEMeshTriats_EmptyVH = HEMeshTriats<EmptyVH_V<E, P>, E, P, EmptyVH_H<E, P>>;
	template <typename V, typename H> using HEMeshTriats_EmptyEP = HEMeshTriats<V, EmptyEP_E<V, H>, EmptyEP_P<V, H>, H>;
	template <typename V, typename P> using HEMeshTriats_EmptyEH = HEMeshTriats<V, EmptyEH_E<V, P>, P, EmptyEH_H<V, P>>;
	template <typename V, typename E> using HEMeshTriats_EmptyPH = HEMeshTriats<V, E, EmptyPH_P<V, E>, EmptyPH_H<V, E>>;

	template <typename H> using HEMeshTriats_EmptyVEP = HEMeshTriats<EmptyVEP_V<H>, EmptyVEP_E<H>, EmptyVEP_P<H>, H>;
	template <typename P> using HEMeshTriats_EmptyVEH = HEMeshTriats<EmptyVEH_V<P>, EmptyVEH_E<P>, P, EmptyVEH_H<P>>;
	template <typename E> using HEMeshTriats_EmptyVPH = HEMeshTriats<EmptyVPH_V<E>, E, EmptyVPH_P<E>, EmptyVPH_P<E>>;
	template <typename V> using HEMeshTriats_EmptyEPH = HEMeshTriats<V, EmptyEPH_E<V>, EmptyEPH_P<V>, EmptyEPH_H<V>>;

	using HEMeshTriats_EmptyVEPH = HEMeshTriats<EmptyVEPH_V, EmptyVEPH_E, EmptyVEPH_P, EmptyVEPH_H>;

	template <typename E, typename P, typename H> class EmptyV : public TVertex  <HEMeshTriats_EmptyV<E, P, H>> {};
	template <typename V, typename P, typename H> class EmptyE : public TEdge    <HEMeshTriats_EmptyE<V, P, H>> {};
	template <typename V, typename E, typename H> class EmptyP : public TPolygon <HEMeshTriats_EmptyP<V, E, H>> {};
	template <typename V, typename E, typename P> class EmptyH : public THalfEdge<HEMeshTriats_EmptyH<V, E, P>> {};

	template <typename P, typename H> class EmptyVE_V : public TVertex  <HEMeshTriats_EmptyVE<P, H>> {};
	template <typename P, typename H> class EmptyVE_E : public TEdge    <HEMeshTriats_EmptyVE<P, H>> {};
	template <typename E, typename H> class EmptyVP_V : public TVertex  <HEMeshTriats_EmptyVP<E, H>> {};
	template <typename E, typename H> class EmptyVP_P : public TPolygon <HEMeshTriats_EmptyVP<E, H>> {};
	template <typename E, typename P> class EmptyVH_V : public TVertex  <HEMeshTriats_EmptyVH<E, P>> {};
	template <typename E, typename P> class EmptyVH_P : public THalfEdge<HEMeshTriats_EmptyVH<E, P>> {};
	template <typename V, typename H> class EmptyEP_E : public TEdge    <HEMeshTriats_EmptyEP<V, H>> {};
	template <typename V, typename H> class EmptyEP_P : public TPolygon <HEMeshTriats_EmptyEP<V, H>> {};
	template <typename V, typename P> class EmptyEH_E : public TEdge    <HEMeshTriats_EmptyEH<V, P>> {};
	template <typename V, typename P> class EmptyEH_H : public THalfEdge<HEMeshTriats_EmptyEH<V, P>> {};
	template <typename V, typename E> class EmptyPH_P : public TPolygon <HEMeshTriats_EmptyPH<V, E>> {};
	template <typename V, typename E> class EmptyPH_H : public THalfEdge<HEMeshTriats_EmptyPH<V, E>> {};

	template <typename H> class EmptyVEP_V : public TVertex  <HEMeshTriats_EmptyVEP<H>> {};
	template <typename H> class EmptyVEP_E : public TEdge    <HEMeshTriats_EmptyVEP<H>> {};
	template <typename H> class EmptyVEP_P : public TPolygon <HEMeshTriats_EmptyVEP<H>> {};
	template <typename P> class EmptyVEH_V : public TVertex  <HEMeshTriats_EmptyVEH<P>> {};
	template <typename P> class EmptyVEH_E : public TEdge    <HEMeshTriats_EmptyVEH<P>> {};
	template <typename P> class EmptyVEH_H : public THalfEdge<HEMeshTriats_EmptyVEH<P>> {};
	template <typename E> class EmptyVPH_V : public TVertex  <HEMeshTriats_EmptyVPH<E>> {};
	template <typename E> class EmptyVPH_P : public TPolygon <HEMeshTriats_EmptyVPH<E>> {};
	template <typename E> class EmptyVPH_H : public THalfEdge<HEMeshTriats_EmptyVPH<E>> {};
	template <typename V> class EmptyEPH_E : public TEdge    <HEMeshTriats_EmptyEPH<V>> {};
	template <typename V> class EmptyEPH_P : public TPolygon <HEMeshTriats_EmptyEPH<V>> {};
	template <typename V> class EmptyEPH_H : public THalfEdge<HEMeshTriats_EmptyEPH<V>> {};

	class EmptyVEPH_V : public TVertex  <HEMeshTriats_EmptyVEPH> {};
	class EmptyVEPH_E : public TEdge    <HEMeshTriats_EmptyVEPH> {};
	class EmptyVEPH_P : public TPolygon <HEMeshTriats_EmptyVEPH> {};
	class EmptyVEPH_H : public THalfEdge<HEMeshTriats_EmptyVEPH> {};
}
