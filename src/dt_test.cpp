//
// Created by George Ford on 3/13/21.
//

#include <iostream>
#include "CTime.hpp"

using namespace std;

int main() {
    dt::CTime ct;

	int month{}, day{}, year{};
	cout << "Enter month, day, year: ";
	
	cin >> month >> day >> year;


	cout << ct << endl;

    return 0;
}
