//
// Created by buf on 2024/3/10.
//
#include "DisplayWeather.h"
#include "Arduino.h"
#include "Display.h"
#include "weather.h"

void displayWeather(WeatherNow weatherNow, Forecast forecast) {
    u8g2Fonts.setFont(TEXT14_GB);
    u8_t margin = 2;
    u8_t font_size = getFontHeight();
    String str = "";
    u16_t weather_mid = (SCREEN_WIDTH - CALENDAR_END) / 2 + CALENDAR_END;
    u16_t weather_x = getCenter_X(CALENDAR_END, weather_mid, ICON_SIZE);
    u16_t pos_y = getCenter_Y(ACTURE_WEATHER_SPLIT, FUTURE_WEATHER_SPLIT, ICON_SIZE + font_size + margin);

    str = weatherNow.getWeatherText().c_str();
    text(str.c_str(), getCenterText_X(str.c_str(), weather_x, weather_x + ICON_SIZE), pos_y + ICON_SIZE + margin);

    margin = 4;
    Serial.println(weatherNow.getWeatherText());
    display.drawBitmap(weather_x, pos_y, MapIcon(weatherNow.getWeatherText()), ICON_SIZE, ICON_SIZE, GxEPD_BLACK);

    u8g2Fonts.setFont(TEXT35_FUB);
    u16_t temp =
        getCenter_Y(ACTURE_WEATHER_SPLIT, FUTURE_WEATHER_SPLIT, u8g2Fonts.getFontAscent() - u8g2Fonts.getFontDescent());
    text((String(weatherNow.getDegree()) + "°").c_str(), SCREEN_WIDTH - margin, temp + 3, true);



    u8_t weather_box_w = (SCREEN_WIDTH - CALENDAR_END) / 3;
    u8_t weather_box_h = SCREEN_HEIGHT - FUTURE_WEATHER_SPLIT;
    Serial.print("weather_box_w： ");
    Serial.println(weather_box_w);
    Serial.print("weather_box_h： ");
    Serial.println(weather_box_h);

    pos_y = FUTURE_WEATHER_SPLIT;
    u8g2Fonts.setFont(TEXT12_GB);
    margin = 2;
    font_size = getFontHeight();
    display.fillRect(CALENDAR_END, FUTURE_WEATHER_SPLIT, SCREEN_WIDTH - CALENDAR_END, margin * 2 + font_size,
                     GxEPD_BLACK);
    pos_y += margin * 2 + font_size;
    String future_day[] = {"今天", "明天", "后天"};
    for (u8_t i = 0; i < 3; i++) {
        display.drawFastVLine(i * weather_box_w + CALENDAR_END, FUTURE_WEATHER_SPLIT, weather_box_h, GxEPD_BLACK);
        
        str = future_day[i];
        text(str.c_str(),
        getCenterText_X(str.c_str(), i * weather_box_w + CALENDAR_END,
                       i * weather_box_w + CALENDAR_END + weather_box_w),
                       getCenter_Y(FUTURE_WEATHER_SPLIT, font_size + margin * 2 + FUTURE_WEATHER_SPLIT, font_size),
                       false,
                       GxEPD_WHITE, GxEPD_BLACK);
        
        display.drawBitmap(
            getCenter_X(i * weather_box_w + CALENDAR_END, (i + 1) * weather_box_w + CALENDAR_END, ICON_SIZE_16),
            pos_y + margin, MapIcon_16(forecast.getDayText(i)), ICON_SIZE_16, ICON_SIZE_16, GxEPD_BLACK);
        
        str = String(forecast.getHigh(i)) + "℃";
        text(str.c_str(),
        getCenterText_X(str.c_str(),
        CALENDAR_END + weather_box_w * i,
                       CALENDAR_END + weather_box_w * (i + 1)),
                       pos_y + margin * 2 + ICON_SIZE_16);
        
        display.drawBitmap(
            getCenter_X(i * weather_box_w + CALENDAR_END, (i + 1) * weather_box_w + CALENDAR_END, ICON_SIZE_16),
            SCREEN_HEIGHT - ICON_SIZE_16 - margin, MapIcon_16(forecast.getNightText(i)), ICON_SIZE_16, ICON_SIZE_16,
            GxEPD_BLACK);

        str = String(forecast.getLow(i)) + "℃";
        text(str.c_str(),
        getCenterText_X(str.c_str(), CALENDAR_END + weather_box_w * i,
                       CALENDAR_END + weather_box_w * (i + 1)),
                       SCREEN_HEIGHT - margin * 2 - ICON_SIZE_16 - 10);
    }
}