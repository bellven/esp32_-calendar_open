#include "main.h"
#include <Seniverse.h>
#include "DHT.h"
#include "Display.h"
#include "DisplayCalendar.h"
#include "DisplayWeather.h"
#include "Ticker.h"
#include "WifiHandle.h"
#include "utils.h"
#include "weather.h"

void InitSystem(uint32_t baud);

ReturnStatus_t getTHData(u8_t &h, u8_t &t);

u32_t second = 0;
u8_t older_day = 255;
Ticker ticker;
Ticker ticker_s;
//ReturnStatus_t status;

void tick_s() {
    second++;
}

struct tm date_today;
lunar_date_t lunarDate;

/**
 * @brief display the main page information
 *
 */
void displayMainPage() {
    ticker.attach(0.5, toggleLed);
    ReturnStatus_t status;
    WeatherNow weatherNow;
    Forecast forecast;
    u8_t h, t;
    // 获取温湿度
    while (getTHData(h, t) == UNSUCCESS) {
        debug_println("Failed to read from DHT sensor!");
        delay(100);
    }
    debug_println("=====getTHData=========");
    debug_println(String(t) +"C");
    debug_println(String(h) +"%");
    debug_println("=======================");

    while (getWeather(weatherNow, forecast) == UNSUCCESS) {
        debug_println("Failed to obtain weather information");
        delay(100);
    }
    debug_println("=====weatherNow=========");
    debug_println(weatherNow.getWeatherCity());
    debug_println(weatherNow.getWeatherText());
    debug_println(weatherNow.getDegree());
    debug_println(weatherNow.getLastUpdate());
    debug_println("=======================");

    for (u8_t i = 0; i < 3; i++) {
        debug_print("======forecast==========\n");
        debug_println(i);
        debug_println(forecast.getDayText(i));
        debug_println(forecast.getHigh(i));
        debug_println(forecast.getLow(i));

        debug_println("=======================");
    }

    display.firstPage();
    ticker.attach(1, toggleLed);
    do {
        display.fillRect(0, CALENDAR_TOP - CALENDAR_HEAD_HEIGHT, CALENDAR_END, CALENDAR_HEAD_HEIGHT, GxEPD_BLACK);
        // 画边界
        display.drawRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, GxEPD_BLACK);

        // 画分割线
        display.drawFastVLine(SCREEN_WIDTH, 0, SCREEN_HEIGHT, GxEPD_BLACK);
        display.drawFastVLine(CALENDAR_END, 0, SCREEN_HEIGHT, GxEPD_BLACK);

        u8_t margin = 0;
        display.drawFastHLine(CALENDAR_END + margin, DHT11_SPLIT, SCREEN_WIDTH - CALENDAR_END, GxEPD_BLACK);
        display.drawFastHLine(CALENDAR_END + margin, ACTURE_WEATHER_SPLIT, SCREEN_WIDTH - CALENDAR_END, GxEPD_BLACK);
        display.drawFastHLine(CALENDAR_END + margin, FUTURE_WEATHER_SPLIT, SCREEN_WIDTH - CALENDAR_END, GxEPD_BLACK);
        displayMonthCalendar(date_today);
        displayDate(date_today);

        displayWeather(weatherNow, forecast);
        displayAdvice(lunarDate);

        // 展示温湿度
        u16_t split_x = SCREEN_WIDTH - (SCREEN_WIDTH - CALENDAR_END) / 2;
        margin = 0.191 * (ACTURE_WEATHER_SPLIT - DHT11_SPLIT);
        display.drawFastVLine(split_x, DHT11_SPLIT + margin, ACTURE_WEATHER_SPLIT - DHT11_SPLIT - 2 * margin,
                              GxEPD_BLACK);
        u8g2Fonts.setFont(TEXT19_MN);
        String h_str = String(h);
        u16_t pos_x = getCenterText_X(h_str.c_str(), CALENDAR_END, split_x);
        u16_t pos_y = getCenter_Y(DHT11_SPLIT, ACTURE_WEATHER_SPLIT, getFontHeight());
        text(h_str.c_str(), pos_x, pos_y);
        u8_t text_w = u8g2Fonts.getUTF8Width(h_str.c_str());
        u8g2Fonts.setFont(TEXT14_GB);
        pos_x += text_w + 2;
        text("%", pos_x, pos_y);

        String t_str = String(t);
        u8g2Fonts.setFont(TEXT19_MN);
        pos_x = getCenterText_X(t_str.c_str(), split_x, SCREEN_WIDTH);
        text(t_str.c_str(), pos_x, pos_y);
        text_w = u8g2Fonts.getUTF8Width(t_str.c_str());
        u8g2Fonts.setFont(TEXT16_GB);
        pos_x += text_w;
        text("°", pos_x, pos_y);
    } while (display.nextPage());
    ticker.detach();
    digitalWrite(PIN_LED, HIGH);
    display.hibernate();
}

#include "btn.h"

void setup() {
    InitSystem(115200);
    BtnInit();
    BTN_CONFIRM.attachClick(displayMainPage);
    displayInit();
    delay(20);
    initWifiManager();
    delay(20);
    debug_println("OK");
    // display.firstPage();
    // u8g2Fonts.setFont(TEXT16_GB);
    // do {
    //     String str = "连接网络成功，正在从服务器获取数据。。。";
    //     text(str.c_str(), getCenter_X(0, SCREEN_WIDTH, u8g2Fonts.getUTF8Width(str.c_str())),
    //          getCenter_Y(0, SCREEN_HEIGHT, getFontHeight()));
    // } while(display.nextPage());
    ticker_s.attach(1, tick_s);
}

void loop() {
    BtnTick();
    delay(10);
    if (second % (60 * 60 * 1) == 0) {
        getCurrentDate(date_today);  // date
        if (older_day != date_today.tm_mday) {
            older_day = date_today.tm_mday;
            u8_t count = 0;
            while (getLunarDate(&date_today, &lunarDate) == UNSUCCESS) {
                if (count++ >= 5) {
                    ESP.restart();
                }
                debug_println("Failed to obtain getLunarDate information");
                delay(100);
            }
            debug_println("=====getLunarDate=========");
            debug_println(lunarDate.suit);
            debug_println(lunarDate.avoid);
            debug_println("=======================");
        }
        displayMainPage();
    }
}

void InitSystem(uint32_t baud) {
// 串口的配置
#ifdef DEBUG
    Serial.begin(baud);
    while (!Serial)
        continue;
    debug_println("Serial OK");
#endif
    // 引脚的配置
    pinMode(PIN_LED, OUTPUT);
    pinMode(PIN_REST_WIFI, INPUT_PULLUP);

    // start ticker with 0.5 because we start in AP mode and try to connect
    ticker.attach(0.5, toggleLed);
}

ReturnStatus_t getTHData(u8_t &h, u8_t &t) {
    DHT dht(PIN_DHT11, DHT11);

    h = dht.readHumidity();
    // Read temperature as Celsius (the default)
    t = dht.readTemperature();

    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t)) {
        return UNSUCCESS;
    }
    t = dht.computeHeatIndex(t, h, false);

    return SUCCESS;

    // Serial.print(F("Humidity: "));
    // Serial.print(h);
    // // 体感温度
    // Serial.print(hic);
    // Serial.print(F("°C "));
}

void displayTHData() {

}
