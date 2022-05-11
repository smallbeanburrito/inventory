/*
Final Project Milestone 5 6
Keith Cao
143332211
Apr. 11, 2022
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/
#pragma once
#include "Item.h"
#include "Date.h"
namespace sdds {
	class Perishable : public Item
	{
		Date p_exp;
		char* p_hand;
	public:
		Perishable();
		Perishable(Perishable& p);
		Perishable& operator=(Perishable& p);
		~Perishable();
		const Date& expiry() const;
		virtual int readSku(std::istream& istr);
		virtual std::ofstream& save(std::ofstream& ofstr)const;
		virtual std::ifstream& load(std::ifstream& ifstr);
		virtual std::ostream& display(std::ostream& ostr)const;
		virtual std::istream& read(std::istream& istr);
	};
}

