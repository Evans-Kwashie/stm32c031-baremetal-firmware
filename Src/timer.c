#include "timer.h"
#include "stm32c031xx.h"
#include <stdint.h>

static volatile uint8_t timer_event = 0;
static volatile uint8_t one_second_event = 0;

static uint8_t timer_count = 0;

void timer_init(void)
{
    RCC->APBENR1 |= RCC_APBENR1_TIM3EN;

    TIM3->PSC = 4799;
    TIM3->ARR = 999;

    TIM3->SR &= ~TIM_SR_UIF;

    TIM3->DIER |= TIM_DIER_UIE;

    NVIC_EnableIRQ(TIM3_IRQn);

    TIM3->CR1 |= TIM_CR1_CEN;
}

void TIM3_IRQHandler(void)
{
    

    if (TIM3->SR & TIM_SR_UIF)
    {
        TIM3->SR &= ~TIM_SR_UIF;

        timer_event = 1;
        timer_count++;
    }

    if (timer_count >=10)
    {
        timer_count = 0;
        one_second_event = 1;
    }
}

uint8_t timer_event_get(void)
{

    if (timer_event)
    {
        timer_event = 0;
        return 1;
    }

    return 0;
}

uint8_t one_second_event_get(void)
{
    if (one_second_event)
    {   
        one_second_event = 0;
        return 1;
    }
    return 0;
}
