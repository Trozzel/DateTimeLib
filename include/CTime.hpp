//
// Created by George Ford on 3/13/21.
//

#ifndef __LIBDATETIME_CTIME_HPP__
#define __LIBDATETIME_CTIME_HPP__

#include <string>
#include <ctime>
#include <iostream>
#include <memory>
#include "dt_tools.hpp"

namespace dt{

class CTime {
private:
    //struct std::tm* _pTm;
	std::time_t _time;
public:
    CTime();
    explicit CTime(const time_t time);
    explicit CTime(const char* iso8610str);
    CTime(int y, int m, int d);
    ~CTime()                           = default;
    CTime(const CTime& src)            = default; 
    CTime(CTime&& src)                 = default;
    CTime& operator=(const CTime& src) = default;
    CTime& operator=(CTime&& src)      = default;

    // BOOLEAN OPERATORS
    bool operator==(const CTime& src) const;
    bool operator!=(const CTime& src) const;
    bool operator< (const CTime& src) const;
    bool operator> (const CTime& src) const;
    bool operator<=(const CTime& src) const;
    bool operator>=(const CTime& src) const;

    // GETTERS
    [[nodiscard]] inline std::string asciiTime()  const;   /* seconds,  range 0 to 59          */
    [[nodiscard]] inline std::string iso8610Str() const;   /* "YYYY-MM-DD HH:MM:SS"            */
    [[nodiscard]] inline int getHour()            const;   /* hours, range 0 to 23             */
    [[nodiscard]] inline int getMDay()            const;   /* day of the month, range 1 to 31  */
    [[nodiscard]] inline int getMonth()           const;   /* month, range 0 to 11             */
    [[nodiscard]] inline int getYear()            const;   /* The number of years since 1900   */
    [[nodiscard]] inline int getWeekday()         const;   /* day of the week, range 0 to 6    */
    [[nodiscard]] inline int getYearDay()         const;   /* day in the year, range 0 to 365  */
    [[nodiscard]] inline bool isDayLightSavings() const;   /* daylight saving time             */
    [[nodiscard]]        bool isLeapYear()        const;

    // OVERLOADED OPERATORS
    inline CTime& operator+=(int ndays) {
		struct tm* pTm = localtime(&_time);
        pTm->tm_yday += ndays;
        _time = std::mktime(pTm);
        return *this;
    }
    inline CTime& operator-=(int ndays) {
		struct tm* pTm = localtime(&_time);
        pTm->tm_yday -= ndays;
        _time = std::mktime(pTm);
        return *this;
    };
    inline CTime& operator++() {
        this->operator+=(1);
        return *this;
    }
    inline CTime& operator--() {
        this->operator-=(1);
        return *this;
    }

	// SETTERS
	CTime& setDay   (int day);
	CTime& setMonth (int month);
	CTime& setYear  (int year);
	
    // ADD UNITS OF TIME
    CTime& addDays  (int ndays);
    CTime& addMonths(int nmonths);
    CTime& addYears (int nyears);

	// APPLY REPEAT
	void applyRepeat(int qty, RepeatType repeatType);

    // STATIC METHODS
    static double getDiffTime(const CTime& ct2, const CTime& ct1);
    static CTime currentCTime();
    static std::string currentAscTime();
    static std::string currentISOTime();
	static CTime nextRepeat(const CTime& cTime, RepeatType repeatType, int qty);
};

// HELPER FUNCTIONS
bool   operator==(const CTime& t1, const CTime& t2);
bool   operator!=(const CTime& t1, const CTime& t2);
double operator- (const CTime& t1, const CTime& t2);

std::ostream& operator<<(std::ostream& out, const CTime& src);

} // namespace dt


#endif //__LIBDATETIME_CTIME_HPP__
