//
// Created by buf on 2024/3/10.
//

#ifndef ESP8266_CALENDAR_DISPLAYCALENDAR_H
#define ESP8266_CALENDAR_DISPLAYCALENDAR_H

#include "Arduino.h"
#include "Calendar.h"

void displayMonthCalendar(struct tm date_today);

void displayAdvice(lunar_date_t lunar_date_t);

#endif //ESP8266_CALENDAR_DISPLAYCALENDAR_H
