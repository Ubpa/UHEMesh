#pragma once
#ifndef _UBPA_HEMESH_HEMESH_PTR_H_
#define _UBPA_HEMESH_HEMESH_PTR_H_

#include <type_traits>

namespace Ubpa {
	template<typename T, typename HEMesh_t>
	class HEMesh_ptr {
	public:
		HEMesh_ptr(int idx = -1, HEMesh_t* mesh = nullptr) : idx(idx), mesh(mesh) {}
		HEMesh_ptr(std::nullptr_t) : HEMesh_ptr(-1, nullptr) { }
		T* operator->() const { return mesh->Get<std::remove_const_t<T>>(idx); }
		bool operator==(const HEMesh_ptr& p) const { assert(mesh == p.mesh); return idx == p.idx; }
		bool operator==(std::nullptr_t) const { return idx == -1; }
		bool operator<(const HEMesh_ptr& p) const { assert(mesh == p.mesh); return idx < p.idx; }
		bool operator<(std::nullptr_t) const { return false; }
		bool operator!=(const HEMesh_ptr& p) const { assert(mesh == p.mesh); return idx != p.idx; }
		bool operator!=(std::nullptr_t) const { return idx != -1; }
		HEMesh_ptr& operator=(const HEMesh_ptr& p) { idx = p.idx; mesh = p.mesh; return *this; }
		HEMesh_ptr& operator=(std::nullptr_t) { idx = -1; mesh = nullptr; return *this; }
		operator bool() const { return idx != -1; }
		operator HEMesh_ptr<const T, HEMesh_t>() const { return HEMesh_ptr<const T, HEMesh_t>(idx, mesh); }

	private:
		template<typename>
		friend struct std::hash;
		size_t hash() const { return std::hash<int>()(idx); }

	private:
		template<typename>
		friend class HEMesh;
		template<typename,typename,typename>
		friend class THalfEdge;
		template<typename, typename, typename>
		friend class TVertex;
		template<typename, typename, typename>
		friend class TEdge;
		template<typename, typename, typename>
		friend class TPolygon;
		int idx;
		HEMesh_t* mesh;
	};

	template<template<typename, typename ...> class ContainerT, typename ValT, typename HEMesh_t, typename ... Args>
	ContainerT<HEMesh_ptr<const ValT, HEMesh_t>> Const(const ContainerT<HEMesh_ptr<ValT, HEMesh_t>, Args...>& c) {
		return ContainerT<HEMesh_ptr<const ValT, HEMesh_t>>(c.begin(), c.end());
	}
}

namespace std {
	template<typename T, typename HEMesh_t>
	struct hash<Ubpa::HEMesh_ptr<T, HEMesh_t>> {
		size_t operator()(const Ubpa::HEMesh_ptr<T, HEMesh_t>& p) const {
			return p.hash();
		}
	};
}

#endif // !_UBPA_HEMESH_HEMESH_PTR_H_
