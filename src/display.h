//
// Created by ico2k2 on 22/5/2022.
//

#ifndef POLO_DISPLAY_H
#define POLO_DISPLAY_H

#include <cstdio>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH            128
#define SCREEN_HEIGHT           64

extern Adafruit_SSD1306 display;

unsigned char rtlprintf(const char* format, ...);
void rtlprint(const char* string);
void rtlprintln(const char* string);

#endif //POLO_DISPLAY_H