#include <iostream>
#include "presentation.h"

using std::cin;
using std::cout;

void UI::printMenu() {
	cout << "1. Adauga carte\n2. Afiseaza toate cartile\n3. Modifica carte\n4. Sterge carte\n5. Cauta carte\n0. Iesire\n\nIntrodu comanda: ";
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

	this->serv.addService(title, author, genre, year);
	cout << "Carte adaugata cu succes!\n\n";
}

void UI::printAll() {
	std::vector<Book> books = this->serv.getAllService();
	for (int i = 0; i < books.size(); i++) {
		cout << books[i].toString();
	}
}

void UI::modifyUI() {
	std::string oldTitle, newTitle, newAuthor, newGenre;
	int newYear;
	
	cout << "Titlu vechi: ";
	cin >> oldTitle;

	cout << "Titlu nou: ";
	cin >> newTitle;

	cout << "Autor nou: ";
	cin >> newAuthor;

	cout << "Gen nou: ";
	cin >> newGenre;

	cout << "An nou: ";
	cin >> newYear;

	serv.modifyService(oldTitle, newTitle, newAuthor, newGenre, newYear);
	cout << "Carte modificata cu succes!\n\n";
}

void UI::removeUI() {
	std::string title;
	cout << "Titlu: ";
	cin >> title;
	
	serv.removeService(title);
	cout << "Carte stearsa cu succes!\n\n";
}

void UI::searchUI() {
	std::string title;
	cout << "Titlu: ";
	cin >> title;

	cout << serv.searchByTitle(title).toString();
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
			printAll();
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
		case '0':
			running = false;
			break;
		default:
			cout << "Comanda invalida!\n\n";
			break;
		}
	}
} 