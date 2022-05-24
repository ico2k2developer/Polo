//
// Created by ico2k2 on 22/5/2022.
//

#ifndef POLO_PIN_H
#define POLO_PIN_H

#define PIN_PICKUP      D5
#define PIN_COIL        D6
#define PIN_LED         D7

#define PIN_PICKUP_ON       HIGH
#define PIN_PICKUP_OFF      LOW
#define PIN_COIL_ON         HIGH
#define PIN_COIL_OFF        LOW
#define PIN_LED_BUILTIN_ON  LOW
#define PIN_LED_BUILTIN_OFF HIGH
#define PIN_LED_ON          HIGH
#define PIN_LED_OFF         LOW

#define setupPickup() pinMode(PIN_PICKUP,INPUT)
#define setupCoil() pinMode(PIN_COIL,INPUT)
#define setupLedBuiltin() pinMode(LED_BUILTIN,OUTPUT)
#define setupLed() pinMode(PIN_LED,OUTPUT)

#define setPickup(on) digitalWrite(PIN_PICKUP,on ? PIN_PICKUP_ON : PIN_PICKUP_OFF)
#define setCoil(on) digitalWrite(PIN_COIL,on ? PIN_COIL_ON : PIN_COIL_OFF)
#define setLedBuiltin(on) digitalWrite(LED_BUILTIN,on ? PIN_LED_BUILTIN_ON : PIN_LED_BUILTIN_OFF)
#define setLed(on) digitalWrite(PIN_LED,on ? PIN_LED_ON : PIN_LED_OFF)

#define getPickup() digitalRead(PIN_PICKUP) ? PIN_PICKUP_ON : PIN_PICKUP_OFF
#define getCoil() digitalRead(PIN_COIL) ? PIN_COIL_ON : PIN_COIL_OFF
#define getLed() digitalRead(PIN_LED) ? PIN_LED_ON : PIN_LED_OFF

#endif //POLO_PIN_H