//
// Created by buf on 2024/3/10.
//
#include "DisplayCalendar.h"
#include "Display.h"
#include "Utils.h"
#include "xDate.h"

/**
 * @brief display the calendar month table
 *
 */
void displayMonthCalendar(struct tm date_today) {
    const uint8_t calender_head_y = CALENDAR_TOP - CALENDAR_HEAD_HEIGHT;

    uint16_t pos_x = 0, pos_y = 0, marrgin = 2;

    // 画年
    uint16_t year = date_today.tm_year;
    u8g2Fonts.setFont(TEXT19_MN);
    pos_x = 6;
    pos_y = calender_head_y - getFontHeight();
    String str = String(year);
    pos_x = text(str.c_str(), pos_x, pos_y);

    u8g2Fonts.setFont(TEXT16_GB);
    pos_y = calender_head_y - getFontHeight() - marrgin * 2;
    text("年", pos_x + marrgin, pos_y);

    // 画月
    u8g2Fonts.setFont(TEXT16_GB);
    pos_x = CALENDAR_END - marrgin * 3;
    pos_y = calender_head_y - getFontHeight() - marrgin * 2;
    pos_x = text("月", pos_x, pos_y, true);

    u8g2Fonts.setFont(TEXT19_MN);
    uint16_t mon = date_today.tm_mon;
    str = String(mon);
    pos_x -= marrgin;
    pos_y = calender_head_y - getFontHeight();
    text(str.c_str(), pos_x, pos_y, true);

    // 画日历头
    display.fillRect(0, CALENDAR_TOP - CALENDAR_HEAD_HEIGHT, CALENDAR_END, CALENDAR_HEAD_HEIGHT, GxEPD_BLACK);
    const String dows_t[7] = {"日", "一", "二", "三", "四", "五", "六"};

    // 高亮双休日
    u8g2Fonts.setFont(TEXT16_GB);
    for (int i = 0; i < 7; i++) {
        if (i == 0) {
            u8g2Fonts.setBackgroundColor(GxEPD_RED);
            u8g2Fonts.setForegroundColor(GxEPD_WHITE);
            display.fillRect(0, CALENDAR_TOP - CALENDAR_HEAD_HEIGHT, BOX_SIZE, CALENDAR_HEAD_HEIGHT, GxEPD_RED);
        } else if (i == 6) {
            u8g2Fonts.setBackgroundColor(GxEPD_RED);
            u8g2Fonts.setForegroundColor(GxEPD_WHITE);
            display.fillRect(CALENDAR_END - BOX_SIZE, CALENDAR_TOP - CALENDAR_HEAD_HEIGHT, BOX_SIZE,
                             CALENDAR_HEAD_HEIGHT, GxEPD_RED);
        }
        text(dows_t[i].c_str(), getCenterText_X(dows_t[i].c_str(), i * BOX_SIZE, (i + 1) * BOX_SIZE),
             getCenter_Y(CALENDAR_TOP - CALENDAR_HEAD_HEIGHT, CALENDAR_TOP, getFontHeight()), false, GxEPD_WHITE,
             GxEPD_BLACK);
        u8g2Fonts.setBackgroundColor(GxEPD_BLACK);
        u8g2Fonts.setForegroundColor(GxEPD_WHITE);
    }
    // 计算数据
    // 计算出周日在的日期day
    int8_t day = date_today.tm_mday - date_today.tm_wday;
    uint8_t days_of_month = xDate::MonthDays(date_today.tm_year, date_today.tm_mon);
    // 找出月初的日期数 day可能是负数
    while (day > 1)
        day -= 7;

    uint32_t Year = date_today.tm_year;
    uint8_t Month = date_today.tm_mon;

    WORD iLunarYear, iLunarMonth, iLunarDay;

    // 开始绘制

    String str_day = String(day);
    pos_y = CALENDAR_TOP;
    uint8_t padding = 2;
    while (day <= days_of_month) {
        // 20 为数字的高度
        uint8_t day_font_height = 20, lunar_font_height = 14;
        uint16_t text_top = getCenter_Y(pos_y, pos_y + BOX_SIZE, lunar_font_height + day_font_height + padding);
        for (int i = 0; i < 7; i++) {
            pos_x = BOX_SIZE * i;
            // 如果是负数不打印直接跳过
            if ((day >= 1) && (day <= days_of_month)) {
                uint8_t solar_term_index = xDate::GetLunarDate(Year, Month, day, iLunarYear, iLunarMonth, iLunarDay);
                String solar_term = xDate::mapSolarTerm(solar_term_index);
                String day_chinese = xDate::FormatLunarDay(iLunarDay);
                String mon_chinese = xDate::FormatLunarMonth(iLunarMonth);
                // highlight today with filled red circle
                if (day == date_today.tm_mday) {
                    display.fillRoundRect(pos_x, pos_y, BOX_SIZE, BOX_SIZE, 5, GxEPD_RED);
                    u8g2Fonts.setFont(TEXT16_MN);
                    str = String(day);
                    text(str.c_str(), getCenterText_X(str.c_str(), pos_x, pos_x + BOX_SIZE), text_top, false,
                         GxEPD_WHITE, GxEPD_RED);
                    u8g2Fonts.setFont(TEXT14_GB);

                    str = (day_chinese == "初一") ? mon_chinese : ((solar_term == "") ? day_chinese : solar_term);

                    text(str.c_str(), getCenterText_X(str.c_str(), pos_x, pos_x + BOX_SIZE),
                         text_top + padding + day_font_height, false, GxEPD_WHITE, GxEPD_RED);

                } else {
                    u8g2Fonts.setFont(TEXT16_MN);
                    str = String(day);
                    text(str.c_str(), getCenterText_X(str.c_str(), pos_x, pos_x + BOX_SIZE), text_top);

                    u8g2Fonts.setFont(TEXT14_GB);
                    str = (day_chinese == "初一") ? mon_chinese : ((solar_term == "") ? day_chinese : solar_term);
                    text(str.c_str(), getCenterText_X(str.c_str(), pos_x, pos_x + BOX_SIZE),
                         text_top + padding + day_font_height);
                }
            }
            day++;
        }
        pos_y += BOX_SIZE;
    }
}

