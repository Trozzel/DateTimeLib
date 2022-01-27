//
// Created by George Ford on 3/13/21.
//

#include <ios>
#include <iostream>
#include <limits>
#include <streambuf>
#include "CTime.hpp"

#define DEBUG_PRINT(arg) cout << (arg) << ": " << __LINE__ << endl;

using namespace std;

int main() {
    dt::CTime ct2;
    dt::CTime ct1(1977, 4, 25);

	cout << "Diff time: " << dt::CTime::getDiffTime(ct2, ct1) << endl;

	cout << "t1: " << ct1 << endl;
	cout << "t2: " << ct2 << endl;

    return 0;
}
