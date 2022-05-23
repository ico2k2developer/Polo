//
// Created by ico2k2 on 22/5/2022.
//

#include <display.h>

Adafruit_SSD1306 display = Adafruit_SSD1306(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

unsigned char rtlprintf(const char* format, ...)
{
    va_list arg;
    va_start(arg, format);
    char temp[64];
    size_t len = vsnprintf(temp, sizeof(temp), format, arg);
    va_end(arg);
    if (len > sizeof(temp) - 1)
    {
        char* buffer = (char*)malloc(len + 1);
        if(!buffer)
            return 1;
        va_start(arg, format);
        vsnprintf(buffer,len + 1,format,arg);
        va_end(arg);
        rtlprint(buffer);
        free(buffer);
    }
    else
        rtlprint(temp);
    return 0;
}

void rtlprint(const char* string)
{
    uint16_t w = 0;
    int16_t tmp = 0;
    display.getTextBounds(string, 0, 0, &tmp, &tmp, &w, (uint16_t*)&tmp);
    display.setCursor(SCREEN_WIDTH - w,display.getCursorY());
    display.print(string);
}

void rtlprintln(const char* string)
{
    rtlprint(string);
    display.print('\n');
}