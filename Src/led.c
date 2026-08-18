#include "stm32c031xx.h"
#include "led.h"

void led_init(void)
{
    RCC->IOPENR |= (1U << 0);

    GPIOA->MODER &= ~(3U << (5 * 2));
    GPIOA->MODER |= (1U << (5 * 2));
}

void led_toggle(void)
{
    GPIOA->ODR ^= (1U << 5);
}