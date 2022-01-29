#include <iostream>
#include <algorithm>
#include <iterator>

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
RepeatingCTime::RepeatingCTime(std::vector<CTimePacket> cTimePackets):
	_cTimePackets(cTimePackets)
{
}

// GET NEXT CTIME
/******************************************************************************/
CTime RepeatingCTime::nextCTime()
{
	using packet_t = pair<CTimePacket, double>; 

	CTime today{};

	// CREATE VECTOR OF NEXT CTIMES WITH DIFFTIME AGAINST TODAY
	vector<packet_t> packets;
	for (auto packet : _cTimePackets) {
		packet_t pktPair(packet, CTime::diffTime(packet.cTime, today));
		packets.push_back(pktPair);
	}

	// SORT THE PREVIOUS PACKETS ACCORDING TO TIME FROM TODAY
	auto comp = [&](const packet_t& p1, const packet_t& p2) {
		return p1.second < p2.second;
	};
	sort(packets.begin(), packets.end(), comp);

	return (*packets.begin()).first.cTime;
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
