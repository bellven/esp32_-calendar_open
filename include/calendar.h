#ifndef _CALENDAR_H
#define _CALENDAR_H

#include "main.h"
#include "ArduinoJson.h"
#include <time.h>

typedef struct lunar_date_t
{
    char animals_year[10];
    char lunar_year[20];
    char lunar_date[20];
    char holiday[30];
    String suit;
    String avoid;
}lunar_date_t;

ReturnStatus_t getCurrentDate(struct tm & date);
extern bool isLeapYear(int year);
extern int getDaysInMonth(struct tm *date);
extern ReturnStatus_t getLunarDate(struct tm *pDate, lunar_date_t *pLunarDate);

#endif