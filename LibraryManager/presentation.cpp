#include <iostream>
#include "presentation.h"
#include "errors.h"

using std::cin;
using std::cout;

void UI::printMenu() {
	cout << "\nCarti in cos: " << basket.size() << "\n\n";
	cout << "1. Adauga carte\n2. Afiseaza toate cartile\n3. Modifica carte\n4. Sterge carte\n5. Cauta carte\n6. Filtreaza dupa an\n7. Filtreaza dupa nume\n8. Sorteaza dupa titlu\n9. Sorteaza dupa autor\na. Sorteaza dupa an + gen\nb. Adauga in cos\nc. Goleste cos\nd. Genereaza cos\ne. Exporta cos\n0. Iesire\n\nIntrodu comanda: ";
}

void UI::addUI() {
	std::string title, author, genre;
	int year;
	cout << "Introdu titlul: ";
	cin >> title;

	cout << "Introdu autorul: ";
	cin >> author;

	cout << "Introdu genul: ";
	cin >> genre;

	cout << "Introdu anul: ";
	cin >> year;

	try {
		this->serv.addService(title, author, genre, year);
		cout << "Carte adaugata cu succes!\n\n";
	}
	catch (StandardError& error) {
		cout << error.getMessage() << "\n";
	}
}

void UI::printAll(const vector<Book>& books) {
	for (auto book:books) {
		cout << book.toString();
	}
}

void UI::modifyUI() {
	std::string oldTitle, oldAuthor, newTitle, newAuthor, newGenre;
	int newYear;
	
	cout << "Titlu vechi: ";
	cin >> oldTitle;

	cout << "Autor vechi: ";
	cin >> oldAuthor;

	cout << "Titlu nou: ";
	cin >> newTitle;

	cout << "Autor nou: ";
	cin >> newAuthor;

	cout << "Gen nou: ";
	cin >> newGenre;

	cout << "An nou: ";
	cin >> newYear;

	try {
		serv.modifyService(oldTitle, oldAuthor, newTitle, newAuthor, newGenre, newYear);
		cout << "Carte modificata cu succes!\n\n";
	}
	catch (StandardError& error) {
		cout << error.getMessage() << "\n";
	}
}

void UI::removeUI() {
	std::string title, author;
	cout << "Titlu: ";
	cin >> title;

	cout << "Autor: ";
	cin >> author;
	
	try {
		serv.removeService(title, author);
		cout << "Carte stearsa cu succes!\n\n";
	}
	catch (StandardError& error) {
		cout << error.getMessage() << "\n";
	}
}

void UI::searchUI() {
	std::string title, author;
	cout << "Titlu: ";
	cin >> title;

	cout << "Autor: ";
	cin >> author;

	try {
		cout << serv.searchByTitleAuthor(title, author).toString();
	}
	catch (StandardError& error) {
		cout << error.getMessage() << "\n";
	}
}

void UI::yearFilterUI() {
	int year;
	cout << "An: ";
	cin >> year;

	auto filteredList = serv.yearFilter(year);
	printAll(filteredList);
}

void UI::titleFilterUI() {
	std::string title;
	cout << "Titlu: ";
	cin >> title;

	auto filteredList = serv.titleFilter(title);
	printAll(filteredList);
}

void UI::titleSortUI() {
	auto sortedList = serv.titleSort();
	printAll(sortedList);
}

void UI::authorSortUI() {
	auto sortedList = serv.authorSort();
	printAll(sortedList);
}

void UI::yearGenreSortUI() {
	auto sortedList = serv.yearGenreSort();
	printAll(sortedList);
}

void UI::addBasketUI() {
	std::string title;
	cout << "Titlu: ";
	cin >> title;

	try {
		basket.addInBasket(title);
		printAll(basket.getAll());
	}
	catch (RepositoryError error) {
		cout << error.getMessage();
	}
}

void UI::clearBasketUI() {
	basket.clearBasket();
}

void UI::generateBasketUI() {
	cout << "Numar de carti de generat: ";
	int nr;
	cin >> nr;

	try {
		basket.generateBasket(nr);
		printAll(basket.getAll());
	}
	catch (ServiceError error) {
		cout << error.getMessage();
	}
}

void UI::exportBasketUI() {
	std::string fileName;
	cout << "Numele fisierului: ";
	cin >> fileName;

	int fileType;
	cout << "[0]CVS [1]HTML: ";
	cin >> fileType;

	try {
		basket.exportBasket(fileName, fileType);
		cout << "Cos exportat cu succes!\n";
	}
	catch (ServiceError error) {
		cout << error.getMessage();
	}
}

void UI::runUI() {
	bool running = true;
	while (running) {
		printMenu();
		char cmd;
		cin >> cmd;

		switch (cmd) {
		case '1':
			addUI();
			break;
		case '2':
			printAll(serv.getAllService());
			break;
		case '3':
			modifyUI();
			break;
		case '4':
			removeUI();
			break;
		case '5':
			searchUI();
			break;
		case '6':
			yearFilterUI();
			break;
		case '7':
			titleFilterUI();
			break;
		case '8':
			titleSortUI();
			break;
		case '9':
			authorSortUI();
			break;
		case 'a':
			yearGenreSortUI();
			break;
		case 'b':
			addBasketUI();
			break;
		case 'c':
			clearBasketUI();
			break;
		case 'd':
			generateBasketUI();
			break;
		case 'e':
			exportBasketUI();
			break;
		case '0':
			running = false;
			break;
		default:
			cout << "Comanda invalida!\n\n";
			break;
		}
	}
} 