#include "presentation.h"
#include "validator.h"
#define _CRTDBG_MAP_ALLOC
#include <vector>
#include "myVector.h"
#include <assert.h>
#include <iostream>

/*
  Functie folosit in teste
  primeste vector prin valoare -> copy constructor
  returneaza prin valoare -> copy constructor sau move constructor
*/
template <typename MyVector>
MyVector testCopyIterate(MyVector v) {
	int totalPrice = 0;
	for (auto el : v) {
		totalPrice += el.getYear();
	}
	Book p{ "total","tt", "gen", totalPrice};
	v.push_back(p);
	return v;
}

template <typename MyVector>
void addBooks(MyVector& v, int cate) {
	for (int i = 0; i < cate; i++) {
		Book p{ std::to_string(i) + "_type",std::to_string(i) + "_spec", "gen", i + 10};
		v.push_back(p);
	}
}

/*
Testare constructori / assignment
E template pentru a refolosi la diferite variante de VectorDinamic din proiect
*/
template <typename MyVector>
void testCreateCopyAssign() {
	MyVector v;//default constructor
	addBooks(v, 100);
	assert(v.size() == 100);
	assert(v[50].getTitle() == "50_type");

	MyVector v2{ v };//constructor de copiere
	assert(v2.size() == 100);
	assert(v2[50].getTitle() == "50_type");

	MyVector v3;//default constructor
	v3 = v;//operator=   assignment
	assert(v3.size() == 100);
	assert(v3[50].getTitle() == "50_type");

	auto v4 = testCopyIterate(v3);
	assert(v4.size() == 101);
	assert(v4[50].getTitle() == "50_type");
}

/*
  Test pentru move constructor si move assgnment
*/
template <typename MyVector>
void testMoveConstrAssgnment() {
	std::vector<MyVector> v;
	//adaugam un vector care este o variabila temporara
	//se v-a apela move constructor
	v.push_back(MyVector{});

	//inseram, la fel se apeleaza move costructor de la vectorul nostru
	v.insert(v.begin(), MyVector{});

	assert(v.size() == 2);

	MyVector v2;
	addBooks(v2, 50);

	v2 = MyVector{};//move assignment

	assert(v2.size() == 0);

}

template <typename MyVector>
void testAll() {
	testCreateCopyAssign<MyVector>();
	testMoveConstrAssgnment<MyVector>();
}


void runTests() {
	//teste vector
	testAll<MyVector<Book>>();

	testValidator();

	testBook();
	testInMemoryRepo();
	testFileRepo();

	testAdd();
	testModify();
	testRemove();
	testSearch();
	testFilters();
	testSort(); 
	testGenreMap();
	testExportBooks();
	testUndo();

	//teste basket
	testAddClearBasket();
	testGenerateBasket();
	testExportBasket();
}

int main() {
	runTests();

	{
		TList undoList;
		Repository* repo = new InMemoryRepo();
		RepoBasket repoBasket = RepoBasket();

		Validator val = Validator();

		Service serv = Service(undoList, repo, val);
		ServiceBasket servBasket = ServiceBasket(repoBasket, repo);

		UI ui = UI(serv, servBasket);

	//	ui.runUI();
		delete repo;
	}

	_CrtDumpMemoryLeaks();
	return 0;
}