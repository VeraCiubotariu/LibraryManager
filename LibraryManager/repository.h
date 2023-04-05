#pragma once
#include <vector>
#include "book.h"

class Repository {
private:
	std::vector<Book> books;

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
	Book getBook(const int pos) const;

	/// <summary>
	/// Returns all the books from the list
	/// </summary>
	/// <returns> vector<Book> </returns>
	const std::vector<Book> getAll() const;
};

void testRepository();