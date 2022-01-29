//
// Created by George Ford on 3/13/21.
//

#include <ios>
#include <iostream>
#include "CTime.hpp"
#include "dt_tools.hpp"

#define DEBUG_PRINT(arg) cout << (arg) << ": " << __LINE__ << endl;

using namespace std;

int main() {
    dt::CTime ct1;

	for (int i = 0; i < 8; ++i) {
		dt::CTime temp = dt::CTime::nextRepeat(ct1, dt::RepeatType::Yearly, i);
		cout << temp << endl;
	}

    return 0;
}
