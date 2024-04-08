#pragma once

#include "Arduino.h"
#include "GxEPD2_3C.h"
#include "U8g2_for_Adafruit_GFX.h"

#define SCREEN_WIDTH        400
#define SCREEN_HEIGHT       300
#define CALE_WIDTH         CALENDAR_END
#define CALENDAR_END 280
#define CALENDAR_TOP 60
#define LUNAR_SPLIT 70
#define DHT11_SPLIT 110
#define ACTURE_WEATHER_SPLIT 160
#define FUTURE_WEATHER_SPLIT 210
#define BOX_SIZE 40
#define CALENDAR_HEAD_HEIGHT 32


#define TEXT16_GB (u8g2_font_wqy16_t_gb2312)
#define TEXT14_GB (u8g2_font_wqy14_t_gb2312)
#define TEXT12_GB (u8g2_font_wqy12_t_gb2312)
#define TEXT16_MN (u8g2_font_inb16_mn)
#define TEXT19_MN (u8g2_font_inb19_mn)
#define TEXT38_MN (u8g2_font_inb38_mn)
#define TEXT35_FUB (u8g2_font_fub35_tf)

// extern GxEPD2_3C<GxEPD2_420c_1680, GxEPD2_420c_1680::HEIGHT> display;
extern GxEPD2_3C<GxEPD2_420c_GDEY042Z98, GxEPD2_420c_GDEY042Z98::HEIGHT> display;
extern U8G2_FOR_ADAFRUIT_GFX u8g2Fonts;

void displayInit();
uint16_t getCenterText_X(const char *s, uint16_t start, uint16_t end);
void displayCenterText_X(const char *s, uint16_t start, uint16_t end, uint16_t y);
uint8_t getFontHeight();
uint16_t text(const char *str, int16_t x, int16_t y, bool w2l = false, uint16_t fg_color = GxEPD_BLACK,
              uint16_t bg_color = GxEPD_WHITE);
uint16_t getCenter_X(uint16_t start, uint16_t end, uint16_t width);
uint16_t getCenter_Y(uint16_t top, uint16_t bottom, uint16_t height);
void display_info(const String &zf);
void displayDate(struct tm date_today);