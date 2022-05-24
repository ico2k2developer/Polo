#define USE_SERIAL      OFF
#define USE_DISPLAY     ON
#define USE_WIFI        OFF
#define USE_OTA         OFF

#include <main.h>

timerp timers[3];
uint_fast64_t err,count,mcs,interval,last_interval,last_err;
uint8_t coil;

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
    setupLed();

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
        display.display();
#endif
    }
#endif

#if USE_SERIAL
    Serial.printf("Using sample rate %llu Hz\n",SAMPLE_RATE);
#endif
#if USE_DISPLAY
    display.setCursor(0,0);
    display.printf("Scan rate %llu "
#if SAMPLE_RATE >= 1000ULL
    "kHz",SAMPLE_RATE / 1000ULL);
#else
    "Hz",SAMPLE_RATE);
#endif
#endif
    timers[0] = timer_new(TIMER_ID_MAIN,1000ULL * 1000ULL / SAMPLE_RATE);
    timers[1] = timer_new(TIMER_ID_OUTPUT,1000ULL * 1000ULL);
    timers[2] = timer_new(TIMER_ID_ALERT,100UL * 1000ULL);
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
    last_interval = last_err = err = count = 0;
    coil = getCoil();
    mcs = micros();
}


void loop()
{
    timer_handle_all(timers,sizeof(timers) / sizeof(timers[0]));
}

uint_fast64_t timer_ms(timerp t)
{
    return micros64();
}

trigger_result timer_triggered(const timerp t, const uint_fast64_t triggered)
{
    switch(timer_id(t))
    {
        case TIMER_ID_MAIN:
        {
            uint8_t read = getCoil();
            if(read != coil)
            {
                coil = read;
                if(read == PIN_COIL_OFF)
                {
                    interval = triggered - mcs;
                    if(last_interval == 0)
                        last_interval = interval;
                    else if(interval > (last_interval * 6 / 5) || interval < (last_interval * 4 / 5))
                    {
                        err++;
                        last_interval = interval;
                    }
                    count++;
                    mcs = timer_ms(t);
                }
            }
            return REARM;
        }
        case TIMER_ID_OUTPUT:
        {
            if(last_err != err)
            {
                setLed(ON);
                timer_reset(timers[2]);
                timer_rearm(timers[2]);
                last_err = err;
            }
            memset(display.getBuffer() + (1 * SCREEN_WIDTH),0,SCREEN_WIDTH * 3 * sizeof(uint8_t));
            display.setCursor(0,8);
            display.printf("Itervl: %llu mcs\nCount: %llu\nErrors: %llu",interval,count,err);
            display.display();
            return REARM;
        }
        case TIMER_ID_ALERT:
        {
            setLed(OFF);
            return NO_REARM;
        }
        default:
#if USE_SERIAL
            Serial.print("Unknown timer triggered\n");
#endif
            return NO_REARM;
    }
}