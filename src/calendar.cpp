#include "calendar.h"
#include "utils.h"
#include "Config.h"

/**
 * @brief get the date of today
 * 
 * @return struct tm 
 */
ReturnStatus_t getCurrentDate(struct tm & date) {
    configTime(GMT_OFFSET_SEC, 0, NTP_SERVER1, NTP_SERVER2, NTP_SERVER3);
    u8_t count = 0;

    while (!getLocalTime(&date)) {
        debug_println("Failed to obtain time");
        WiFi.reconnect();
        if (count++ > 4) {
            ESP.restart();
        }
        delay(1000);
    }

    date.tm_year += 1900;
    date.tm_mon += 1;

    return SUCCESS;
}

/**
 * @brief checks if the given year is leap year
 * 
 * @param year 
 * @return true 
 * @return false 
 */
bool isLeapYear(int year) {
    if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
        return true;

    return false;
}

/**
 * @brief get the total days in a month
 * 
 * @param date 
 * @return int 
 */
int getDaysInMonth(struct tm *date) {
    int days_in_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int year = date->tm_year;
    int mon = date->tm_mon;

    /* return the month days (other than Feb.)*/
    if (mon != 2)
        return days_in_month[(mon - 1) % 12];

    /* return Feb. month days depending on the year */
    if (isLeapYear(year))
        return 29;

    return 28;
}

/**
 * @brief get the lunar calendar for the given date
 * 
 * @param pDate 
 * @param pLunarDate 
 * @return ReturnStatus_t 
 */
ReturnStatus_t getLunarDate(struct tm *pDate, lunar_date_t *pLunarDate) {
    ReturnStatus_t status = SUCCESS;

    int year = pDate->tm_year;
    int mon = pDate->tm_mon;
    int mday = pDate->tm_mday;

    String url =
            "https://v.juhe.cn/calendar/day?date=" + String(year) + "-" + String(mon) + "-" + String(mday) + "&key=" +
            JUHE_API_KEY;

    String payload = httpGetRqst(url);

    StaticJsonDocument<1024> doc;

    DeserializationError error = deserializeJson(doc, payload);
    if (error) {
        debug_print("deserializeJson() failed: ");
        debug_println(error.c_str());
        status = UNSUCCESS;
    }
    debug_println("hhhhhhhhhhhhhhhhhhhhhhhhhhh");
    
//    strcpy(pLunarDate->animals_year, doc["result"]["data"]["animalsYear"]);
//    strcpy(pLunarDate->lunar_year, doc["result"]["data"]["lunarYear"]);
//    strcpy(pLunarDate->lunar_date, doc["result"]["data"]["lunar"]);
//    strcpy(pLunarDate->holiday, doc["result"]["data"]["holiday"]);
    if (!doc["result"]["data"]["suit"].isNull()) {
        pLunarDate->suit = doc["result"]["data"]["suit"].as<String>();
    }
    if (!doc["result"]["data"]["avoid"].isNull()) {
        pLunarDate->avoid = doc["result"]["data"]["avoid"].as<String>();
    }
    return status;
}