#include "service.h"
#include <assert.h>
#include <typeinfo>
#include <iostream>
#include <string.h>
#include "errors.h"

int Service::searchPos(const std::string& title, const std::string& author) const {
	std::vector<Book> books = repo.getAll();

	for (int i = 0; i < books.size(); i++) {
		if (books[i].getTitle() == title && books[i].getAuthor() == author) {
			return i;
		}
	}

	throw(ServiceError("Carte inexistenta!\n"));
}

void Service::addService(const std::string& title, const std::string& author, const std::string& genre, const int year) {
	Book book = Book(title, author, genre, year);
	val.validateBook(book);
	bool existent = false;

	try {
		searchByTitle(title, author);
		existent = true;
	}
	catch (const ServiceError& error) {
		repo.add(book);
	}

	if (existent) {
		throw(ServiceError("Carte deja in lista!\n"));
	}

}

const std::vector<Book> Service::getAllService() const {
	return this->repo.getAll();
}

void Service::modifyService(const std::string& oldTitle, const std::string& oldAuthor, const std::string& newTitle, const std::string& newAuthor, const std::string& newGenre, const int newYear) {
	Book newBook = Book(newTitle, newAuthor, newGenre, newYear);
	val.validateBook(newBook);
	searchByTitle(oldTitle, oldAuthor);

	repo.modify(searchPos(oldTitle, oldAuthor), newBook);
}

void Service::removeService(const std::string& title, const std::string& author) {
	searchByTitle(title, author);
	repo.remove(searchPos(title, author));
}

const Book& Service::searchByTitle(const std::string& title, const std::string& author) const {
	return repo.getBook(searchPos(title, author));
}

std::vector<Book> Service::standardFilter(std::function<bool(const Book&)> filterCond) {
	auto books = repo.getAll();
	std::vector<Book> res;

	for (int i = 0; i < books.size(); i++) {
		if (filterCond(books[i])) {
			res.push_back(books[i]);
		}
	}

	return res;
}

std::vector<Book> Service::yearFilter(const int year) {
	return standardFilter([=](const Book& book) {
		return book.getYear() == year;
		});
}

std::vector<Book> Service::titleFilter(const std::string& title){
	return standardFilter([=](const Book& book) {
		return book.getTitle() == title;
		});
}

std::vector<Book> Service::standardSort(bool(*lessThan)(const Book& b1, const Book& b2)) {
	auto books = repo.getAll();

	for (int i = 0; i < books.size() - 1; i++) {
		for (int j = i + 1; j < books.size(); j++) {
			if (lessThan(books[j], books[i])) {
				auto aux = books[i];
				books[i] = books[j];
				books[j] = aux;
			}
		}
	}

	return books;
}

std::vector<Book> Service::titleSort() {
	return standardSort([](const Book& b1, const Book& b2) {
		return b1.getTitle() < b2.getTitle(); 
		});
}

std::vector<Book> Service::authorSort() {
	return standardSort([](const Book& b1, const Book& b2) {
		return b1.getAuthor() < b2.getAuthor();
		});
}

std::vector<Book> Service::yearGenreSort() {
	return standardSort([](const Book& b1, const Book& b2) {
		if (b1.getYear() == b2.getYear()) {
			return b1.getGenre() < b2.getGenre();
		}

		return b1.getYear() < b2.getYear();
		});
}

void testAdd() {
	Repository repo = Repository();
	Validator val = Validator();
	Service serv = Service(repo, val);

	assert(repo.booksNumber() == 0);

	serv.addService("My life", "Nobody", "Confession", 2001);
	assert(repo.booksNumber() == 1);
	assert(repo.getBook(0).getTitle() == "My life");

	serv.addService("No longer human", "Osamu Dazai", "Psychological", 1989);
	assert(repo.booksNumber() == 2);
	assert(repo.getBook(1).getYear() == 1989);

	assert(serv.getAllService().size() == 2);

	try {
		serv.addService("", "", "", -90);
		assert(false);
	}
	catch (const ValidationError& error) {
		assert(true);
	}

	try {
		serv.addService("No longer human", "Osamu Dazai", "Psychological", 1999);
		assert(false);
	}
	catch (const ServiceError& error) {
		assert(true);
	} 
}

