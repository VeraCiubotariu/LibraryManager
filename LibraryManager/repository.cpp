#include "repository.h"
//#include <vector>
#include <assert.h>
#include "errors.h"

void Repository::add(const Book& book) {
	this->books.push_back(book);
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

const Book& Repository::getBook(const int pos) const {
	return this->books[pos];
}

vector<Book> Repository::getAll() const {
	return this->books;
}

const Book& Repository::searchByTitle(const std::string& title) const {
	auto iterator = std::find_if(books.begin(), books.end(), [=](const Book& book) {
		if (book.getTitle() == title) {
			return 1;
		}
		return 0;
		});

	if (iterator == books.end()) {
		throw RepositoryError("Carte inexistenta!\n");
	}

	else {
		return books[iterator - books.begin()];
	}
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
	assert(books.searchByTitle("Title") == a);

	vector<Book> copy = books.getAll();
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

	try {
		books.searchByTitle("Title");
		assert(false);
	}
	catch (RepositoryError error) {
		assert(true);
	}
}

