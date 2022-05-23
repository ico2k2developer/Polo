//
// Created by ico2k2 on 22/5/2022.
//

#ifndef POLO_BOARD_H
#define POLO_BOARD_H

#include <pin.h>
#include <version.h>

#define BOARD_TYPE              "NodeMCU 1.0 (ESP-12E)"
#define BOARD_REG_EMULATION     "None"

#define _restart()              delay(500); ESP.restart();

#endif //POLO_BOARD_H