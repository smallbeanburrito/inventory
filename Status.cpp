/*
Final Project Milestone 5 6
Keith Cao
143332211
Apr. 11, 2022
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/
#define _CRT_SECURE_NO_WARNINGS
#include<string.h>
#include "Status.h"
namespace sdds {
	bool Status::isValid() const{
		return s_desc != nullptr;
	}
	bool Status::isValid(char* desc) const{
		return desc != nullptr;
	}
	Status::Status() {
		s_desc = nullptr;
		s_code = 0;
	}
	Status::Status(const char* desc) {
		s_desc = new char[strlen(desc) + 1];
		strcpy(s_desc, desc);
		s_code = 0;
	}
	Status::Status(Status& s) {
		if (s.isValid()) {
			s_code = s.s_code;
			s_desc = new char[strlen(s.s_desc) + 1];
			strcpy(s_desc, s.s_desc);
		}
		s_code = s.s_code;
	}
	Status& Status::operator=(const Status& s) {
		if (this != &s) {
			delete[] s_desc;
			s_desc = nullptr;
			if (s.isValid()) {
				s_desc = new char[strlen(s.s_desc) + 1];
				strcpy(s_desc, s.s_desc);
			}
		}
		s_code = s.s_code;
		return *this;
	}
	Status::~Status() {
		delete[] s_desc;
		s_desc = nullptr;
	}
	Status& Status::operator=(int code) {
		s_code = code;
		return *this;
	}
	Status& Status::operator=(const char* desc) {
		delete[] s_desc;
		s_desc = new char[strlen(desc) + 1];
		strcpy(s_desc, desc);
		return *this;
	}
	Status::operator int() const {
		return s_code;
	}
	Status::operator const char*() const {

		return s_desc;
	}
	Status::operator bool() const {
		return s_desc == nullptr;
	}
	Status& Status::clear() {
		delete[] s_desc;
		s_desc = nullptr;
		s_code = 0;
		return *this;
	}
	ostream& operator<<(ostream& ostr, const Status& s) {
		if (!s) {
			if (s.s_code != 0) {
				ostr << "ERR#" << s.s_code << ": ";
			}
			ostr << s.s_desc;
		}
		return ostr;
	}
}