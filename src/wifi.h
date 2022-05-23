//
// Created by ico2k2 on 22/5/2022.
//

#ifndef POLO_WIFI_H
#define POLO_WIFI_H

#include <ESP8266WiFi.h>
#include <private.h>

#define WIFI_SSID_MAX       32
#define WIFI_PASSWORD_MAX   64

#if USE_OTA
#include <ArduinoOTA.h>
#endif

#endif //POLO_WIFI_H
