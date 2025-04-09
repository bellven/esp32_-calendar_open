#include "utils.h"
#include "HTTPClient.h"

/**
 * @brief GET request helper function
 *
 * @param url
 * @return String
 */
String httpGetRqst(String url) {
    HTTPClient http;
    String payload = "HTTP GET";

    http.begin(url);

    int http_code = http.GET();
    if (http_code > 0) {
        if (http_code == HTTP_CODE_OK) {
            payload = http.getString();
        }
    }

    http.end();

    return payload;
}
String splitString(const String s, u8_t count) {
    int index = 0;     // 记录每次查找到的索引位置
    String subString;  // 存储拆分出来的子字符串
    String result = "";

    for (u8_t i = 0; i < count; i++) {
        int found = s.indexOf('.', index);  // 在 s 中从 index 位置开始查找 '.' 的位置
        if (found != -1) {
            subString = s.substring(index, found);  // 获取从 index 到 found 的子字符串
            index = found + 1;                      // 更新 index 为下一个字符的位置
        } else {
            // 如果找不到 '.' 了，说明已经到了末尾，最后一个子字符串从 index 到末尾
            subString = s.substring(index);
            result += subString;
            break;  // 跳出循环
        }

        
        result += subString + " ";
    }
    return result;
}

/**
 * 功能描述：设置LED灯闪烁，提示用户进入配置模式
 */
void toggleLed() {
    // toggle state
    int state = digitalRead(PIN_LED);  // get the current state of GPIO1 pin
    // debug_println(state);
    digitalWrite(PIN_LED, !state);     // set pin to the opposite state
}