# UHEMesh

> **U**bpa **H**alf-**E**dge **Mesh** 

⭐ Star us on GitHub — it helps!

[![repo-size](https://img.shields.io/github/languages/code-size/Ubpa/UHEMesh?style=flat)](https://github.com/Ubpa/UHEMesh/archive/master.zip) [![tag](https://img.shields.io/github/v/tag/Ubpa/UHEMesh)](https://github.com/Ubpa/UHEMesh/tags) [![license](https://img.shields.io/github/license/Ubpa/UHEMesh)](LICENSE) 

an elegant, high-performance, user-friendly halfedge data structure

## Feature

- Elegant: store **topology** only
- High-performance: **cache-friendly** 
- User-friendly: you can custom `vertex`, `edge` and `polygon` class

## Usage

### default Vertex, Edge and Polygon class

```c++
#include <UHEMesh/HEMesh.h>
#include <vector>
int main() {
    std::vector<size_t> indices = {0,1,2,0,2,3};
    Ubpa::HEMesh<> mesh(indices, 3);
    // ...
}
```

### custom Vertex, Edge and Polygon class

```c++
#include <UHEMesh/HEMesh.h>
#include <vector>
using namespace Ubpa;
// forward declaration
class V;
class E;
class P;
using Traits_VEP = HEMeshTraits<V, E, P>;
// custom vertex, edge and polygon class
class V : public TVertex<Traits_VEP> { /*...*/ }
class E : public TEdge<Traits_VEP> { /*...*/ }
class P : public TPolygon<Traits_VEP> { /*...*/ }
int main() {
    std::vector<size_t> indices = {0,1,2,0,2,3};
    HEMesh<Traits_VEP> mesh(indices, 3);
    // ...
}
```

## Tips

- customed class `T` should have a constructor with default arguments, e.g. `T(argT0 arg0 = val0, ...)` 
- you can get vertex, edge, polygon and halfedge type by `HEMesh<...>::V/E/P/HE` 
- use `EmptyE<V, P>`、`EmptyP<V, E>`、`EmptyEP_E<V>`、`EmptyEP_P<V>` when you don't custom `Edge` or `Polygon` type
- boundary polygon is `nullptr` or use `HEMesh<...>::P::IsBoundary(polygon)` to avoid literal value

