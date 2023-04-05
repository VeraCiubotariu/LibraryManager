#include "repository.h"
#include <vector>
#include <assert.h>

void Repository::add(const Book& book) {
	this->books.emplace_back(book);
}

void Repository::modify(const int pos, const Book& newBook) {
	books[pos].setTitle(newBook.getTitle());
	books[pos].setAuthor(newBook.getAuthor());
	books[pos].setGenre(newBook.getGenre());
	books[pos].setYear(newBook.getYear());
}

void Repository::remove(const int pos) {
	modify(pos, books[books.size() - 1]);
	books.pop_back();
}

int Repository::booksNumber() const {
	return this->books.size();
}

Book Repository::getBook(const int pos) const {
	return this->books[pos];
}

const std::vector<Book> Repository::getAll() const {
	//std::vector<Book> res;
	//res = this->books;
	//return res;
	return this->books;
}

void testRepository() {
	Repository books = Repository();
	assert(books.booksNumber() == 0);
	Book a = Book("Title", "Author", "Genre", 2005);

	books.add(a);
	assert(books.booksNumber() == 1);
	assert(books.getBook(0) == a);

	Book b = Book("Other", "Cool dude", "Horror", 1987);
	books.add(b);
	assert(books.booksNumber() == 2);
	assert(books.getBook(1) == b);

	std::vector<Book> copy = books.getAll();
	assert(copy[0] == a);
	assert(copy[1] == b);
	assert(copy.size() == 2);

	Book c = Book("No longer human", "Osamu Dazai", "Psychological", 1978);
	books.modify(0, c);
	assert(books.getBook(0) == c);

	books.remove(0);
	assert(books.booksNumber() == 1);
	assert(books.getBook(0) == b);

	books.remove(0);
	assert(books.booksNumber() == 0);
}

