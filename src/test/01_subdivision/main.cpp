#include <UHEMesh/HEMesh.h>
#include <iostream>
#include <string>

using namespace Ubpa;
using namespace std;

class V;
class E;
class P;
using TraitsVEP = HEMeshTraits_EmptyH<V, E, P>;
class V : public TVertex<TraitsVEP> {
public:
	V(const string& name = "NO_NAME") : name(name) {}
	~V() { printf("%s dead\n", name.c_str()); }
public:
	string name;
};
class E : public TEdge<TraitsVEP> {
public:
	E(const string& pre = "E") : pre(pre) {}
	~E() { printf("%s dead\n", pre.c_str()); }
public:
	const string Name() const { return "[" + pre + "]" + HalfEdge()->Origin()->name + "-" + HalfEdge()->End()->name; }
private:
	string pre;
};
class P : public TPolygon<TraitsVEP> {
public:
	P(const string& pre = "P") :pre(pre) {}
	~P() { printf("%s dead\n", pre.c_str()); }
public:
	const string Name() const {
		string name = "[" + pre + "]";
		auto* he = HalfEdge();
		name += he->Origin()->name;
		do {
			name += "-" + he->End()->name;
			he = he->Next();
		} while (he != HalfEdge());
		return name;
	}
private:
	string pre;
};

ostream& operator<< (ostream& os, V* v) {
	os << v->name;
	return os;
}

ostream& operator<< (ostream& os, HEMesh<TraitsVEP>::H * he) {
	os << he->Origin() << "->" << he->End();
	return os;
}

void Print(shared_ptr<HEMesh<TraitsVEP>> mesh) {
	cout << (mesh->IsValid() ? "[valid]" : "[not valid]") << endl;
	cout << " V:" << mesh->Vertices().size() << endl;
	for (auto* v : mesh->Vertices())
		cout << "    " << v->name << endl;

	cout << "HE:" << mesh->HalfEdges().size() << endl;
	for (auto* he : mesh->HalfEdges())
		cout << "    " << he << endl;

	cout << " E:" << mesh->Edges().size() << endl;
	for (auto* e : mesh->Edges())
		cout << "    " << e->Name() << endl;

	cout << " P:" << mesh->Polygons().size() << endl << endl;
	for (auto* p : mesh->Polygons())
		cout << "    " << p->Name() << endl;

	cout << " B:" << mesh->Boundaries().size() << endl;
	for (auto* b : mesh->Boundaries()) {
		cout << "    ";

		for (auto* he : b->NextLoop())
			cout << he->Origin() << "-";
		cout << b->Origin() << endl;
	}
	cout << endl;
}

int main() {
	auto mesh = make_shared<HEMesh<TraitsVEP>>();
	cout << "add V0, V1, V2" << endl;

	auto* v0 = mesh->AddVertex("V0");
	auto* v1 = mesh->AddVertex("V1");
	auto* v2 = mesh->AddVertex("V2");
	Print(mesh);
	cout << "add E01, E12, E21" << endl;
	auto* e01 = mesh->AddEdge(v0, v1, "E01");
	auto* e12 = mesh->AddEdge(v1, v2, "E12");
	auto* e20 = mesh->AddEdge(v2, v0, "E20");
	Print(mesh);

	auto* v3 = mesh->AddEdgeVertex(e01, "V3");
	auto* v4 = mesh->AddEdgeVertex(e12, "V4");
	auto* v5 = mesh->AddEdgeVertex(e20, "V5");

	auto* e34 = mesh->AddEdge(v3, v4, "E34");
	auto* e45 = mesh->AddEdge(v4, v5, "E45");
	auto* e53 = mesh->AddEdge(v5, v3, "E53");

	mesh->AddPolygon({ e34->HalfEdge(), e45->HalfEdge(), e53->HalfEdge() }, "P345");
	mesh->AddPolygon({ v4->HalfEdgeTo(v3), v3->HalfEdgeTo(v1), v1->HalfEdgeTo(v4) }, "P431");
	mesh->AddPolygon({ v5->HalfEdgeTo(v4), v4->HalfEdgeTo(v2), v2->HalfEdgeTo(v5) }, "P542");
	mesh->AddPolygon({ v3->HalfEdgeTo(v5), v5->HalfEdgeTo(v0), v0->HalfEdgeTo(v3) }, "P350");
	Print(mesh);

	return 0;
}
