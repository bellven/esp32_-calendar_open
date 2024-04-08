#include "btn.h"
#include "WifiHandle.h"

// 按键绑定
OneButton BTN_CONFIRM(PIN_BTN, true);

// 按键回调函数 确认
void CLICK_CONFIRM() {
    debug_println("Button CON click.");
}


void BtnInit() {
    BTN_CONFIRM.attachLongPressStart(handleRestWifi);
}

void BtnTick() {
    BTN_CONFIRM.tick();
}