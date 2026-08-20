#include "uart.h"
#include "stm32c031xx.h"

void uart_init()
{
    RCC->IOPENR |= (1U << 0);
    RCC->APBENR2 |= RCC_APBENR2_USART1EN;

    GPIOA->MODER &= ~(3U << (9 * 2));
    GPIOA->MODER |= (2U << (9 * 2));

    GPIOA->AFR[1] &= ~(0xFU << ((9 - 8) * 4));
    GPIOA->AFR[1] |= (0x1U << ((9 - 8) * 4));

    USART1->BRR = 5000;

    USART1->CR1 |= USART_CR1_TE | USART_CR1_UE;
}

void uart_write_char(char c)
{
    while(!(USART1->ISR & USART_ISR_TXE_TXFNF))
    {
    }
     USART1->TDR = c;
}

void uart_write_string(const char *str)
{
    while(*str != '\0')
    {
        uart_write_char(*str);
        str++;
    }
}