/*
Final Project Milestone 5 6
Keith Cao
143332211
Apr. 11, 2022
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/
#pragma once
#include <iostream>
#include "Utils.h"
using namespace std;
namespace sdds {
	class Status 
	{
		char* s_desc=nullptr;
		int s_code=0;
	public:
		Status();
		Status(const char* desc);
		Status(Status& s);
		Status& operator=(const Status& s);
		~Status();
		bool isValid()const;
		bool isValid(char* desc)const;
		Status& operator=(int code);
		Status& operator=(const char* desc);
		operator int()const;
		operator const char*() const;
		operator bool() const;
		Status& clear();
		friend ostream& operator<<(ostream& ostr, const Status& s);
	};
}

