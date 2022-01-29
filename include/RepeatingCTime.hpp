#ifndef __REPEATINGCTIME_HPP__
#define __REPEATINGCTIME_HPP__

#include <initializer_list>
#include <vector>

#include "CTime.hpp"
#include "CTimePacket.hpp"

namespace dt {

class RepeatingCTime
{
private:
	std::vector<CTimePacket> _cTimePackets;

public:
	RepeatingCTime(const CTime& cTime, RepeatType repeatType, int qty);
	RepeatingCTime(std::vector<CTimePacket> cTimePackets);

	// GET THE NEXT CTIME THAT WOULD REPEAT
	CTime nextCTime();

	// VECTOR WRAPPER FUCNTIONALITY
	inline void pushBack(CTimePacket cTimePacket);
	inline void pushBack(CTime cTime, RepeatType repeatType, int qty);
	inline CTimePacket pop();
	inline CTimePacket front();
	inline CTimePacket back();
};


}

#endif // __REPEATINGCTIME_HPP__
