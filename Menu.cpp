/*
Final Project Milestone 5 3
Keith Cao
143332211
Apr. 10, 2022
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/
#define _CRT_SECURE_NO_WARNINGS
#include "Menu.h"
namespace sdds {
	Menu::Menu(const char* options, unsigned int numOptions) {
		m_options = new char[strlen(options) + 1];
		strcpy(m_options, options);
		m_numOptions = numOptions;
		if (!isValid()) {
			delete[] m_options;
			m_options = nullptr;
			m_numOptions = 0;
		}
	}
	Menu::~Menu() {
		delete[] m_options;
		m_options = nullptr;
	}
	bool Menu::isValid() {
		return m_options != nullptr && m_numOptions < 15;
	}
	unsigned int Menu::run() const {
		cout << m_options;
		cout << "0- Exit\n> ";
		unsigned int option = 100;
		while (option > m_numOptions || option < 0) {
			cin >> option;
			if (!cin) {
				cout << "Invalid Integer, retry: ";
				cin.clear();
				option = 100;
				cin.ignore(2000, '\n');
			}
			else if (option > m_numOptions || option < 0) {
				cout << "Value out of range [" << "0<=val<=" << m_numOptions << "]: ";
			}
		} 
		return option;
	}
}
