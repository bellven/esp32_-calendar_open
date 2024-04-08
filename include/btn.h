#ifndef KEY_H
#define KEY_H

#include "OneButton.h"
#include "Config.h"

extern OneButton BTN_CONFIRM;

void BtnInit();
void BtnTick();
void CLICK_CONFIRM();

#endif