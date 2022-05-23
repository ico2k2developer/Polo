//
// Created by ico2k2 on 22/5/2022.
//

#ifndef POLO_TIMER_H
#define POLO_TIMER_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>

typedef struct
{
    uint_fast64_t duration,start;
    uint8_t id;
} timer;

typedef timer* timerp;

typedef enum
{
    REARM,
    NO_REARM,
} trigger_result;

typedef enum
{
    TRIGGERED,
    NOT_TRIGGERED,
} handler_result;

extern uint_fast64_t timer_ms(timerp t);
extern trigger_result timer_triggered(timerp t, uint_fast64_t triggered);

handler_result timer_handle_all(timerp* timers, size_t count);
handler_result timer_handle(timerp timer);

void timer_reset(timerp t);
uint8_t timer_armed(timerp t);
void timer_rearm(timerp t);
void timer_off(timerp t);
uint8_t timer_id(timerp t);

timerp timer_new(uint8_t id,uint_fast64_t duration);
void timer_free(timerp t);

#endif //POLO_TIMER_H
