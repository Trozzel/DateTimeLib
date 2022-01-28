//
// Created by George Ford on 3/13/21.
//

#ifndef LIBDATETIME_ST_TOOLS_H
#define LIBDATETIME_ST_TOOLS_H

#include <vector>
#include <string>

namespace dt {
// WEEKDAYS
const std::vector<std::string> Weekdays{
    "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
};

// MONTHS
/***************************************************************************
* Months contains amount of days per month for regular and non-leap year
*/
using vec_of_pairs_t = std::vector<std::pair<std::string, std::vector<int>>>;
const vec_of_pairs_t Months {
    { "January",   {31,31} },
    { "February",  {28,29} },
    { "March",     {31,31} },
    { "April",     {30,30} },
    { "May",       {31,31} },
    { "June",      {30,30} },
    { "July",      {30,30} },
    { "August",    {31,31} },
    { "September", {30,30} },
    { "October",   {31,31} },
    { "November",  {30,30} },
    { "December",  {31,31} }
};

// IS VALID ISO-8610 STRING
/***************************************************************************
* Must be in format: "YYYY-MM-DD HH:MM:SS"
* See: https://sqlite.org/lang_datefunc.html
* @param iso8610str
* @return
*/
bool isValidIso8610(const char* iso8610str);

// IS VALID DATE
/*******************************************************************************
 * Verifies that the given Year, Month and Day are valid entries
 */
bool isValidDate(int y, int m, int d);

// REPEAT TYPE
/*******************************************************************************
 * Describes different manners in which a CTime object can repeat
 */
enum class RepeatType {
	Daily, Weekly, Monthly, Yearly
};

} /* namespace dt */

#endif //LIBDATETIME_ST_TOOLS_H
