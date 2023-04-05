#pragma once
#include "repository.h"

class Service {
private:
	Repository& repo;

public:
	/// <summary>
	/// The constructor of the class
	/// </summary>
	/// <param name="books"> Repository </param>
	Service(Repository& books) : repo{ books } {
	};

	/// <summary>
	/// Returns the list of books
	/// </summary>
	/// <returns> vector<Book> </returns>
	const std::vector<Book> getAllService() const;

	/// <summary>
	/// Searches the book with the given name and returns its position in the list
	/// </summary>
	/// <param name="name"> string </param>
	/// <returns> int </returns>
	int searchPos(const std::string& name) const;

	/// <summary>
	/// Adds the book with the given properties to the list
	/// </summary>
	/// <param name="title"> string </param>
	/// <param name="author"> string </param>
	/// <param name="genre"> string </param>
	/// <param name="year"> int </param>
	void addService(const std::string& title, const std::string& author, const std::string& genre, const int year);

	/// <summary>
	/// Modifies the properties of the given book with the new ones
	/// </summary>
	/// <param name="oldTitle"> string </param>
	/// <param name="newTitle"> string </param>
	/// <param name="newAuthor"> string </param>
	/// <param name="newGenre"> string </param>
	/// <param name="newYear"> int </param>
	void modifyService(const std::string& oldTitle, const std::string& newTitle, const std::string& newAuthor, const std::string& newGenre, const int newYear);

	/// <summary>
	/// Removes the books with the given title from the list
	/// </summary>
	/// <param name="title"> string </param>
	void removeService(const std::string& title);

	/// <summary>
	/// Searches the book with the given title in the list and returns it
	/// </summary>
	/// <param name="title"> string </param>
	/// <returns> Book </returns>
	Book searchByTitle(const std::string& title) const;
};

void testAdd();
void testModify();
void testRemove();
void testSearch();