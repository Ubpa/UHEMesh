#pragma once

#include <vector>
#include <set>
#include <type_traits>

#include <cassert>

#include "../HEMeshTriats.h"

namespace Ubpa {
	template<typename V, typename E, typename P> struct HEMeshTriats;

	template<typename Traits> class THalfEdge;
	template<typename Traits> class TVertex;
	template<typename Traits> class TEdge;
	template<typename Traits> class TPolygon;

	template<typename Traits> class HEMesh;

	template <typename E, typename P> class EmptyV;
	template <typename V, typename P> class EmptyE;
	template <typename V, typename E> class EmptyP;

	template <typename P> class EmptyVE_V;
	template <typename P> class EmptyVE_E;
	template <typename E> class EmptyVP_V;
	template <typename E> class EmptyVP_P;
	template <typename V> class EmptyEP_E;
	template <typename V> class EmptyEP_P;

	class EmptyVEP_V;
	class EmptyVEP_E;
	class EmptyVEP_P;

	template<template<typename, typename ...> class ContainerT, typename ElemT, typename ... Args>
	const ContainerT<const ElemT*> Const(const ContainerT<ElemT*, Args...>& container) {
		return ContainerT<const ElemT*>(container.begin(), container.end());
	}
}
