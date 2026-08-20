#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

void timer_init(void);
uint8_t timer_event_get(void);
uint8_t one_second_event_get(void);

#endif