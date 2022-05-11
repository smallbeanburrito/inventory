/*
Final Project Milestone 5 6
Keith Cao
143332211
Apr. 11, 2022
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/
#include "Date.h"
namespace sdds {
	bool Date::validate() {
		if (d_year < sdds_testYear || d_year > MAX_YEAR) {
			status = "Invalid year in date";
			status = 1;
			return false;
		}
		if (d_month < 1 || d_month > 12) {
			status = "Invalid month in date";
			status = 2;
			return false;
		}
		if (d_day < 1 || d_day > ut.daysOfMon(d_month, d_year)) {
			status = "Invalid day in date";
			status = 3;
			return false;
		}
		status.clear();
		return true;
	}
	int Date::unDate() {
		return d_year * 372 + d_month * 31 + d_day;
	}
	Date::Date() {
		ut.getSystemDate(&d_year, &d_month, &d_day);
		d_format = true;
	}
	Date::Date(int year, int month, int day) {
		d_year = year;
		d_month = month;
		d_day = day;
		d_format = true;
		validate();
	}
	bool Date::operator==(Date d) {
		return unDate() == d.unDate();
	}
	bool Date::operator!=(Date d) {
		return unDate() != d.unDate();
	}
	bool Date::operator>=(Date d) {
		return unDate() >= d.unDate();
	}
	bool Date::operator<=(Date d) {
		return unDate() <= d.unDate();
	}
	bool Date::operator>(Date d) {
		return unDate() > d.unDate();
	}
	bool Date::operator<(Date d) {
		return unDate() < d.unDate();
	}
	const Status& Date::state() {
		return status;
	}
	Date& Date::formatted(bool format) {
		d_format = format;
		return *this;
	}
	Date::operator bool() {
		return status;
	}
	ostream& Date::write(ostream& ostr) const {
		if (d_format) {
			ostr << d_year<<'/';
			ostr.width(2);
			ostr.fill('0');
			ostr << d_month << '/';
			ostr.width(2);
			ostr.fill('0');
			ostr << d_day;
		}
		else {
			ostr << d_year-2000;
			ostr.width(2);
			ostr.fill('0');
			ostr << d_month;
			ostr.width(2);
			ostr.fill('0');
			ostr << d_day;
		}
		return ostr;
	}
	istream& Date::read(istream& istr) {
		int tempDate;
		istr >> tempDate;
		if (istr) {
			if (tempDate > 99999 && tempDate < 1000000) {
				d_year = tempDate / 10000 +2000;
				d_month = (tempDate % 10000) / 100;
				d_day = tempDate % 100;
			}
			else if (tempDate < 10000 && tempDate > 999) {
				d_year = sdds_testYear;
				d_month = tempDate / 100;
				d_day = tempDate % 100;
			}
			else {
				d_year = sdds_testYear;
				d_month = 0;
				d_day = 0;
			}
			if (!validate()) {
				istr.istream::setstate(ios::badbit);
			}
		}
		else {
			cout << "Invalid date value";
		}
		return istr;
	}
	ostream& operator<<(ostream& ostr, const Date& d) {
		d.write(ostr);
		return ostr;
	}
	istream& operator>>(istream& istr, Date& d) {
		d.read(istr);
		return istr;
	}
}