//
// Created by George Ford on 3/13/21.
//

#include <ios>
#include <iostream>
#include "CTime.hpp"

#define DEBUG_PRINT(arg) cout << (arg) << ": " << __LINE__ << endl;

using namespace std;

int main() {
    dt::CTime ct1;

	for (int i = 0; i < 8; ++i) {
		ct1.applyRepeat(1, dt::RepeatType::Weekly);
		cout << ct1 << endl;
	}

    return 0;
}
