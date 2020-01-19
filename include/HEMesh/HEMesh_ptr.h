#pragma once
#ifndef _UBPA_HEMESH_HEMESH_PTR_H_
#define _UBPA_HEMESH_HEMESH_PTR_H_

#include <type_traits>

namespace Ubpa {
	template<typename T, typename HEMesh_t>
	class HEMesh_ptr {
	public:
		HEMesh_ptr(HEMesh_t* mesh = nullptr, int idx = -1) : mesh(mesh), idx(idx) {}
		T* operator->() const { return mesh->Get<std::remove_const_t<T>>(idx); }
		bool operator==(const HEMesh_ptr& p) const { assert(mesh == p.mesh); return idx == p.idx; }
		bool operator==(std::nullptr_t) const { return idx == -1; }
		bool operator<(const HEMesh_ptr& p) const { assert(mesh == p.mesh); return idx < p.idx; }
		bool operator!=(const HEMesh_ptr& p) const { assert(mesh == p.mesh); return idx != p.idx; }
		bool operator!=(std::nullptr_t) const { return idx != -1; }
		HEMesh_ptr& operator=(const HEMesh_ptr& p) { mesh = p.mesh; idx = p.idx; return *this; }
		HEMesh_ptr& operator=(std::nullptr_t) { mesh = nullptr; idx = -1; return *this; }
		operator bool() const { return idx != -1; }
		operator HEMesh_ptr<const T, HEMesh_t>() const { return HEMesh_ptr<const T, HEMesh_t>(mesh, idx); }

	private:
		template<typename>
		friend struct std::hash;
		size_t hash() const { return std::hash<int>()(idx); }

	private:
		template<typename V>
		friend class HEMesh;
		HEMesh_t* mesh;
		int idx;
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
