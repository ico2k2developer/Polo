//
// Created by ico2k2 on 22/5/2022.
//

#ifndef POLO_PIN_H
#define POLO_PIN_H

#define PIN_PICKUP      D5
#define PIN_COIL        D6

#define PIN_PICKUP_ON   ON
#define PIN_PICKUP_OFF  OFF
#define PIN_COIL_ON     ON
#define PIN_COIL_OFF    OFF

#define setupPickup() pinMode(PIN_PICKUP,INPUT)
#define setupCoil() pinMode(PIN_COIL,INPUT)

#define setPickup(on) digitalWrite(PIN_PICKUP,on ? PIN_PICKUP_ON : PIN_PICKUP_OFF)
#define setCoil(on) digitalWrite(PIN_COIL,on ? PIN_COIL_ON : PIN_COIL_OFF)

#define getPickup() digitalRead(PIN_PICKUP) ? PIN_PICKUP_ON : PIN_PICKUP_OFF
#define getCoil() digitalRead(PIN_COIL) ? PIN_COIL_ON : PIN_COIL_OFF

#endif //POLO_PIN_H