#define USE_SERIAL      OFF
#define USE_DISPLAY     ON
#define USE_WIFI        OFF
#define USE_OTA         OFF

#include <main.h>

timerp timers[2];
uint_fast64_t count;

void setup()
{
#if USE_SERIAL
    Serial.begin(115200);
    Serial.println(
            "\n"
            "Version: " VERSION "\n"
            __FILE__ "\n"
            __DATE__ " " __TIME__ "\n"
            BOARD_TYPE);
#endif

    setupPickup();
    setupCoil();

#if USE_WIFI
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
#endif

#if USE_DISPLAY
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    display.setTextColor(SSD1306_WHITE);
    display.cp437(true);
    rtlprint(VERSION);

    display.display();
    delay(2000);
#if USE_WIFI
    while(!WiFi.isConnected())
        delay(250);
#endif
    display.clearDisplay();
#endif

#if USE_WIFI && (USE_SERIAL || USE_DISPLAY)
    {
        IPAddress ip = WiFi.localIP();
#if USE_SERIAL
        Serial.printf("Connected to %s with IP address %hhu.%hhu.%hhu.%hhu\n",
                      WiFi.SSID().c_str(),ip[0],ip[1],ip[2],ip[3]);
#endif
#if USE_DISPLAY
        rtlprintf("%hhu.%hhu",ip[2],ip[3]);
        display.setCursor(0,0);
        display.display();
#endif
    }
#endif

#if USE_SERIAL
    Serial.printf("Using sample rate %llu Hz\n",SAMPLE_RATE);
#endif
#if USE_DISPLAY
    display.printf("S.R. rate %llu "
#if SAMPLE_RATE >= 1000ULL
    "kHz",SAMPLE_RATE / 1000ULL);
#else
    "Hz",SAMPLE_RATE);
#endif
#endif
    timers[0] = timer_new(TIMER_ID_MAIN,1000ULL * 1000ULL / SAMPLE_RATE);
    timers[1] = timer_new(TIMER_ID_OUTPUT,1000ULL);
    timer_rearm(timers[0]);
    timer_rearm(timers[1]);
    timer_reset(timers[0]);
    timer_reset(timers[1]);
#if USE_SERIAL
    Serial.printf("Main timer has id %x (%x) %llu, "
                  "output timer has id %x (%x) %llu\n",
                  timer_id(timers[0]),timers[0]->id,timers[0]->start,
                  timer_id(timers[1]),timers[1]->id,timers[1]->start);
    Serial.print("Setup ended, going into loop()\n");
#endif
    count = 0;
}


void loop()
{
    timer_handle_all(timers,sizeof(timers) / sizeof(timers[0]));
}

uint_fast64_t timer_ms(timerp t)
{
    switch (timer_id(t))
    {
        case TIMER_ID_MAIN:
        {
            return micros();
        }
        case TIMER_ID_OUTPUT:
        {
            return millis();
        }
        default:
            return 0;
    }
}

trigger_result timer_triggered(const timerp t, const uint_fast64_t triggered)
{
    switch(timer_id(t))
    {
        case TIMER_ID_MAIN:
        {
            count++;
            return REARM;
        }
        case TIMER_ID_OUTPUT:
        {
            memset(display.getBuffer() + 1 * SCREEN_WIDTH,0,SCREEN_WIDTH * 1 * sizeof(uint8_t));
            display.setCursor(0,8);
            display.printf("Count: %llu",count);
            display.display();
            count = 0;
            return REARM;
        }
        default:
#if USE_SERIAL
            Serial.print("Unknown timer triggered\n");
#endif
            return NO_REARM;
    }
}