/**
 * @brief display today's date information
 *
 */
void displayDate(struct tm date_today) {
    // ===========处理数据=======
    uint32_t Year = date_today.tm_year;
    uint8_t Month = date_today.tm_mon;
    uint8_t Day = date_today.tm_mday;

    WORD iLunarYear, iLunarMonth, iLunarDay;
    xDate::GetLunarDate(Year, Month, Day, iLunarYear, iLunarMonth, iLunarDay);

    String lunar_year = xDate::FormatLunarYear(iLunarYear);
    String mon_chinese = xDate::FormatLunarMonth(iLunarMonth);
    String day_chinese = xDate::FormatLunarDay(iLunarDay);

    String ludary_date = String(mon_chinese) + String(day_chinese);

    // ==========画数据==========
    // 画日期
    u8g2Fonts.setFont(TEXT38_MN);
    uint8_t padding = 10;
    uint8_t font_size = getFontHeight() - 5;
    display.fillRoundRect(getCenter_X(CALENDAR_END, SCREEN_WIDTH, font_size * 2),
                          getCenter_Y(0, LUNAR_SPLIT, font_size) - padding, font_size * 2, font_size + padding * 2, 10,
                          GxEPD_RED);

    String str = "";
    str = String(Day);
    text(str.c_str(), getCenterText_X(str.c_str(), CALENDAR_END, SCREEN_WIDTH), getCenter_Y(0, LUNAR_SPLIT, font_size),
         false, GxEPD_WHITE, GxEPD_RED);

    // 画阴历
    u8g2Fonts.setFont(TEXT14_GB);
    font_size = getFontHeight();
    padding = 2;
    u8_t margin = 3;
    str = lunar_year;
    text(str.c_str(), getCenterText_X(str.c_str(), CALENDAR_END, SCREEN_WIDTH), LUNAR_SPLIT + margin);
    str = ludary_date;
    text(str.c_str(), getCenterText_X(str.c_str(), CALENDAR_END, SCREEN_WIDTH), LUNAR_SPLIT + margin + font_size + padding);
}

void displayAdvice(lunar_date_t lunar_date_t) {
    u8g2Fonts.setFont(TEXT14_GB);
    uint8_t font_size = getFontHeight();
    uint8_t margin = 4;
    String suit = lunar_date_t.suit;
    String avoid = lunar_date_t.avoid;
    String temp = splitString(suit, 4);
    if (temp == "") {
        suit += " [宜]";
    } else {
        suit = temp + " [宜]";
    }

    temp = splitString(avoid, 4);
    if (temp == "") {
        avoid += " [忌]";
    } else {
        avoid = temp + " [忌]";
    }

    Serial.println("++++++++++++++++++++++++++++++");
    Serial.println(suit);
    Serial.println(avoid);
    Serial.println("++++++++++++++++++++++++++++++");
    uint16_t pos_y = getCenter_Y(SCREEN_HEIGHT - 40, SCREEN_HEIGHT, font_size * 2 + margin);

    text(suit.c_str(), CALENDAR_END - margin, pos_y, true);
    pos_y += font_size + margin;

    text(avoid.c_str(), CALENDAR_END - margin, pos_y, true, GxEPD_RED);
}