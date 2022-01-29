//
// Created by George Ford on 3/13/21.
//
#include <sstream>
#include "CTime.hpp"

using namespace std;

namespace dt {

// DEFAULT CTOR - defaults to "today" at 0630
CTime::CTime() 
{
    _time = std::time(nullptr);
    struct tm* pTm = localtime(&_time);
    _time = mktime(pTm);
}

// CTOR WITH std::time_t
CTime::CTime(const time_t time) 
{
    _time = time;
}

// CTOR FROM ISO-8610 STRING
/*******************************************************************************
 * Important for working with datetime format of SQLite
 * See: https://sqlite.org/lanatefunc.html
 * @param char* : iso8610sg_dtr
 */
CTime::CTime(const char* iso8610str) 
{
    if (!isValidIso8610(iso8610str))
        throw std::invalid_argument("Must be in format 'YYYY-MM-DD HH:MM:SS'");
    int y, mon, d, hr, minute, sec = 0;
    std::sscanf(iso8610str, "%d-%d-%d %d:%d:%d",
                            &y, &mon, &d, &hr, &minute, &sec);

    time_t t = std::time(nullptr);
    struct tm* pTm = localtime(&t);
    pTm->tm_year = y - 1900;
    pTm->tm_mon  = mon - 1;
    pTm->tm_mday = d;
    pTm->tm_hour = hr;
    pTm->tm_min  = minute;
    pTm->tm_sec  = sec;
    if (!isValidDate(y, mon-1, d))
        throw std::runtime_error("Not a valid entry date");
    _time = std::mktime(pTm);
}

// CTOR WITH INTS
CTime::CTime(int y, int m, int d) 
{
	--m;
    if (!isValidDate(y, m, d)) {
        std::stringstream ss;
        ss << "(" << y << ", " << m << ", " << d << ")";
        throw std::invalid_argument(ss.str() + " are in values for CTime");
    }
    time_t t = std::time(nullptr);
    struct tm* pTm = localtime(&t);
    pTm->tm_year = y - 1900;
    pTm->tm_mon  = m;
    pTm->tm_mday = d;

    // ADD DEFAULT VALUES
    pTm->tm_hour = 6;
    pTm->tm_min  = 30;
    pTm->tm_sec  = 0;
    _time = std::mktime(pTm);
}

/************************* BOOLEAN OPERATORS **********************************/
bool CTime::operator==(const CTime& src) const 
{
    return diffTime(*this, src) == 0;
}

bool CTime::operator!=(const CTime& src) const 
{

    return diffTime(*this, src) != 0;
}

bool CTime::operator> (const CTime& src) const 
{
    return (diffTime(*this, src) > 0);
}

bool CTime::operator< (const CTime& src) const 
{
    return (diffTime(*this, src) < 0);
}

bool CTime::operator>=(const CTime& src) const 
{
    return operator==(src) || operator>(src);
}

bool CTime::operator<=(const CTime& src) const 
{
    return operator==(src) || operator<(src);
}

/*********************************** GETTERS **********************************/
// GET ASC TIME
/*******************************************************************************
 * getAscTime
 * @return std::string: example: "Fri Apr 15 12:05:34 2005"
 * @param None
 */
std::string CTime::asciiTime() const 
{
    struct tm* pTm = localtime(&_time);
    return std::string(asctime(pTm));
}

// GET ISO-8610 STRING
std::string CTime::iso8610Str() const 
{
    char datetime[20];
    struct tm* pTm = localtime(&_time);
    std::strftime(datetime, 20, "%Y-%m-%d %H:%M:%S", pTm);
    return std::string { datetime };
}

// GET HOUR
int CTime::getHour() const 
{
    struct tm* pTm = localtime(&_time);
    return pTm->tm_hour;
}

// GET DAY
int CTime::getMDay() const 
{
	struct tm* pTm = localtime(&_time);
    return pTm->tm_mday;
}

// GET MONTH
int CTime::getMonth() const 
{
    struct tm* pTm = localtime(&_time);
    return pTm->tm_mon;
}

// GET YEAR
int CTime::getYear() const 
{
	struct tm* pTm = localtime(&_time);
    return pTm->tm_year;
}

// GET WEEKDAY
int CTime::getWeekday() const 
{
	struct tm* pTm = localtime(&_time);
    return pTm->tm_wday;
}

// GET DAY OF YEAR
int CTime::getYearDay() const 
{
	struct tm* pTm = localtime(&_time);
    return pTm->tm_yday;
}

bool CTime::isDayLightSavings() const 
{
	struct tm* pTm = localtime(&_time);
    return static_cast<bool>(pTm->tm_isdst);
}

bool CTime::isLeapYear() const 
{
	struct tm* pTm = localtime(&_time);
    int year = pTm->tm_year;
    return (year%4 == 0 && year%100 !=0) || year%400 == 0;
}

/******************************** SETTERS *************************************/
// SET DAY
CTime& CTime::setDay(int day)
{
	// CHECK TO SEE IF THIS IS A VALID DAY
	struct tm* pTm = localtime(&_time);
    int year  = pTm->tm_year; 
    int month = pTm->tm_mon;

	if (isValidDate(year, month, day))
		pTm->tm_mday = day;
	else // DO NOT UPDATE THE DAY
		cout << "WARNING: " << day << " is not a valid day for " 
			 << Months[pTm->tm_mon].first << ", " << pTm->tm_year << endl;

	return *this;
}

// SET DAY
CTime& CTime::setMonth(int day)
{
	return *this;
}

// SET DAY
CTime& CTime::setYear(int day)
{
	return *this;
}

/************************* ADD UNITS*******************************************/
// ADD DAYS
CTime& CTime::addDays(int ndays) 
{
	struct tm* pTm = localtime(&_time);
    pTm->tm_mday += ndays;
    std::mktime(pTm);
    return *this;
}

// ADD MONTHS
CTime& CTime::addMonths(int nmonths) 
{
	struct tm* pTm = localtime(&_time);
    pTm->tm_mon += nmonths;
    _time = std::mktime(pTm);
    return *this;
}

// ADD YEARS
CTime& CTime::addYears(int nyears) 
{
	struct tm* pTm = localtime(&_time);
    pTm->tm_year += nyears;
    _time = std::mktime(pTm);
    return *this;
}

// APPLY REPEAT
void CTime::applyRepeat(int qty, RepeatType repeatType)
{
	struct tm* pTm = localtime(&_time);

	switch (repeatType) {
	case RepeatType::Daily:
		pTm->tm_mday += qty;
		break;
	case RepeatType::Weekly:
		pTm->tm_mday += 7 * qty;
		break;
	case RepeatType::Monthly:
		pTm->tm_mon += qty;
		break;
	case RepeatType::Yearly:
		pTm->tm_year += qty;
		break;
	}
	_time = mktime(pTm);
}

/********************* STATIC FUNCTIONS ***************************************/
// GET DIFF TIME
double CTime::diffTime(const CTime &ct2, const CTime &ct1) 
{
    return std::difftime(ct2._time, ct1._time);
}

// GET NEXT REPEAT
CTime CTime::nextRepeat(const CTime& cTime, RepeatType repeatType, int qty)
{
	struct tm* pTm = localtime(&cTime._time);

	switch (repeatType) {
	case RepeatType::Daily:
		pTm->tm_mday += qty;
		break;
	case RepeatType::Weekly:
		pTm->tm_mday += 7 * qty;
		break;
	case RepeatType::Monthly:
		pTm->tm_mon += qty;
		break;
	case RepeatType::Yearly:
		pTm->tm_year += qty;
		break;
	}
	return CTime(mktime(pTm));
}


/************************** HELPER FUNCTIONS **********************************/
bool operator==(const CTime &t1, const CTime &t2) 
{
    return t1.operator==(t2);
}

bool operator!=(const CTime &t1, const CTime &t2) 
{
    return t1.operator!=(t2);
}

double operator-(const CTime& t1, const CTime& t2)
{
	return CTime::diffTime(t2, t1);
}

std::ostream& operator<<(std::ostream &out, const CTime &src) 
{
    out << src.asciiTime();
    return out;
}

CTime CTime::currentCTime() 
{
    struct std::tm* temp_tm;
    std::time_t t_now = std::time(nullptr);
    temp_tm = localtime(&t_now);
    mktime(temp_tm);
    return CTime{t_now};
}

std::string CTime::currentAscTime() 
{
    CTime now {currentCTime()};
    return now.asciiTime();
}


std::string CTime::currentISOTime() 
{
    CTime now {currentCTime()};
    return now.iso8610Str();
}

} // namespace dt
