#include "timer.h"
#include "stm32c031xx.h"

static volatile uint8_t timer_event = 0;

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

