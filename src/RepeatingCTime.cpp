#include <algorithm>

#include "RepeatingCTime.hpp"

using namespace std;

namespace dt {

// CTOR 1
/******************************************************************************/
RepeatingCTime::RepeatingCTime(const CTime& cTime, RepeatType repeatType,
		int qty)
{
	_cTimePackets.push_back(CTimePacket(cTime, repeatType, qty));
}


// CTOR 2
/******************************************************************************/
RepeatingCTime::RepeatingCTime(std::initializer_list<CTimePacket> cTimePackets):
	_cTimePackets(cTimePackets)
{
}

// GET NEXT CTIME
/******************************************************************************/
CTime RepeatingCTime::nextCTime()
{
	vector<CTimePacket> nextCTimePackets(_cTimePackets.size());
	for (auto cTimePacket : _cTimePackets)
		nextCTimePackets.push_back(CTimePacket::nextCTimePacket(cTimePacket));

	sort(nextCTimePackets.begin(), nextCTimePackets.end());

	return (*nextCTimePackets.begin()).cTime;
}

/**************************** VECTOR FUCNTIONALITY ****************************/
void RepeatingCTime::pushBack(CTimePacket cTimePacket)
{
	_cTimePackets.push_back(cTimePacket);
}

void RepeatingCTime::pushBack(CTime cTime, RepeatType repeatType, int qty)
{
	_cTimePackets.push_back(CTimePacket(cTime, repeatType, qty));
}

CTimePacket RepeatingCTime::pop()
{
	CTimePacket packet { back() };
	_cTimePackets.pop_back();
	return packet;
}

CTimePacket RepeatingCTime::front()
{
	return _cTimePackets.front();
}

CTimePacket RepeatingCTime::back()
{
	return _cTimePackets.back();
}


} // namespace dt
