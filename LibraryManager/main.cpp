#include "presentation.h"

void runTests() {
	testBook();
	testRepository();

	testAdd();
	testModify();
	testRemove();
	testSearch();
}

int main() {
	runTests();

	Repository repo = Repository();
	Service serv = Service(repo);
	UI ui = UI(serv);

	//ui.runUI();

	return 0;
}