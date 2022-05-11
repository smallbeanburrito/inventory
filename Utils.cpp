/*
Final Project Milestone 5 6
Keith Cao
143332211
Apr. 11, 2022
I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include "Utils.h"
using namespace std;
namespace sdds {
    Utils ut;
    void Utils::testMode(bool testmode) {
        m_testMode = testmode;
    }
    void Utils::getSystemDate(int* year, int* mon, int* day) {
        if (m_testMode) {
            if (day) *day = sdds_testDay;
            if (mon) *mon = sdds_testMon;
            if (year) *year = sdds_testYear;
        }
        else {
            time_t t = std::time(NULL);
            tm lt = *localtime(&t);
            if (day) *day = lt.tm_mday;
            if (mon) *mon = lt.tm_mon + 1;
            if (year) *year = lt.tm_year + 1900;
        }
    }
    int Utils::daysOfMon(int month, int year)const {
        int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
        int mon = (month >= 1 && month <= 12 ? month : 13) - 1;
        return days[mon] + int((mon == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
    }
    int Utils::getint(int min, int max) {
        int temp = -1;
        while (temp > max || temp < min) {
            cin >> temp;
            if (!cin) {
                cout << "Invalid Integer, retry: ";
                cin.clear();
                temp = min-1;
                cin.ignore(2000, '\n');
            }
            else if (temp > max || temp < min) {
                cout << "Value out of range [" << min <<"<=val<=" << max << "]: ";
            }
        }
        return temp;
    }
    double Utils::getDouble(double min, double max) {
        double temp = -1;
        while (temp > max || temp < min) {
            cin >> temp;
            if (!cin) {
                cout << "Invalid number, retry: ";
                cin.clear();
                temp = min - 1;
                cin.ignore(2000, '\n');
            }
            else if (temp > max || temp < min) {
                cout << "Value out of range ["; 
                cout.setf(ios::fixed);
                cout.precision(2);
                cout << min; 
                cout << "<=val<="; 
                cout.precision(2);
                cout << max << "]: ";
            }
        }
        return temp;
    }
}