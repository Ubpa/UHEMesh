#pragma once
#ifndef _UBPA_HEMESH_FORWARDDECL_H_
#define _UBPA_HEMESH_FORWARDDECL_H_

#include <vector>
#include <set>

#include <assert.h>

namespace Ubpa {
	template<typename V, typename E, typename P>
	class THalfEdge;
	template<typename V, typename E, typename P>
	class TVertex;
	template<typename V, typename E, typename P>
	class TEdge;
	template<typename V, typename E, typename P>
	class TPolygon;

	template<typename V>
	class _enable_HEMesh;
	template<typename V>
	class HEMesh;

	template <typename E, typename P>
	class EmptyV;
	template <typename V, typename E>
	class EmptyP;
	template <typename V, typename P>
	class EmptyE;

	template <typename V>
	class EmptyEP_E;
	template <typename V>
	class EmptyEP_P;

	class AllEmpty;

	template<typename T, typename HEMesh_t>
	class HEMesh_ptr;
}

#endif // !_UBPA_HEMESH_FORWARDDECL_H_
