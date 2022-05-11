/*
Final Project Milestone 5 6
Keith Cao
143332211
Apr. 11, 2022
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/
#pragma once
#include "Status.h"
#include "iProduct.h"
namespace sdds {
	class Item:public iProduct
	{
		double i_price;
		int i_qtyHand;
		int i_qtyNeed;
		char* i_desc;
		bool i_display;
	protected:
		Status status;
		int i_sku;
		bool isLinear() const;
	public:
		Item();
		Item(Item& i);
		Item& operator=(Item& i);
		virtual ~Item();
		virtual int readSku(std::istream& istr);
		virtual int qtyNeeded() const;
		virtual int qty() const;
		virtual operator double() const;
		virtual operator bool() const;
		virtual int operator-=(int qty);
		virtual int operator+=(int qty);
		virtual void linear(bool isLinear);
		void clear();
		virtual bool operator==(int sku) const;
		virtual bool operator==(const char* description)const;
		virtual std::ofstream& save(std::ofstream& ofstr)const;
		virtual std::ifstream& load(std::ifstream& ifstr);
		virtual std::ostream& display(std::ostream& ostr)const;
		virtual std::istream& read(std::istream& istr);
	};
}

