#pragma once
#include "repository.h"

class RepoBasket :public Repository {
public:
	void clear() {
		books.clear();
	}
};