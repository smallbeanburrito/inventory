/*
Final Project Milestone 5 6
Keith Cao
143332211
Apr. 11, 2022
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/
#include "Status.h"
#pragma once
namespace sdds {
	class Menu
	{
		char* m_options;
		unsigned int m_numOptions;
	public:
		Menu(const char* options, unsigned int numOptions);
		Menu(Menu& m) = delete;
		Menu& operator=(Menu& m) = delete;
		~Menu();
		// my own method
		bool isValid();
		unsigned int run()const;
	};
}