void testModify() {
	Repository repo = Repository();
	Validator val = Validator();
	Service serv = Service(repo, val);

	serv.addService("My life", "Nobody", "Confession", 2001);
	serv.addService("No longer human", "Osamu Dazai", "Psychological", 1989);

	serv.modifyService("No longer human", "Osamu Dazai", "a", "b", "c", 1000);
	assert(repo.getBook(1) == Book("a", "b", "c", 1000));

	try {
		serv.modifyService("a", "b", "", "", "", 2033);
		assert(false);
	}
	catch (const ValidationError& error) {
		assert(true);
	}

	try {
		serv.modifyService("No longer human", "Osamu Dazai", "a", "b", "c", 1000);
		assert(false);
	}
	catch (const ServiceError& error) {
		assert(true);
	}
}

void testRemove() {
	Repository repo = Repository();
	Validator val = Validator();
	Service serv = Service(repo, val);

	serv.addService("My life", "Nobody", "Confession", 2001);
	serv.addService("No longer human", "Osamu Dazai", "Psychological", 1989);

	serv.removeService("My life", "Nobody");
	assert(repo.booksNumber() == 1);
	assert(repo.getBook(0).getTitle() == "No longer human");

	serv.removeService("No longer human", "Osamu Dazai");
	assert(repo.booksNumber() == 0); 

	try {
		serv.removeService("My life", "Nobody");
		assert(false);
	}
	catch (const ServiceError& error) {
		assert(true);
	}
}

void testSearch() {
	Repository repo = Repository();
	Validator val = Validator();
	Service serv = Service(repo, val);

	serv.addService("My life", "Nobody", "Confession", 2001);
	serv.addService("No longer human", "Osamu Dazai", "Psychological", 1989);

	assert(serv.searchByTitle("My life", "Nobody") == Book("My life", "Nobody", "Confession", 2001));
	assert(serv.searchByTitle("No longer human", "Osamu Dazai") == Book("No longer human", "Osamu Dazai", "Psychological", 1989));

	try {
		serv.searchByTitle("Cool Book", "Not so Cool Author");
		assert(false);
	}
	catch (const ServiceError& error) {
		assert(true);
	}
}

void testFilters() {
	Repository repo = Repository();
	Validator val = Validator();
	Service serv = Service(repo, val);

	serv.addService("My life", "Nobody", "Confession", 2001);
	serv.addService("No longer human", "Osamu Dazai", "Psychological", 1989);
	serv.addService("Mr. Bottle", "Mamma Mia", "Comedy", 2001);
	serv.addService("My life", "Marge Simpson", "Thriller", 2001);
	serv.addService("My life", "Mary Poppins", "Fantasy", 1999);

	auto filteredList = serv.yearFilter(2001);
	assert(filteredList.size() == 3);
	assert(filteredList[0].getAuthor() == "Nobody");
	assert(filteredList[2].getAuthor() == "Marge Simpson");

	filteredList = serv.yearFilter(1989);
	assert(filteredList.size() == 1);

	filteredList = serv.yearFilter(2020);
	assert(filteredList.size() == 0); 

	filteredList = serv.titleFilter("My life");
	assert(filteredList.size() == 3);
	assert(filteredList[2].getAuthor() == "Mary Poppins");

	filteredList = serv.titleFilter("No way");
	assert(filteredList.size() == 0);
}

void testSort() {
	Repository repo = Repository();
	Validator val = Validator();
	Service serv = Service(repo, val);

	serv.addService("Wanna go home", "Nobody", "Confession", 2001);
	serv.addService("No longer human", "Osamu Dazai", "Psychological", 1989);
	serv.addService("Mr. Bottle", "Mamma Mia", "Comedy", 2001);
	serv.addService("No more donuts", "Marge Simpson", "Thriller", 2001);
	serv.addService("My wife", "Mary Poppins", "Fantasy", 1999);

	auto sortedList = serv.titleSort();
	assert(sortedList.size() == 5);
	assert(sortedList[0].getTitle() == "Mr. Bottle");
	assert(sortedList[1].getTitle() == "My wife");
	assert(sortedList[4].getTitle() == "Wanna go home");

	sortedList = serv.authorSort();
	assert(sortedList[0].getAuthor() == "Mamma Mia");
	assert(sortedList[4].getAuthor() == "Osamu Dazai");

	sortedList = serv.yearGenreSort();
	assert(sortedList[0].getGenre() == "Psychological");
	assert(sortedList[1].getGenre() == "Fantasy");
	assert(sortedList[3].getGenre() == "Confession");
}