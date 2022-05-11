/*
Final Project Milestone 5 6
Keith Cao
143332211
Apr. 11, 2022
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <cstring>
#include <string>
#include <fstream>
#include "Item.h"

namespace sdds {
	bool Item::isLinear() const{
		return i_display;
	}
	Item::Item() {
		i_price = 0.0;
		i_qtyHand = 0;
		i_qtyNeed = 0;
		i_desc = nullptr;
		i_display = false;
		i_sku = 0;
	}
	Item::Item(Item& i) {
		i_desc = nullptr;
		if (i.i_desc != nullptr) {
			i_desc = new char[strlen(i.i_desc) + 1];
			strcpy(i_desc, i.i_desc);
		}
		i_price = i.i_price;
		i_qtyHand = i.i_qtyHand;
		i_qtyNeed = i.i_qtyNeed;
		i_display = i.i_display;
		i_sku = i.i_sku;
	}
	Item& Item::operator=(Item& i) {
		if (this != &i) {
			delete[] i_desc;
			i_desc = nullptr;
			if (i.i_desc != nullptr) {
				i_desc = new char[strlen(i.i_desc) + 1];
				strcpy(i_desc, i.i_desc);
			}
			i_price = i.i_price;
			i_qtyHand = i.i_qtyHand;
			i_qtyNeed = i.i_qtyNeed;
			i_display = i.i_display;
			i_sku = i.i_sku;
		}
		return *this;
	}
	Item::~Item() {
		delete[] i_desc;
		i_desc = nullptr;
	}
	int Item::qtyNeeded() const {
		return i_qtyNeed;
	}
	int Item::qty() const {
		return i_qtyHand;
	}
	Item::operator double() const {
		return i_price;
	}
	Item::operator bool() const {
		return status;
	}
	int Item::operator-=(int qty) {
		int minusValue = i_qtyHand - qty;
		if (minusValue < 0) {
			int subtracted = i_qtyHand;
			i_qtyHand = 0;
			return subtracted;
		}
		else {
			i_qtyHand -= qty;
			return qty;
		}
	}
	int Item::operator+=(int qty) {
		i_qtyHand += qty;
		return i_qtyHand;
	}
	void Item::linear(bool isLinear) {
		i_display = isLinear;
	}
	void Item::clear() {
		status.Status::clear();
	}
	bool Item::operator==(int sku) const{
		return i_sku == sku;
	}
	bool Item::operator==(const char* description)const {
		return i_desc != nullptr && description != nullptr && strstr(i_desc, description) != nullptr;
	}
	std::ofstream& Item::save(std::ofstream& ofstr)const {
		if (status) {
			ofstr << i_sku << '\t' << i_desc << '\t' << i_qtyHand << '\t' << i_qtyNeed << '\t' << i_price;
		}
		return ofstr;
	}
	std::ifstream& Item::load(std::ifstream& ifstr) {
		char tempDesc[1000];
		clear();
		ifstr >> i_sku;
		ifstr.get();
		ifstr.getline(tempDesc, 2000, '\t');
		delete[]i_desc;
		i_desc = new char[strlen(tempDesc) + 1];
		strcpy(i_desc, tempDesc);
		ifstr >> i_qtyHand >> i_qtyNeed >> i_price;
		ifstr.get();
		if (!ifstr) {
			status = "Input file stream read failed!";
		}
		return ifstr;
	}
	std::ostream& Item::display(std::ostream& ostr)const {
		if (!status) {
			ostr << status;
		}
		else if (i_display) {
			ostr.width(5);
			ostr << i_sku << " | ";
			ostr.width(35);
			ostr.setf(ios::left);
			if (strlen(i_desc) > 35) {
				int i;
				char tempDesc[36];
				for (i = 0; i < 35; i++) {
					tempDesc[i] = i_desc[i];
				}
				tempDesc[i] = '\0';
				ostr << tempDesc << " | ";
			}
			else {
				ostr << i_desc << " | ";
			}
			ostr.unsetf(ios::left);
			ostr.width(4);
			ostr << i_qtyHand << " | ";
			ostr.width(4);
			ostr << i_qtyNeed << " | ";
			ostr.width(7);
			ostr.setf(ios::fixed);
			ostr.precision(2);
			ostr << i_price << " |";
		}
		else {
			ostr << "AMA Item:" << endl;
			ostr << i_sku << ": " << i_desc <<endl;
			ostr << "Quantity Needed: ";
			ostr << i_qtyNeed << endl;
			ostr << "Quantity Available: ";
			ostr << i_qtyHand << endl;
			ostr << "Unit Price: $";
			ostr.setf(ios::fixed);
			ostr.precision(2);
			ostr << i_price << endl;
			ostr << "Needed Purchase Fund: $";
			ostr.setf(ios::fixed);
			ostr.precision(2);
			double needPurchase = ((double)i_qtyNeed - (double)i_qtyHand) * i_price;
			ostr << needPurchase << endl;
		}
		return ostr;
	}
	int Item::readSku(std::istream& istr) {
		cout << "SKU: ";
		i_sku = ut.getint(40000, 99999);
		return i_sku;
	}
	std::istream& Item::read(std::istream& istr) {
		char tempDesc[51];
		clear();
		cout << "AMA Item:" << endl;
		cout << "SKU: " << i_sku << endl;
		cout << "Description: ";
		istr.get();
		istr.getline(tempDesc, 2000, '\n');
		delete[] i_desc;
		i_desc = new char[strlen(tempDesc) + 1];
		strcpy(i_desc, tempDesc);
		cout << "Quantity Needed: ";
		i_qtyNeed = ut.getint(1, 9999);
		cout << "Quantity On Hand: ";
		i_qtyHand = ut.getint(0, i_qtyNeed);
		cout << "Unit Price: $";
		i_price = ut.getDouble(0.0, 9999.0);
		if (!istr.good()) {
			status = "Console entry failed!";
		}
		return istr;
	}
}