# UHEMesh

> **U**bpa **H**alf-**E**dge **Mesh** 

⭐ Star us on GitHub — it helps!

[![repo-size](https://img.shields.io/github/languages/code-size/Ubpa/UHEMesh?style=flat)](https://github.com/Ubpa/UHEMesh/archive/master.zip) [![tag](https://img.shields.io/github/v/tag/Ubpa/UHEMesh)](https://github.com/Ubpa/UHEMesh/tags) [![license](https://img.shields.io/github/license/Ubpa/UHEMesh)](LICENSE) 

an elegant, high-performance, user-friendly halfedge data structure

## Feature

- Elegant: store **topology** only
- High-performance: **cache-friendly** 
- User-friendly: you can custom **Vertex, Edge, Polygon and Half-Edge** class

## Usage

### default Vertex, Edge, Polygon and Half-Edge class

```c++
#include <UHEMesh/HEMesh.h>
#include <vector>
int main() {
    std::vector<size_t> indices = {0,1,2,0,2,3};
    Ubpa::HEMesh<> mesh(indices, 3);
    // ...
}
```

### custom Vertex, Edge, Polygon and Half-Edge class

```c++
#include <UHEMesh/HEMesh.h>
#include <vector>
using namespace Ubpa;
// forward declaration
class V;
class E;
class P;
class H;
using Traits_VEPH = HEMeshTraits<V, E, P, H>;
// custom vertex, edge, polygon and half-edge class
class V : public TVertex  <Traits_VEPH> { /*...*/ }
class E : public TEdge    <Traits_VEPH> { /*...*/ }
class P : public TPolygon <Traits_VEPH> { /*...*/ }
class H : public THalfEdge<Traits_VEPH> { /*...*/ }
int main() {
    std::vector<size_t> indices = {0,1,2,0,2,3};
    HEMesh<Traits_VEPH> mesh(indices, 3);
    // ...
}
```

## Tips

- customed class `T` should `std::is_default_constructibl` 

- you can get vertex, edge, polygon and halfedge type by `HEMesh<...>::V/E/P/HE` 

- use `Empty*_*` type if you don't need to custom some class, see [Empty.h](include/UHEMesh/Empty.h) for more details.

  > **example** 
  >
  > if you just need to custom vertex and polygon, so you can do like this
  >
  > ```c++
  > class V;
  > class P;
  > using Traits_VP = HEMeshTriats_EmptyEH<V, P>;
  > class V : public TVertex <Traits_VP> { /*...*/ }
  > class P : public TPolygon<Traits_VP> { /*...*/ }
  > 
  > int main() {
  >     std::vector<size_t> indices = {0,1,2,0,2,3};
  >     HEMesh<Traits_VP> mesh(indices, 3);
  >     // ...
  > }
  > ```

- boundary polygon is `nullptr` or use `HEMesh<...>::P::IsBoundary(polygon)` to avoid literal value

