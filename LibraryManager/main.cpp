#include "presentation.h"
#include "validator.h"

void runTests() {
	testValidator();

	testBook();
	testRepository();

	testAdd();
	testModify();
	testRemove();
	testSearch();
	testFilters();
	testSort();
}

int main() {
	runTests();

	Repository repo = Repository();
	Validator val = Validator();
	Service serv = Service(repo, val);
	UI ui = UI(serv);

	ui.runUI();

	return 0;
}