#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

void timer_init(void);
uint8_t timer_event_get(void);
uint8_t one_second_event_get(void);
uint32_t timer_status_before_get(void);
uint32_t timer_status_after_get(void);

#endif