#ifndef __CTIMEPACKET_HPP__
#define __CTIMEPACKET_HPP__

#include "CTime.hpp"

namespace dt {

struct CTimePacket {
	CTime cTime;
	RepeatType repeatType;
	int qty;

	CTimePacket() : cTime(CTime()), repeatType(RepeatType::Weekly), qty(0)
	{}
	CTimePacket(CTime cTime, RepeatType rType, int qty) :
		cTime(cTime), repeatType(rType), qty(qty)
	{}

	static CTimePacket nextCTimePacket(CTimePacket packet) {
		CTime cTime { CTime::nextRepeat(packet.cTime, packet.repeatType,
				packet.qty) };
		return CTimePacket(cTime, packet.repeatType, packet.qty);
	};

	bool operator< (const CTimePacket& other) {
		return cTime < other.cTime;
	}
};

} // namespace dt

#endif // __CTIMEPACKET_HPP__
