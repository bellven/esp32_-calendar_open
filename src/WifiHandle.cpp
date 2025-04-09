#include "WifiHandle.h"
#include "Config.h"
#include "Display.h"
#include "Ticker.h"
#include "Utils.h"
#include "WiFi.h"
#include "WiFiManager.h"
#include "bitmap.h"
#include "Preferences.h"

WiFiManager wifiManager;
WiFiManagerParameter para_seniverse_key("seniverse_key", "心知天气Token", "", 32); //     心知天气key
// WiFiManagerParameter para_seniverse_location("seniverse_loc", "位置ID", "", 9, "pattern='\\d{9}'"); //     城市code

bool shouldSaveConfig = false;
void displayMainPage();
extern Ticker ticker;
extern u32_t second;

/**
 * 功能描述：初始化 wifimanager
 */
void initWifiManager() {
    wifiManager.setDebugOutput(false);
    wifiManager.setTitle("E-ink-calendar");
    wifiManager.addParameter(&para_seniverse_key);
    // 设置进入AP模式的回调
    wifiManager.setAPCallback(configModeCallback);
    // 设置点击保存的回调
    wifiManager.setSaveConfigCallback(saveConfigCallback);

    if (!wifiManager.autoConnect("E-ink-calendar")) {
        debug_println("failed to connect and hit timeout");
        // reset and try again, or maybe put it to deep sleep

        delay(1000);
    }

    debug_println("Wifi connected!!");
    ticker.attach(0.2, toggleLed);
    debug_println("local ip");
    debug_println(WiFi.localIP());
    debug_println(WiFi.SSID());
}

/**
 * 功能描述：初始化 配置网络回调
 */
void configModeCallback(WiFiManager* myWiFiManager) {
    String t = String() + "进入配网模式:" + "WiFi名字是:" + myWiFiManager->getConfigPortalSSID();
    debug_println(t);
    debug_println(WiFi.softAPIP());
    debug_println(myWiFiManager->getConfigPortalSSID());
    /*如果联网失败就显示失败提醒*/
    display.fillScreen(GxEPD_WHITE);
    display.drawInvertedBitmap(0, 0, jitang, 400, 300, GxEPD_BLACK);  // 画图
    display.nextPage();

    // ticker.attach(0.2, toggleLed);
}

/**
 * 功能描述：设置配网保存的回调
 */
void saveConfigCallback() {
    debug_println("Should save config");
    Preferences pref;
    pref.begin(PREF_NAMESPACE);
    pref.putString(XINZHI_API_KEY, para_seniverse_key.getValue());
    pref.end();
    shouldSaveConfig = true;
    // displayMainPage();
    ESP.restart(); // 重启
}

void handleRestWifi() {
    wifiManager.resetSettings();
    debug_println("WiFi Settings Cleared");
    delay(1000);
    initWifiManager();
}