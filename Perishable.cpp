/*
Final Project Milestone 5 6
Keith Cao
143332211
Apr. 11, 2022
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include "Perishable.h"

using namespace std;
namespace sdds {
	Perishable::Perishable() {
		status = "Invalid";
		status = 0;
		p_hand = nullptr;
	}
	Perishable::Perishable(Perishable& p):Item(p) {
		p_hand = nullptr;
		if (p.p_hand != nullptr) {
			p_hand = new char[strlen(p.p_hand) + 1];
			strcpy(p_hand, p.p_hand);
		}
		status = p.status;
		p_exp = p.expiry();
	}
	Perishable& Perishable::operator=(Perishable& p) {
		Item::operator=(p);
		if (this != &p) {
			delete[] p_hand;
			p_hand = nullptr;
			if (p.p_hand != nullptr) {
				p_hand = new char[strlen(p.p_hand) + 1];
				strcpy(p_hand, p.p_hand);
			}
		}
		status = p.status;
		p_exp = p.expiry();
		return *this;
	}
	Perishable::~Perishable() {
		delete[] p_hand;
		p_hand = nullptr;
	}
	const Date& Perishable::expiry() const {
		return p_exp;
	}
	int Perishable::readSku(std::istream& istr) {
		cout << "SKU: ";
		i_sku = ut.getint(10000, 39999);
		return i_sku;
	}
	std::ofstream& Perishable::save(std::ofstream& ofstr)const {
		Item::save(ofstr);
		Date tempExp;
		tempExp = p_exp;
		tempExp.formatted(false);
		if (status) {
			ofstr << '\t';
			if (p_hand != nullptr && strlen(p_hand) != 0) {
				ofstr << p_hand;
			}
			ofstr << '\t';
			ofstr << tempExp;
		}
		return ofstr;
	 }
	std::ifstream& Perishable::load(std::ifstream& ifstr) {
		char tempHand[51];
		Item::load(ifstr);
		ifstr.getline(tempHand, 2000, '\t');
		delete[] p_hand;
		p_hand = nullptr;
		if (strlen(tempHand) != 0) {
			p_hand = new char[strlen(tempHand) + 1];
			strcpy(p_hand, tempHand);
		}
		if (!ifstr) {
			status = "Input file stream read (perishable) failed!";
			return ifstr;
		}
		ifstr >> p_exp;
		ifstr.get();
		return ifstr;
	 }
	std::ostream& Perishable::display(std::ostream& ostr)const {
		ostr.fill(' ');
		if (!status) {
			ostr << status;
		}
		else if (isLinear()) {
			Item::display(ostr);
			if (p_hand != nullptr) {
				ostr << '*';
			}
			else {
				ostr << ' ';
			}
			ostr << expiry();
		}
		else {
			ostr << "Perishable ";
			Item::display(ostr);
			ostr << "Expiry date: ";
			ostr << expiry() << endl;
			if (p_hand != nullptr) {
				ostr << "Handling Instructions: " << p_hand  << endl;
			}
		}
		return ostr;
	 }
	std::istream& Perishable::read(std::istream& istr) {
		Item::read(istr);
		delete[] p_hand;
		p_hand = nullptr;
		cout << "Expiry date (YYMMDD): ";
		istr >> p_exp;
		istr.ignore(2000, '\n');
		cout << "Handling Instructions, ENTER to skip: ";
		if (istr.peek() != '\n') {
			char tempHand[51];
			istr.getline(tempHand, 2000, '\n');
			p_hand = new char[strlen(tempHand) + 1];
			strcpy(p_hand, tempHand);
		}
		if (!istr) {
			status = "Perishable console date entry failed!";
		}
		return istr;
	 }
}
