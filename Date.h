/*
Final Project Milestone 5 6
Keith Cao
143332211
Apr. 11, 2022
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/
#pragma once
#include "Status.h"

namespace sdds {
	const int MAX_YEAR = 2030;
	class Date
	{
		int d_year;
		int d_month;
		int d_day;
		Status status;
		bool d_format;
		bool validate();
		int unDate();
	public:
		Date();
		Date(int year, int month, int day);
		bool operator==(Date d);
		bool operator!=(Date d);
		bool operator>=(Date d);
		bool operator<=(Date d);
		bool operator>(Date d);
		bool operator<(Date d);
		const Status& state();
		Date& formatted(bool format);
		operator bool();
		ostream& write(ostream& ostr)const;
		istream& read(istream& istr);
		friend ostream& operator<<(ostream& ostr, const Date& d);
		friend istream& operator>>(istream& istr, Date& d);
	};
}
