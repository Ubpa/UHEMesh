# HEMesh

an elegant, high-performance, user-friendly halfedge data structure

## Feature

- Elegant: store **topology** only
- High-performance: **cache-friendly** 
- User-friendly: you can custom `vertex`, `edge` and `polygon` class

## Usage

### default Vertex, Edge and Polygon class

```c++
#include <HEMesh/HEMesh.h>
#include <vector>
int main() {
    std::vector<size_t> indices = {0,1,2,0,2,3};
    Ubpa::HEMesh<> mesh(indices, 3);
    // ...
}
```

### custom Vertex, Edge and Polygon class

```c++
#include <HEMesh/HEMesh.h>
#include <vector>
using namespace Ubpa;
// forward declaration
class V;
class E;
class P;
// custom vertex, edge and polygon class
class V : public TVertex<V, E, P> { /*...*/ }
class E : public TEdge<V, E, P> { /*...*/ }
class P : public TPolygon<V, E, P> { /*...*/ }
int main() {
    std::vector<size_t> indices = {0,1,2,0,2,3};
    HEMesh<V> mesh(indices, 3);
    // ...
}
```

## Tips

- customed class `T` should have a constructor with default arguments, e.g. `T(argT0 arg0 = val0, ...)` 
- you can get pointer type by `HEMesh<...>::ptrXX` or `XX::Ptr` 
- use `EmptyE<V, P>`、`EmptyP<V, E>`、`EmptyEP_E<V>`、`EmptyEP_P<V>` when you don't custom `Edge` or `Polygon` type
- boundary polygon is `nullptr` or use `HEMesh<...>::P::IsBoundary(polygon)` to avoid literal value

