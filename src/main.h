//
// Created by ico2k2 on 22/5/2022.
//

#ifndef POLO_MAIN_H
#define POLO_MAIN_H

#define ON      1
#define OFF     0

#ifndef ESP8266
#error "Source files targetting ESP8266 in a non ESP8266 project."
#endif

#include <Arduino.h>
#include <board.h>
#include <timer.h>

#if USE_WIFI
#include <wifi.h>
#endif

#if USE_DISPLAY
#include <display.h>
#endif

#define INTERVAL_LIMIT_MAX(i)  (((i) * 9 / 5))

void error();

#endif //POLO_MAIN_H