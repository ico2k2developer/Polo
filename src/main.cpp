#define USE_SERIAL      OFF
#define USE_DISPLAY     ON
#define USE_WIFI        ON
#define USE_OTA         OFF

#include <main.h>

uint_fast32_t mcs_coil,last,interval,limit,mcs_pickup,err_limit,mcs_loop,mcs_loop_max;
uint8_t read_pickup,read_coil,coil,pickup,err;

void setup()
{
    WiFi.mode(WIFI_OFF);
    WiFi.forceSleepBegin();
    setupCoil();
    setupLed();
    Serial.begin(115200);

#if USE_DISPLAY
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.setTextColor(SSD1306_WHITE);
    display.cp437(true);
    rtlprint(VERSION);

    display.display();
    display.clearDisplay();
    delay(1000);
    display.display();
#endif
    pickup = getPickup();
    //coil = getCoil();
    last = 0;
    limit = 0;
    interval = 0;
    err = 0;
    mcs_loop_max = 0;

    Serial.println();

    delay(1000);
    mcs_loop = micros();
}

void loop()
{
    if((micros() - mcs_loop) > mcs_loop_max)
    {
        mcs_loop_max = micros() - mcs_loop;
    }
    if(mcs_loop_max > 200U)
    {
        Serial.printf("Max loop time %u uS\n",mcs_loop_max);
        mcs_loop_max = 0;
    }
    mcs_loop = micros();


    read_pickup = getPickup();
    //read_coil = getCoil();
    if(pickup && !read_pickup)
    {
        mcs_pickup = mcs_loop;
        if(last)
            interval = mcs_pickup - last;
        last = mcs_pickup;
        if(interval > limit && limit != 0)
        {
            err = 1;
            //Serial.printf("Interval %u > %u\n",interval,limit);

#if USE_DISPLAY
            err_limit = limit;
#endif
        }
        limit = interval ? INTERVAL_LIMIT_MAX(interval) : 0;
    }
    /*if(coil && !read_coil)
    {
        mcs_coil = micros() - mcs_pickup;
    }*/
    pickup = read_pickup;
    //coil = read_coil;
    if(err)
    {
        error();
        last = 0;
        limit = 0;
        interval = 0;
        mcs_loop = micros();
    }
}

void error()
{
    setLed(!getLed());
#if USE_DISPLAY
    display.setCursor(0,0);
    display.printf("Last interval:\n%u micros\n"
                   "Interval limit:\n%u micros",
                   interval,err_limit);
    display.display();
    clearRows(0,4);
#endif
    err = 0;
}