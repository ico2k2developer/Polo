//
// Created by ico2k2 on 22/5/2022.
//

#include <timer.h>

void timer_handle_all(timerp* timers, size_t count)
{
    size_t i;
    for(i = 0; i < count; i++)
        timer_handle(timers[i]);
}

handler_result timer_handle(timerp t)
{
    handler_result result = NOT_TRIGGERED;
    if(timer_armed(t))
    {
        uint_fast64_t ms;
        if(((ms = timer_ms(t)) - t->start) >= t->duration)
        {
            result = TRIGGERED;
            if(timer_triggered(t, ms) == NO_REARM)
                timer_off(t);
            else
                t->start = ms;
        }
    }
    return result;
}

void timer_reset(timerp t)
{
    t->start = timer_ms(t);
}

uint8_t timer_armed(const timerp t)
{
    return t->id & (1 << (sizeof(t->id) * 8 - 1)) ? 1 : 0;
}

void timer_rearm(timerp t)
{
    t->id |= (1 << (sizeof(t->id) * 8 - 1));
}

void timer_off(timerp t)
{
    t->id &= ~(1 << (sizeof(t->id) * 8 - 1));
}

uint8_t timer_id(timerp t)
{
    return t->id & ~(1 << (sizeof(t->id) * 8 - 1));
}

timerp timer_new(const uint8_t id,const uint_fast64_t duration)
{
    auto t = (timerp)malloc(sizeof(timer));
    if(t)
    {
        t->id = id;
        t->start = 0;
        t->duration = duration;
        timer_off(t);
    }
    else
        t = nullptr;
    return t;
}

void timer_free(const timerp t)
{
    free(t);
}