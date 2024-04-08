#ifndef WEATHER_H
#define WEATHER_H

#include "main.h"
#include "Seniverse.h"
#define ICON_SIZE   32  // 32x32 weather icon size
#define ICON_SIZE_16   16  // 16x16 weather icon size

ReturnStatus_t
getWeather(WeatherNow &weatherNow, Forecast &forecast);
const uint8_t* MapIcon(const String weather_icon);
const uint8_t* MapIcon_16(const String weather_icon);

#endif  /* WEATHER_H */
