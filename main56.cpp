/*
Final Project Milestone 5 6
Keith Cao
143332211
Apr. 11, 2022
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/
#include <iostream>
#include <fstream>
#include "AidMan.h"
#include "Utils.h"
using namespace sdds;
using namespace std;

void copyfile(const char* to, const char* from);
void displayFile(const char* file);

int main() {
	copyfile("data.dat", "data56.dat");
	ut.testMode();
	AidMan().run();
	displayFile("data.dat");
	cout << endl << "------------------------------------------------" << endl;
	displayFile("shippingOrder.txt");
	return 0;
}

void displayFile(const char* file) {
	ifstream in(file);
	char ch;
	cout << "File: " << file << endl;
	while (in.get(ch)) cout << ch;
}

void copyfile(const char* to, const char* from) {
	std::ifstream in(from);
	std::ofstream out(to);
	char ch;
	while (in.get(ch)) out.put(ch);
}