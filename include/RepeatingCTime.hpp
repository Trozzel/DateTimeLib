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
	// ITERATOR: SEE DEFINITION BELOW
	class iterator;

	RepeatingCTime(const CTime& cTime, RepeatType repeatType, int qty);
	RepeatingCTime(std::initializer_list<CTimePacket> cTimePackets);

	// GET THE NEXT CTIME THAT WOULD REPEAT
	CTime nextCTime();

	// VECTOR WRAPPER FUCNTIONALITY
	inline void pushBack(CTimePacket cTimePacket);
	inline void pushBack(CTime cTime, RepeatType repeatType, int qty);
	inline CTimePacket pop();
	inline CTimePacket front();
	inline CTimePacket back();

	/**************************************************************************/
	// ITERATOR FUNCATIONALITY
	iterator begin() { return iterator(*this, 0);                    }
	iterator end()   { return iterator(*this, _cTimePackets.size()); }

	class iterator {
		private:
		RepeatingCTime& _rptCTime;
		size_t _pos;

		public:
		iterator(RepeatingCTime& rptCTime, size_t pos) : 
			_rptCTime(rptCTime), _pos(pos)
			{}
		iterator& operator++() {
			++_pos;
			return *this;
		}
		iterator& operator++(int) {
			++_pos;
			return *this;
		}
		iterator& operator--() {
			--_pos;
			return *this;
		}
		iterator& operator--(int) {
			--_pos;
			return *this;
		}
		iterator& operator+=(size_t jump) {
			_pos += jump;
			return *this;
		}
		iterator& operator-=(size_t jump) {
			_pos -= jump;
			return *this;
		}
	};
	/**************************************************************************/
};


}

#endif // __REPEATINGCTIME_HPP__
