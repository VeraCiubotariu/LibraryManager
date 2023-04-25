#pragma once
#include <vector>
using std::vector;
#include "book.h"
//#include "myVector.h"

class Repository {
protected:
	vector<Book> books;

public:
	/// <summary>
	/// Adds the book to the list
	/// </summary>
	/// <param name="book"> Book </param>
	void add(const Book& book);

	/// <summary>
	/// Changes the book from the pos position in the list with newBook
	/// </summary>
	/// <param name="pos"> int </param>
	/// <param name="newBook"> Book </param>
	void modify(const int pos, const Book& newBook);

	/// <summary>
	/// Removes the book from the position pos from the list
	/// </summary>
	/// <param name="pos"> int </param>
	void remove(const int pos);

	/// <summary>
	/// Returns the number of books in the list
	/// </summary>
	/// <returns> int </returns>
	int booksNumber() const;

	/// <summary>
	/// Returns the book with the given title from the list
	/// </summary>
	/// <param name="pos"> int </param>
	/// <returns> Book </returns>
	const Book& getBook(const int pos) const;

	/// <summary>
	/// Returns all the books from the list
	/// </summary>
	/// <returns> vector<Book> </returns>
	vector<Book> getAll() const;

	/// <summary>
	/// Returns the book with the given title. Raises exception if the book doesn't exist
	/// </summary>
	/// <param name="title"> string </param>
	/// <returns> Book </returns>
	/// <raises> RepositoryError, if the book doesn't exist </raises>
	const Book& searchByTitle(const std::string& title) const;
};

void testRepository();