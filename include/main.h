/**
 * @brief main header file for saving macros and hardware pinouts for LuatOS ESP32-C3 development board
 * Board Link: https://wiki.luatos.com/chips/esp32c3/board.html
 *
 */
#ifndef MAIN_H
#define MAIN_H

#include "config.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <SPI.h>
#include <GxEPD2_3C.h>
#include <U8g2_for_Adafruit_GFX.h>
#include <cstring>
struct News            // 新闻API
{
    char status_code[64];  // 错误代码
    char title[11][64];
};
struct Hitokoto  // 一言API
{
    char status_code[64];  // 错误代码
    char hitokoto[64];
};

typedef enum ReturnStatus_t
{
    UNSUCCESS = 0,
    SUCCESS = 1
}ReturnStatus_t;


#endif
