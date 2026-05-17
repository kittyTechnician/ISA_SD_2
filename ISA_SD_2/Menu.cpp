#include "Menu.h"
#include "Tests.h"
#include <iostream>

using namespace std;

//funkcja do czyszczenia bledow wejscia 
static void clearInput() {
	cin.clear();
	cin.ignore(100, '\n');
}

//funkcja zbierajaca input od uzytkownika
static int menuChoice() {
	int choice;
	while (!(cin >> choice)) {
		clearInput();
		cout << "Niepoprawny wybor, sprobuj ponownie. \n";
	}
	return choice;
}

//funkcja wyswietlajaca menu testow dla wybranej struktury danych
static void testMenu(int method) {
	while (true) {
		cout << "\n--- Wybierz operacje do przetestowania ---\n";
		cout << "1. insert(e, p) (dodanie elementu z losowym priorytetem)\n";
		cout << "2. extract-max() (usuniecie i pobranie maxa)\n";
		cout << "3. find-max() / peek() (podglad elementu max)\n";
		cout << "4. modify-key(e, p) (zmiana priorytetu istniejacego elementu)\n";
		cout << "5. return-size() (pobranie rozmiaru kolejki)\n";
		cout << "6. Wszystkie testy (uruchamia powyzsze po kolei)\n";
		cout << "0. Powrot\n";

		int testChoice = menuChoice();
		if (testChoice == 0) break;

		switch (method) {
		case 1: // Testy dla LinkedList
			switch (testChoice) {
			case 1:
				Test::testLinkedListInsert();
				break;
			case 2:
				Test::testLinkedListExtractMax();
				break;
			case 3:
				Test::testLinkedListFindMax();
				break;
			case 4:
				Test::testLinkedListModifyKey();
				break;
			case 5:
				Test::testLinkedListReturnSize();
				break;
			case 6:
				Test::testLinkedListInsert();
				Test::testLinkedListExtractMax();
				Test::testLinkedListFindMax();
				Test::testLinkedListModifyKey();
				Test::testLinkedListReturnSize();
				break;
			default:
				cout << "Niepoprawny test\n";
				break;
			}
			break;

		case 2: // Testy dla MaxHeap
			switch (testChoice) {
			case 1:
				Test::testHeapInsert();
				break;
			case 2:
				Test::testHeapExtractMax();
				break;
			case 3:
				Test::testHeapFindMax();
				break;
			case 4:
				Test::testHeapModifyKey();
				break;
			case 5:
				Test::testHeapReturnSize();
				break;
			case 6:
				Test::
				Test::testHeapInsert();
				Test::testHeapExtractMax();
				Test::testHeapFindMax();
				Test::testHeapModifyKey();
				Test::testHeapReturnSize();
				break;
			default:
				cout << "Niepoprawny test\n";
				break;
			}
			break;
		}
	}
}

//funkcja wyswietlajaca glowne menu, pozwalajace na wybor struktury danych do testowania
void menu() {
	while (true) {
		cout << "\n--- Wybierz strukture danych do badania ---\n";
		cout << "1. Lista Wiazana\n";
		cout << "2. Kopiec\n";
		cout << "0. Wyjscie\n";

		int methodChoice = menuChoice();
		if (methodChoice == 0) break;
		if (methodChoice >= 1 && methodChoice <= 2) {
			testMenu(methodChoice);
		}
		else {
			cout << "Niepoprawna struktura\n";
		}
	}
}