#include "weather.h"
#include "bitmap.h"
#include "Seniverse.h"

ReturnStatus_t
getWeather(WeatherNow &weatherNow, Forecast &forecast) {
    weatherNow.config(XINZHI_API_KEY, "ip", "c");
    if (!weatherNow.update()) {
        return UNSUCCESS;
    }
    forecast.config(XINZHI_API_KEY, "ip", "c");
    if (!forecast.update()) {
        return UNSUCCESS;
    }

    return SUCCESS;
}

const uint8_t *MapIcon(const String weather_icon) {
    if (weather_icon == "多云" || weather_icon == "晴间多云" || weather_icon == "大部多云") {
        return Bitmap_101_fill;
    } else if (weather_icon == "晴") {
        return Bitmap_100_fill;
    } else if (weather_icon == "阴") {
        return Bitmap_104_fill;
    } else if (weather_icon == "阵雨") {
        return Bitmap_300_fill;
    } else if (weather_icon == "雷阵雨") {
        return Bitmap_302_fill;
    } else if (weather_icon == "雷阵雨伴有冰雹") {
        return Bitmap_304_fill;
    } else if (weather_icon == "小雨") {
        return Bitmap_305_fill;

    } else if (weather_icon == "中雨") {
        return Bitmap_306_fill;

    } else if (weather_icon == "大雨") {
        return Bitmap_307_fill;

    } else if (weather_icon == "暴雨" || weather_icon == "大暴雨" || weather_icon == "特大暴雨") {
        return Bitmap_310_fill;

    } else if (weather_icon == "冻雨") {
        return Bitmap_313_fill;

    } else if (weather_icon == "雨夹雪") {
        return Bitmap_404_fill;

    } else if (weather_icon == "阵雪") {
        return Bitmap_407_fill;

    } else if (weather_icon == "小雪") {
        return Bitmap_400_fill;

    } else if (weather_icon == "中雪") {
        return Bitmap_401_fill;

    } else if (weather_icon == "大雪") {
        return Bitmap_402_fill;

    } else if (weather_icon == "暴雪") {
        return Bitmap_403_fill;

    } else if (weather_icon == "浮尘") {
        return Bitmap_504_fill;

    } else if (weather_icon == "扬沙" || weather_icon == "沙尘暴" || weather_icon == "强沙尘暴") {
        return Bitmap_503_fill;

    } else if (weather_icon == "雾") {
        return Bitmap_501_fill;

    } else if (weather_icon == "霾") {
        return Bitmap_502_fill;

    } else if (weather_icon == "未知") {
        return Bitmap_999_fill;
    }
    return Bitmap_999_fill;
}

const uint8_t *MapIcon_16(const String weather_icon) {
    if (weather_icon == "多云" || weather_icon == "晴间多云" || weather_icon == "大部多云") {
        return Bitmap_101_fill_16;
    } else if (weather_icon == "晴") {
        return Bitmap_100_fill_16;
    } else if (weather_icon == "阴") {
        return Bitmap_104_fill_16;
    } else if (weather_icon == "阵雨") {
        return Bitmap_300_fill_16;
    } else if (weather_icon == "雷阵雨") {
        return Bitmap_302_fill_16;
    } else if (weather_icon == "雷阵雨伴有冰雹") {
        return Bitmap_304_fill_16;
    } else if (weather_icon == "小雨") {
        return Bitmap_305_fill_16;

    } else if (weather_icon == "中雨") {
        return Bitmap_306_fill_16;

    } else if (weather_icon == "大雨") {
        return Bitmap_307_fill_16;

    } else if (weather_icon == "暴雨" || weather_icon == "大暴雨" || weather_icon == "特大暴雨") {
        return Bitmap_310_fill_16;

    } else if (weather_icon == "冻雨") {
        return Bitmap_313_fill_16;

    } else if (weather_icon == "雨夹雪") {
        return Bitmap_404_fill_16;

    } else if (weather_icon == "阵雪") {
        return Bitmap_407_fill_16;

    } else if (weather_icon == "小雪") {
        return Bitmap_400_fill_16;

    } else if (weather_icon == "中雪") {
        return Bitmap_401_fill_16;

    } else if (weather_icon == "大雪") {
        return Bitmap_402_fill_16;

    } else if (weather_icon == "暴雪") {
        return Bitmap_403_fill_16;

    } else if (weather_icon == "浮尘") {
        return Bitmap_504_fill_16;

    } else if (weather_icon == "扬沙" || weather_icon == "沙尘暴" || weather_icon == "强沙尘暴") {
        return Bitmap_503_fill_16;

    } else if (weather_icon == "雾") {
        return Bitmap_501_fill_16;

    } else if (weather_icon == "霾") {
        return Bitmap_502_fill_16;

    } else if (weather_icon == "未知") {
        return Bitmap_999_fill_16;
    }
    return Bitmap_999_fill_16;
}