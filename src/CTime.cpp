//
// Created by George Ford on 3/13/21.
//
#include <sstream>
#include "CTime.hpp"

using namespace std;

// DEFAULT CTOR - defaults to 0630
dt::CTime::CTime() 
{
    _time = std::time(nullptr);
    struct tm* pTm = localtime(&_time);
    _time = mktime(pTm);
}

// CTOR WITH std::time_t
dt::CTime::CTime(const time_t* time) 
{
    _time = *time;
}

// CTOR FROM ISO-8610 STRING
/*******************************************************************************
 * Important for working with datetime format of SQLite
 * See: https://sqlite.org/lanatefunc.html
 * @param char* : iso8610sg_dtr
 */
dt::CTime::CTime(const char* iso8610str) 
{
    if (!dt::isValidIso8610(iso8610str))
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
    if (!dt::isValidDate(y, mon-1, d))
        throw std::runtime_error("Not a valid entry date");
    _time = std::mktime(pTm);
}

// CTOR WITH INTS
dt::CTime::CTime(int y, int m, int d) 
{
    if (!isValidDate(y, m, d)) {
        std::stringstream ss;
        ss << "(" << y << ", " << m << ", " << d << ")";
        throw std::invalid_argument(ss.str() + " are in values for CTime");
    }
    time_t t = std::time(nullptr);
    struct tm* pTm = localtime(&t);
    pTm->tm_year = y - 1900;
    pTm->tm_mon  = m - 1;
    pTm->tm_mday = d;

    // ADD DEFAULT VALUES
    pTm->tm_hour = 6;
    pTm->tm_min  = 30;
    pTm->tm_sec  = 0;
    _time = std::mktime(pTm);
}

/************************* BOOLEAN OPERATORS **********************************/
bool dt::CTime::operator==(const dt::CTime& src) const 
{
    return getDiffTime(*this, src) == 0;
}

bool dt::CTime::operator!=(const dt::CTime& src) const 
{

    return getDiffTime(*this, src) != 0;
}

bool dt::CTime::operator> (const dt::CTime& src) const 
{
    return (getDiffTime(*this, src) > 0);
}

bool dt::CTime::operator< (const dt::CTime& src) const 
{
    return (getDiffTime(*this, src) < 0);
}

bool dt::CTime::operator>=(const dt::CTime& src) const 
{
    return operator==(src) || operator>(src);
}

bool dt::CTime::operator<=(const dt::CTime& src) const 
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
std::string dt::CTime::asciiTime() const 
{
    struct tm* pTm = localtime(&_time);
    return std::string(asctime(pTm));
}

// GET ISO-8610 STRING
std::string dt::CTime::iso8610Str() const 
{
    char datetime[20];
    struct tm* pTm = localtime(&_time);
    std::strftime(datetime, 20, "%Y-%m-%d %H:%M:%S", pTm);
    return std::string { datetime };
}

// GET HOUR
int dt::CTime::getHour() const 
{
    struct tm* pTm = localtime(&_time);
    return pTm->tm_hour;
}

// GET DAY
int dt::CTime::getMDay() const 
{
	struct tm* pTm = localtime(&_time);
    return pTm->tm_mday;
}

// GET MONTH
int dt::CTime::getMonth() const 
{
    struct tm* pTm = localtime(&_time);
    return pTm->tm_mon;
}

// GET YEAR
int dt::CTime::getYear() const 
{
	struct tm* pTm = localtime(&_time);
    return pTm->tm_year;
}

// GET WEEKDAY
int dt::CTime::getWeekday() const 
{
	struct tm* pTm = localtime(&_time);
    return pTm->tm_wday;
}

// GET DAY OF YEAR
int dt::CTime::getYearDay() const 
{
	struct tm* pTm = localtime(&_time);
    return pTm->tm_yday;
}

bool dt::CTime::isDayLightSavings() const 
{
	struct tm* pTm = localtime(&_time);
    return static_cast<bool>(pTm->tm_isdst);
}

bool dt::CTime::isLeapYear() const 
{
	struct tm* pTm = localtime(&_time);
    int year = pTm->tm_year;
    return (year%4 == 0 && year%100 !=0) || year%400 == 0;
}

/******************************** SETTERS *************************************/
// SET DAY
dt::CTime& dt::CTime::setDay(int day)
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
dt::CTime& dt::CTime::setMonth(int day)
{
	return *this;
}

// SET DAY
dt::CTime& dt::CTime::setYear(int day)
{
	return *this;
}

/************************* ADD UNITS*******************************************/
// ADD DAYS
dt::CTime& dt::CTime::addDays(int ndays) 
{
	struct tm* pTm = localtime(&_time);
    pTm->tm_mday += ndays;
    std::mktime(pTm);
    return *this;
}

// ADD MONTHS
dt::CTime& dt::CTime::addMonths(int nmonths) 
{
	struct tm* pTm = localtime(&_time);
    pTm->tm_mon += nmonths;
    _time = std::mktime(pTm);
    return *this;
}

// ADD YEARS
dt::CTime& dt::CTime::addYears(int nyears) 
{
	struct tm* pTm = localtime(&_time);
    pTm->tm_year += nyears;
    _time = std::mktime(pTm);
    return *this;
}

/********************* STATIC FUNCTIONS ***************************************/
// GET DIFF TIME
double dt::CTime::getDiffTime(const dt::CTime &ct2, const dt::CTime &ct1) 
{
    return std::difftime(ct2._time, ct1._time);
}

/************************** HELPER FUNCTIONS **********************************/
bool dt::operator==(const dt::CTime &t1, const dt::CTime &t2) 
{
    return t1.operator==(t2);
}

bool dt::operator!=(const dt::CTime &t1, const dt::CTime &t2) 
{
    return t1.operator!=(t2);
}

double dt::operator-(const CTime& t1, const CTime& t2)
{
	return dt::CTime::getDiffTime(t2, t1);
}

std::ostream& dt::operator<<(std::ostream &out, const dt::CTime &src) 
{
    out << src.asciiTime();
    return out;
}

dt::CTime dt::CTime::currentCTime() 
{
    struct std::tm* temp_tm;
    std::time_t t_now = std::time(nullptr);
    temp_tm = localtime(&t_now);
    mktime(temp_tm);
    return CTime{&t_now};
}

std::string dt::CTime::currentAscTime() 
{
    CTime now {currentCTime()};
    return now.asciiTime();
}


std::string dt::CTime::currentISOTime() 
{
    CTime now {currentCTime()};
    return now.iso8610Str();
}
