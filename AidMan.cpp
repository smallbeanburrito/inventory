/*
Final Project Milestone 5 6
Keith Cao
143332211
Apr. 11, 2022
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include "AidMan.h"
#include "Item.h"
#include "Perishable.h"
namespace sdds {
	AidMan::AidMan() : Menu("1- List Items\n2- Add Item\n3- Remove Item\n4- Update Quantity\n5- Sort\n6- Ship Items\n7- New/Open Aid Database\n---------------------------------\n", 7) {
		a_filename = nullptr;
		a_numProducts = 0;
	}
	unsigned int AidMan::menu() {
		int day, month, year;
		ut.getSystemDate(&year, &month, &day);
		char filename[51];
		if (a_filename == nullptr) {
			strcpy(filename, "No file");
		}
		else {
			strcpy(filename, a_filename);
		}
		cout << "Aid Management System" << endl;
		cout << "Date: " << year << '/';
		cout.width(2);
		cout.fill('0');
		cout << month << '/';
		cout.width(2);
		cout.fill('0');
		cout << day << endl;
		cout << "Data file: " << filename << endl;
		cout << "---------------------------------" << endl;
		return Menu::run();
	}
	AidMan::~AidMan() {
		deallocate();
	}
	void AidMan::run() {
		int option = -1;
		while (option != 0) {
			option = menu();
			if (a_filename == nullptr && option != 0) {
				option = 7;
			}
			if (option == 0) {
				cout << "Exiting Program!" << endl;
			}
			else if (option == 1) {
				cout << "\n****List Items****" << endl;
				list();
			}
			else if (option == 2) {
				cout << "\n****Add Item****" << endl;
				addItem();
			}
			else if (option == 3) {
				cout << "\n****Remove Item****" << endl;
				removeItem();
			}
			else if (option == 4) {
				cout << "\n****Update Quantity****" << endl;
				updateQty();
			}
			else if (option == 5) {
				cout << "\n****Sort****" << endl;
				sort();
			}
			else if (option == 6) {
				cout << "\n****Ship Items****" << endl;
				shipItem();
			}
			else if (option == 7) {
				cout << "\n****New/Open Aid Database****" << endl;
				load();
			}
		}
		save();
	}
	void AidMan::save() {
		if (a_filename != nullptr) {
			ofstream ofstr(a_filename, ios::trunc);
			for (int i = 0; i < a_numProducts; i++) {
				a_products[i]->save(ofstr);
				ofstr << '\n';
			}
		}
	}
	void AidMan::deallocate() {
		for (int i = 0; i < a_numProducts; i++) {
			delete a_products[i];
			a_products[i] = nullptr;
		}
		delete[] a_filename;
		a_filename = nullptr;
		a_numProducts = 0;
	}
	bool AidMan::load() {
		char tempFile[51];
		int loaded = 0;
		save();
		cout << "Enter file name: ";
		std::cin >> tempFile;
		a_filename = new char[strlen(tempFile) + 1];
		strcpy(a_filename, tempFile);
		deallocate();
		a_filename = new char[strlen(tempFile) + 1];
		strcpy(a_filename, tempFile);
		ifstream in(a_filename);
		if (in.is_open()) {
			while (in) {
				int pori = in.peek()-48;
				if (pori <= 3 && pori >= 1) {
					a_products[a_numProducts] = new Perishable;
					a_products[a_numProducts]->load(in);
					if (a_products[a_numProducts]) {
						a_numProducts++;
						loaded++;
					}
					else {
						delete a_products[a_numProducts];
						a_products[a_numProducts] = nullptr;
					}
				}
				else if (pori <= 9 && pori >= 4) {
					a_products[a_numProducts] = new Item;
					a_products[a_numProducts]->load(in);
					if (a_products[a_numProducts]) {
						a_numProducts++;
						loaded++;
					}
					else {
						delete a_products[a_numProducts];
						a_products[a_numProducts] = nullptr;
					}
				}
				else {
					in.setstate(ios::failbit);
				}
			}
			cout << loaded << " records loaded!\n" << endl;
		}
		else {
			cout << "Failed to open " << a_filename << " for reading!" << endl;
			cout << "1 - Yes!\n0- Exit\n>";
			if (ut.getint(0, 1) == 1) {
				ofstream(a_filename);
			}
		}
		return loaded;
	}
	int AidMan::list(const char* sub_desc) {
		int rows = 0;
		int* rowNum = nullptr;
		rowNum = new int[a_numProducts + 1];
		if (sub_desc == nullptr) {
			cout << " ROW " << "| " << " SKU " << " |";
			cout.setf(ios::left);
			cout.width(36);
			cout.fill(' ');
			cout << " Description" << " |";
			cout << " Have " << '|' << " Need " << "| " << " Price " << " |" << " Expiry" << endl;
			cout.unsetf(ios::left);
			cout.width(6);
			cout.fill('-');
			cout << '+';
			cout.width(8);
			cout.fill('-');
			cout << '+';
			cout.width(38);
			cout.fill('-');
			cout << '+';
			cout.width(7);
			cout.fill('-');
			cout << '+';
			cout.width(7);
			cout.fill('-');
			cout << '+';
			cout.width(10);
			cout.fill('-');
			cout << '+';
			cout.width(11);
			cout.fill('-');
			cout << '-' << endl;
			for (int i = 0; i < a_numProducts; i++) {
				cout.width(4);
				cout.fill(' ');
				cout << rows+1 << " | ";
				a_products[i]->linear(true);
				a_products[i]->display(cout);
				cout << '\n';
				rowNum[rows++] = i;
			}
			cout.width(6);
			cout.fill('-');
			cout << '+';
			cout.width(8);
			cout.fill('-');
			cout << '+';
			cout.width(38);
			cout.fill('-');
			cout << '+';
			cout.width(7);
			cout.fill('-');
			cout << '+';
			cout.width(7);
			cout.fill('-');
			cout << '+';
			cout.width(10);
			cout.fill('-');
			cout << '+';
			cout.width(11);
			cout.fill('-');
			cout << '-' << endl;
			if (rows == 0) {
				cout << "The list is empty!" << endl;
			}
			else {
				cout << "Enter row number to display details or <ENTER> to continue:\n> ";
				std::cin.ignore(2000, '\n');
				int enter = std::cin.get();
				if (enter == 10) {
					// exit
				}
				else {
					a_products[rowNum[enter - 49]]->linear(false);
					a_products[rowNum[enter - 49]]->display(cout);
					cout << '\n';
				}
				cout << '\n';
			}
		}
		else {
			cout << " ROW " << "| " << " SKU " << " |";
			cout.setf(ios::left);
			cout.width(36);
			cout.fill(' ');
			cout << " Description" << " |";
			cout << " Have " << '|' << " Need " << "| " << " Price " << " |" << " Expiry" << endl;
			cout.unsetf(ios::left);
			cout.width(6);
			cout.fill('-');
			cout << '+';
			cout.width(8);
			cout.fill('-');
			cout << '+';
			cout.width(38);
			cout.fill('-');
			cout << '+';
			cout.width(7);
			cout.fill('-');
			cout << '+';
			cout.width(7);
			cout.fill('-');
			cout << '+';
			cout.width(10);
			cout.fill('-');
			cout << '+';
			cout.width(11);
			cout.fill('-');
			cout << '-' << endl;
			for (int i = 0; i < a_numProducts; i++) {
				if (*a_products[i] == sub_desc) {
					cout.width(4);
					cout.fill(' ');
					cout << rows + 1 << " | ";
					a_products[i]->linear(true);
					a_products[i]->display(cout);
					rowNum[rows] = i;
					cout << '\n';
				}
				rows++;
			}
			cout.width(6);
			cout.fill('-');
			cout << '+';
			cout.width(8);
			cout.fill('-');
			cout << '+';
			cout.width(38);
			cout.fill('-');
			cout << '+';
			cout.width(7);
			cout.fill('-');
			cout << '+';
			cout.width(7);
			cout.fill('-');
			cout << '+';
			cout.width(10);
			cout.fill('-');
			cout << '+';
			cout.width(11);
			cout.fill('-');
			cout << '-' << endl;
			if (rows == 0) {
				cout << "The list is empty!" << endl;
			}
		}
		delete[] rowNum;
		rowNum = nullptr;
		return rows;
	}
	int AidMan::search(int sku) const {
		for (int i = 0; i < a_numProducts; i++) {
			if (*a_products[i] == sku) {
				return i;
			}
		}
		return -1;
	}
	void AidMan::addItem() {
		if (a_numProducts >= sdds_max_num_items-1) {
			cout << "Database full!\n";
		}
		else {
			int option = 0;
				cout << "1- Perishable\n2- Non-Perishable\n-----------------\n0- Exit\n> ";
				option = ut.getint(0, 2);
				if (option == 0) {
					cout << "Aborted\n";
				}
				else if (option == 1) {
					a_products[a_numProducts] = new Perishable;
					int tempSku = a_products[a_numProducts]->readSku(cin);
					int found = search(tempSku);
					if (found != -1) {
						cout << "Sku: " << tempSku << " is already in the system, try updating quantity instead.\n\n";
						delete a_products[a_numProducts];
						a_products[a_numProducts] = nullptr;
					}
					else {
						cin >> *a_products[a_numProducts];
						cout << '\n';
						if (*a_products[a_numProducts]) {
							a_numProducts++;
						}
						else {
							cout << *a_products[a_numProducts];
							delete a_products[a_numProducts];
							a_products[a_numProducts] = nullptr;
						}
					}
				}
				else {
					a_products[a_numProducts] = new Item;
					int tempSku = a_products[a_numProducts]->readSku(cin);
					int found = search(tempSku);
					if (found != -1) {
						cout << "Sku: " << tempSku << " is already in the system, try updating quantity instead.\n\n";
						delete a_products[a_numProducts];
						a_products[a_numProducts] = nullptr;
					}
					else {
						cin >> *a_products[a_numProducts];
						if (*a_products[a_numProducts]) {
							a_numProducts++;
						}
						else {
							cout << *a_products[a_numProducts];
							delete a_products[a_numProducts];
							a_products[a_numProducts] = nullptr;
						}
					}
				}
		}
	}
	void AidMan::remove(int index) {
		int i;
		delete a_products[index];
		for (i = index; i < a_numProducts - 1; i++) {
			a_products[i] = a_products[i + 1];
		}
		a_products[i] = nullptr;
		a_numProducts--;
	}
	void AidMan::removeItem() {
		char tempDesc[51];
		int tempSku, index;
		cout << "Item description: ";
		cin >> tempDesc; 
		if (list(tempDesc)) {
			cout << "Enter SKU: ";
			tempSku = ut.getint(10000, 99999);
			index = search(tempSku);
			if (index != -1) {
				cout << "Following item will be removed: " << endl;
				a_products[index]->linear(false);
				cout << *a_products[index];
				cout << "\nAre you sure?\n1- Yes!\n0- Exit\n> ";
				int option = -1;
				option = ut.getint(0, 1);
				if (option) {
					remove(index);
					cout << "Item removed!\n\n";
				}
				else {
					cout << "Aborted!";
				}
			}
			else {
				cout << "SKU not found!" << endl;
			}
		}
	}
	void AidMan::updateQty() {
		char tempDesc[51];
		int tempSku, index;
		cout << "Item description: ";
		cin >> tempDesc;
		if (list(tempDesc)) {
			cout << "Enter SKU: ";
			tempSku = ut.getint(10000, 99999);
			index = search(tempSku);
			int option = -1;
			if (index != -1) {
				cout << "1- Add\n2- Reduce\n0- Exit\n> ";
				option = ut.getint(0, 2);
				if (option == 1) {
					int add = 0;
					if (a_products[index]->qty() == a_products[index]->qtyNeeded()) {
						cout << "Quantity Needed already fulfilled!\n\n";
					}
					else {
						cout << "Quantity to add: ";
						add = ut.getint(1, a_products[index]->qtyNeeded() - a_products[index]->qty());
						*a_products[index] += add;
						cout << add << " items added!\n\n";
					}
				}
				else if (option == 2) {
					int minus = 0;
					if (a_products[index]->qty() == 0) {
						cout << "Quantity on hand is zero!\n\n";
					}
					else {
						cout << "Quantity to reduce: ";
						minus = ut.getint(1, a_products[index]->qty());
						*a_products[index] -= minus;
						cout << minus << " items removed!\n\n";
					}
				}
				else {
					cout << "Aborted!\n\n";
				}
			}
			else {
				cout << "SKU not found!\n";
			}
		}
		else {
			cout << "No matches found!\n";
		}
	}
	void AidMan::sort() {
		int i, j, index = a_numProducts - 1;
		for (i = 0; i < index; i++) {
			for (j = 0; j < index - i; j++) {
				if ((a_products[j]->qtyNeeded() - a_products[j]->qty()) < (a_products[j + 1]->qtyNeeded() - a_products[j + 1]->qty())) {
					iProduct* tempItem = a_products[j];
					a_products[j] = a_products[j + 1];
					a_products[j + 1] = tempItem;
				}
			}
		}
		cout << "Sort completed!\n\n";
	}
	void AidMan::shipItem() {
		int day, month, year, rows = 0, items=0;
		ofstream ofstr("shippingOrder.txt");
		ut.getSystemDate(&year, &month, &day);
		ofstr << "Shipping Order, Date: " << year << '/'; 
		ofstr.width(2);
		ofstr.fill('0');
		ofstr << month << '/'; 
		ofstr.width(2);
		ofstr.fill('0');
		ofstr << day << endl;
		ofstr << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl;
		ofstr << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
		for (int i = 0; i < a_numProducts; i++) {
			if (a_products[i]->qty() == a_products[i]->qtyNeeded()) {
				a_products[i]->linear(true);
				ofstr.width(4);
				ofstr.fill(' ');
				ofstr << ++rows << " | ";
				ofstr << *a_products[i] << endl;
				remove(i);
				items++;
			}
		}
		ofstr << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;
		cout << "Shipping Order for " << items << " times saved!\n\n";
	}
}