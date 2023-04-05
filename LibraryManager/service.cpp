#include "service.h"
#include <assert.h>

int Service::searchPos(const std::string& title) const {
	std::vector<Book> books = repo.getAll();

	for (int i = 0; i < books.size(); i++) {
		if (books[i].getTitle() == title) {
			return i;
		}
	}
}

void Service::addService(const std::string& title, const std::string& author, const std::string& genre, const int year) {
	Book book = Book(title, author, genre, year);
	repo.add(book);
}

const std::vector<Book> Service::getAllService() const {
	return this->repo.getAll();
}

void Service::modifyService(const std::string& oldTitle, const std::string& newTitle, const std::string& newAuthor, const std::string& newGenre, const int newYear) {
	Book newBook = Book(newTitle, newAuthor, newGenre, newYear);
	repo.modify(searchPos(oldTitle), newBook);
}

void Service::removeService(const std::string& title) {
	repo.remove(searchPos(title));
}

Book Service::searchByTitle(const std::string& title) const{
	return repo.getBook(searchPos(title));
}

void testAdd() {
	Repository repo = Repository();
	Service serv = Service(repo);
	assert(repo.booksNumber() == 0);

	serv.addService("My life", "Nobody", "Confession", 2001);
	assert(repo.booksNumber() == 1);
	assert(repo.getBook(0).getTitle() == "My life");

	serv.addService("No longer human", "Osamu Dazai", "Psychological", 1989);
	assert(repo.booksNumber() == 2);
	assert(repo.getBook(1).getYear() == 1989);

	assert(serv.getAllService().size() == 2);
}

void testModify() {
	Repository repo = Repository();
	Service serv = Service(repo);

	serv.addService("My life", "Nobody", "Confession", 2001);
	serv.addService("No longer human", "Osamu Dazai", "Psychological", 1989);

	serv.modifyService("No longer human", "a", "b", "c", 1000);
	assert(repo.getBook(1) == Book("a", "b", "c", 1000));
}

void testRemove() {
	Repository repo = Repository();
	Service serv = Service(repo);

	serv.addService("My life", "Nobody", "Confession", 2001);
	serv.addService("No longer human", "Osamu Dazai", "Psychological", 1989);

	serv.removeService("My life");
	assert(repo.booksNumber() == 1);
	assert(repo.getBook(0).getTitle() == "No longer human");

	serv.removeService("No longer human");
	assert(repo.booksNumber() == 0);
}

void testSearch() {
	Repository repo = Repository();
	Service serv = Service(repo);

	serv.addService("My life", "Nobody", "Confession", 2001);
	serv.addService("No longer human", "Osamu Dazai", "Psychological", 1989);

	assert(serv.searchByTitle("My life") == Book("My life", "Nobody", "Confession", 2001));
	assert(serv.searchByTitle("No longer human") == Book("No longer human", "Osamu Dazai", "Psychological", 1989));
}