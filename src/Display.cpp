#include "Display.h"
#include "Config.h"

GxEPD2_3C<GxEPD2_420c_1680, GxEPD2_420c_1680::HEIGHT> display(
        GxEPD2_420c_1680(/*CS=D8*/ SS, /*DC*/ PIN_DC, /*RST*/ PIN_RES, /*BUSY*/ PIN_BUSY)); //
U8G2_FOR_ADAFRUIT_GFX u8g2Fonts;

void displayInit() {
    display.init(115200);
    display.setRotation(0);
    u8g2Fonts.begin(display);
    u8g2Fonts.setForegroundColor(GxEPD_BLACK);  // 设置前景色
    u8g2Fonts.setBackgroundColor(GxEPD_WHITE);  // 设置背景色
}

uint8_t getFontHeight() {
    return u8g2Fonts.getFontAscent() - u8g2Fonts.getFontDescent(); // get font height
}


// 获取从start 至 end 水平居中的x坐标
uint16_t getCenter_X(uint16_t start, uint16_t end, uint16_t width) {
    return start + ((end - start - width) / 2);
}

// 获取从start 至 end 水平居中的x坐标
uint16_t getCenterText_X(const char *s, uint16_t start, uint16_t end) {
    return start + ((end - start - u8g2Fonts.getUTF8Width(s)) / 2);
}

uint16_t getCenter_Y(uint16_t top, uint16_t bottom, uint16_t height) {
    return top + ((bottom - top - height) / 2);
}

uint16_t text(const char *str, int16_t x, int16_t y, bool w2l, uint16_t fg_color,
             uint16_t bg_color) {
    u8g2Fonts.setFontMode(1);
    u8g2Fonts.setBackgroundColor(bg_color);
    u8g2Fonts.setForegroundColor(fg_color);
    uint16_t baseline = u8g2Fonts.getFontAscent() + 2;

    if (w2l) {
        u8g2Fonts.drawUTF8(x - u8g2Fonts.getUTF8Width(str), y + baseline, str);
        return x - u8g2Fonts.getUTF8Width(str);
    } else {
        u8g2Fonts.drawUTF8(x, y + baseline, str);
        return x + u8g2Fonts.getUTF8Width(str);
    }
}

void displayCenterText_X(const char *s, uint16_t start, uint16_t end, uint16_t y) {
    u8g2Fonts.drawUTF8(getCenterText_X(s, start, end), y, s);
}

void display_info(const String &zf) {
    display.firstPage();
    do {
        display.fillScreen(GxEPD_WHITE);
        displayCenterText_X(zf.c_str(),
                            0,
                            display.width(),
                            getCenter_Y(0, display.height(), getFontHeight()));
    } while (display.nextPage());

    display.powerOff(); //关闭屏幕电源
    display.hibernate();
}







