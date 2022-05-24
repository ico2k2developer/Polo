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

#include <board.h>
#include <timer.h>

#if USE_WIFI
#include <wifi.h>
#endif

#if USE_DISPLAY
#include <display.h>
#endif

#define SAMPLE_RATE 600ULL

#define TIMER_ID_MAIN   0x10
#define TIMER_ID_OUTPUT 0x20
#define TIMER_ID_ALERT  0x30

#endif //POLO_MAIN_H