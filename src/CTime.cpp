//
// Created by George Ford on 3/13/21.
//
#include <sstream>
#include "CTime.hpp"

using namespace std;

// DEFAULT CTOR - defaults to 0630
dt::CTime::CTime() 
{
    std::time_t t_now = std::time(nullptr);
    _pTm = localtime(&t_now);
    //m_ptm->tm_hour = 6;
    //m_ptm->tm_min  = 30;
    //m_ptm->tm_sec  = 0;
    mktime(_pTm);
}

// CTOR WITH std::time_t
dt::CTime::CTime(const time_t* time) 
{
    _pTm = std::localtime((time));
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

    std::time_t t = std::time(nullptr);
    _pTm = localtime(&t);
    _pTm->tm_year = y - 1900;
    _pTm->tm_mon  = mon - 1;
    _pTm->tm_mday = d;
    _pTm->tm_hour = hr;
    _pTm->tm_min  = minute;
    _pTm->tm_sec  = sec;
    if (!dt::isValidDate(y, mon-1, d))
        throw std::runtime_error("Not a valid entry date");
    std::mktime(_pTm);
}

// CTOR WITH INTS
dt::CTime::CTime(int y, int m, int d) 
{
    if (!isValidDate(y, m, d)) {
        std::stringstream ss;
        ss << "(" << y << ", " << m << ", " << d << ")";
        throw std::invalid_argument(ss.str() + " are in values for CTime");
    }
    std::time_t t = std::time(nullptr);
    _pTm = localtime(&t);
    _pTm->tm_year = y - 1900;
    _pTm->tm_mon  = m - 1;
    _pTm->tm_mday = d;

    // ADD DEFAULT VALUES
    _pTm->tm_hour = 6;
    _pTm->tm_min  = 30;
    _pTm->tm_sec  = 0;
    std::mktime(_pTm);
}

/************************* BOOLEAN OPERATORS **********************************/
bool dt::CTime::operator==(const dt::CTime& src) const 
{
    return getDiffTime(*this, src) == 0;
        //m_ptm->tm_sec    == src.m_ptm->tm_sec    &&
        //m_ptm->tm_min    == src.m_ptm->tm_min    &&
        //m_ptm->tm_hour   == src.m_ptm->tm_hour   &&
        //m_ptm->tm_mday   == src.m_ptm->tm_mday   &&
        //m_ptm->tm_year   == src.m_ptm->tm_year   &&
        //m_ptm->tm_yday   == src.m_ptm->tm_yday   &&
        //m_ptm->tm_wday   == src.m_ptm->tm_wday   &&
        //m_ptm->tm_mon    == src.m_ptm->tm_mon    &&
        //m_ptm->tm_isdst  == src.m_ptm->tm_isdst  &&
        //m_ptm->tm_gmtoff == src.m_ptm->tm_gmtoff &&
        //m_ptm->tm_zone   == src.m_ptm->tm_zone ;
}

bool dt::CTime::operator!=(const dt::CTime& src) const 
{

    return getDiffTime(*this, src) != 0;
        //m_ptm->tm_sec    != src.m_ptm->tm_sec    ||
        //m_ptm->tm_min    != src.m_ptm->tm_min    ||
        //m_ptm->tm_hour   != src.m_ptm->tm_hour   ||
        //m_ptm->tm_mday   != src.m_ptm->tm_mday   ||
        //m_ptm->tm_year   != src.m_ptm->tm_year   ||
        //m_ptm->tm_yday   != src.m_ptm->tm_yday   ||
        //m_ptm->tm_wday   != src.m_ptm->tm_wday   ||
        //m_ptm->tm_mon    != src.m_ptm->tm_mon    ||
        //m_ptm->tm_isdst  != src.m_ptm->tm_isdst  ||
        //m_ptm->tm_gmtoff != src.m_ptm->tm_gmtoff ||
        //m_ptm->tm_zone   != src.m_ptm->tm_zone ;
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
std::string dt::CTime::getAscTime() const 
{
    return std::string(asctime(_pTm));
}

// GET ISO-8610 STRING
std::string dt::CTime::getIso8610Str() const 
{
    char datetime[20];
    std::strftime(datetime, 20, "%Y-%m-%d %H:%M:%S", _pTm);
    return std::string { datetime };
}

// GET HOUR
int dt::CTime::getHour() const 
{
    return _pTm->tm_hour;
}

// GET DAY
int dt::CTime::getMDay() const 
{
    return _pTm->tm_mday;
}

// GET MONTH
int dt::CTime::getMonth() const 
{
    return _pTm->tm_mon;
}

// GET YEAR
int dt::CTime::getYear() const 
{
    return _pTm->tm_year;
}

// GET WEEKDAY
int dt::CTime::getWeekday() const 
{
    return _pTm->tm_wday;
}

// GET DAY OF YEAR
int dt::CTime::getYearDay() const 
{
    return _pTm->tm_yday;
}

bool dt::CTime::isDayLightSavings() const 
{
    return static_cast<bool>(_pTm->tm_isdst);
}

bool dt::CTime::isLeapYear() const 
{
    int year = _pTm->tm_year;
    return (year%4 == 0 && year%100 !=0) || year%400 == 0;
}

/******************************** SETTERS *************************************/
// SET DAY
dt::CTime& dt::CTime::setDay(int day)
{
	// CHECK TO SEE IF THIS IS A VALID DAY
    int year  = _pTm->tm_year; 
    int month = _pTm->tm_mon;

	if (isValidDate(year, month, day))
		_pTm->tm_mday = day;
	else // DO NOT UPDATE THE DAY
		cout << "WARNING: " << day << " is not a valid day for " 
			 << Months[_pTm->tm_mon].first << ", " << _pTm->tm_year << endl;

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
    _pTm->tm_mday += ndays;
    std::mktime(_pTm);
    return *this;
}

// ADD MONTHS
dt::CTime& dt::CTime::addMonths(int nmonths) 
{
    _pTm->tm_mon += nmonths;
    std::mktime(_pTm);
    return *this;
}

// ADD YEARS
dt::CTime& dt::CTime::addYears(int nyears) 
{
    _pTm->tm_year += nyears;
    std::mktime(_pTm);
    return *this;
}

/********************* STATIC FUNCTIONS ***************************************/
// GET DIFF TIME
double dt::CTime::getDiffTime(const dt::CTime &ct1, const dt::CTime &ct2) 
{
    std::time_t t1 = std::mktime(ct1._pTm);
    std::time_t t2 = std::mktime(ct2._pTm);
    return std::difftime(t2, t1);
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

std::ostream& dt::operator<<(std::ostream &out, const dt::CTime &src) 
{
    out << src.getAscTime();
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
    return now.getAscTime();
}


std::string dt::CTime::currentISOTime() 
{
    CTime now {currentCTime()};
    return now.getIso8610Str();
}
