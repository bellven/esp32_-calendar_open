#pragma once
#include "WiFiManager.h"

extern WiFiManager wifiManager;
extern bool shouldSaveConfig;

void initWifiManager();
void configModeCallback(WiFiManager* myWiFiManager);
void saveConfigCallback();
void handleRestWifi();