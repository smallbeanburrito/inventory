/*
Final Project Milestone 5 6
Keith Cao
143332211
Apr. 11, 2022
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/
#pragma once
#include "iProduct.h"
#include "Menu.h"
namespace sdds {
	const int sdds_max_num_items = 100;
	class AidMan : public Menu
	{
		char* a_filename;
		unsigned int menu();
		iProduct* a_products[sdds_max_num_items];
		int a_numProducts;
		void save();
		void deallocate();
		bool load();
		int list(const char* sub_desc=nullptr);
		int search(int sku) const;
		void addItem();
		void remove(int index);
		void removeItem();
		void updateQty();
		void sort();
		void shipItem();
	public:
		AidMan();
		AidMan(AidMan& a) = delete;
		AidMan& operator=(AidMan& a) = delete;
		~AidMan();
		void run();
	};
}

