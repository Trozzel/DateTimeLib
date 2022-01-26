//
// Created by George Ford on 3/13/21.
//
#include "dt_tools.hpp"

/* Must be in format: "YYYY-MM-DD HH:MM:SS" */
bool dt::isValidIso8610(const char* iso8610str) {
    return (strlen(iso8610str) == 19  &&
                iso8610str[4]  == '-' &&
                iso8610str[7]  == '-' &&
                iso8610str[10] == ' ' &&
                iso8610str[13] == ':' &&
                iso8610str[16] == ':');
}

bool dt::isValidDate(int y, int m, int d) {
    // 1. IS VALID YEAR
    bool isValid = (y>=1900) && (y<=2500);
    if (isValid) {
        // 2. IS VALID MONTH
        isValid = (m>=0) && (m<=11);
        if (isValid) {
            // 3. IS VALID DAY
            // 3a. IS LEAP YEAR
            bool isLeapYear = (y%4 == 0 && y%100 != 0) || y%400 == 0;
            int idx = isLeapYear? 1 : 0;
            isValid = d <= dt::Months[m].second[idx];
        }
    }
    return isValid;
}
