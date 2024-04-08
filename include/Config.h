//
// Created by buf on 2024/3/5.
//
#define DEBUG
#ifndef CONFIG_H
#define CONFIG_H
#include "Arduino.h"

#ifdef DEBUG
#define debug_println(msg)   \
    Serial.print("debug: "); \
    Serial.println(msg)
#define debug_print(msg) Serial.print(msg)
#else
#define debug_println(msg)
#define debug_print(msg)

#endif



#define US_TO_S_FACTOR          1000000U
#define REFRESH_INTERVAL        (3600U * 4)    // 4 hour

#define XINZHI_API_KEY        "" // 心知天气API KEY
#define MY_COUNTRY_CODE         "zh-Hans"

#define JUHE_API_KEY            ""  // 聚合数据老黄历API KEY

#define GMT_OFFSET_SEC          (3600 * 8)
#define NTP_SERVER1              "cn.pool.ntp.org"  // 国内NTP server
#define NTP_SERVER2              "pool.ntp.org"  // 国内NTP server
#define NTP_SERVER3              "ntp.sjtu.edu.cn"  // 国内NTP server


#define PIN_BUSY 0  // 白
#define PIN_RES 1  // 绿
#define PIN_DC 2    // 紫
// SS 7 蓝
// SCLK 4 黄
// MOSI 6 橙

#define PIN_RGB 8
#define PIN_REST_WIFI 5
#define PIN_LED 20
#define PIN_BTN 10
#define PIN_DHT11 3


#endif
