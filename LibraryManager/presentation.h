#pragma once
#include "service.h"
#include "serviceBasket.h"

class UI {
private:
	Service& serv;
	ServiceBasket& basket;
public:
	/// <summary>
	/// Constructor of the class
	/// </summary>
	/// <param name="serv"> Service </param>
	UI(Service& serv, ServiceBasket& servBasket) noexcept : serv{ serv }, basket{ servBasket } {
	};

	/// <summary>
	/// Prints the menu
	/// </summary>
	void printMenu();

	/// <summary>
	/// Reads the input and adds the book to the list
	/// </summary>
	void addUI();

	/// <summary>
	/// Reads the input and modifies the given book
	/// </summary>
	void modifyUI();

	/// <summary>
	/// Reads the input  and removes the given book
	/// </summary>
	void removeUI();

	/// <summary>
	/// Reads the input and returns the book with the given title from the list
	/// </summary>
	void searchUI();

	/// <summary>
	/// Reads the input and filters the books by the year given
	/// </summary>
	void yearFilterUI();

	/// <summary>
	/// Reads the input and filters the books by the title given
	/// </summary>
	void titleFilterUI();

	/// <summary>
	/// Sorts the list of books by their titles and prints them
	/// </summary>
	void titleSortUI();

	/// <summary>
	/// Sorts the list of books by their authors and prints them
	/// </summary>
	void authorSortUI();

	/// <summary>
	/// Sorts the list of books by their year and then genre and prints them
	/// </summary>
	void yearGenreSortUI();

	/// <summary>
	/// Adds an item to the basket and prints the basket
	/// </summary>
	void addBasketUI();

	/// <summary>
	/// Clears the basket
	/// </summary>
	void clearBasketUI();

	/// <summary>
	/// Generates a random basket and prints it
	/// </summary>
	void generateBasketUI();

	/// <summary>
	/// Exports the current basket
	/// </summary>
	void exportBasketUI();

	/// <summary>
	/// Prints all the books
	/// </summary>
	void printAll(const vector<Book>& books);

	/// <summary>
	/// Runs the interface
	/// </summary>
	void runUI();

};