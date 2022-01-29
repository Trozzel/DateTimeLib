//
// Created by George Ford on 3/13/21.
//

#include <ios>
#include <iostream>
#include "CTime.hpp"
#include "CTimePacket.hpp"
#include "RepeatingCTime.hpp"
#include "dt_tools.hpp"

#define DEBUG_PRINT(arg) cout << (arg) << ": " << __LINE__ << endl;

using namespace std;
using namespace dt;

int main() {
	dt::CTime ct1(2022, 3,  25);
	dt::CTime ct2(2022, 9,  21);
	dt::CTime ct3(2022, 6,  14);
	dt::CTime ct4(2022, 12, 13);
	dt::CTime ct5(2022, 2,  15);

	vector<dt::CTimePacket> timePackets {
		dt::CTimePacket(ct1, RepeatType::Yearly, 1), 
			dt::CTimePacket(ct4, RepeatType::Weekly, 1),
			dt::CTimePacket(ct3, RepeatType::Monthly, 1),
			dt::CTimePacket(ct5, RepeatType::Daily, 1),
			dt::CTimePacket(ct2, RepeatType::Yearly, 1)
	};

	RepeatingCTime rct { timePackets };

	CTime nextCt = rct.nextCTime();
	cout << "Next Birthday: " << nextCt << endl;

    return 0;
}
