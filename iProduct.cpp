/*
Final Project Milestone 5 6
Keith Cao
143332211
Apr. 11, 2022
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/
#include "iProduct.h"
namespace sdds {
	ostream& operator<<(ostream& ostr, iProduct& i) {
		i.display(ostr);
		return ostr;
	}
	istream& operator>>(istream& istr, iProduct& i) {
		i.read(istr);
		return istr;
	}
}