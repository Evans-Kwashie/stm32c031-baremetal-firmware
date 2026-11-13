#include "uart.h"
#include "stm32c031xx.h"
#include <stdint.h>

void uart_init()
{
    RCC->IOPENR |= (1U << 0);
    RCC->APBENR2 |= RCC_APBENR2_USART1EN;

    GPIOA->MODER &= ~(3U << (9 * 2));
    GPIOA->MODER |= (2U << (9 * 2));

    GPIOA->AFR[1] &= ~(0xFU << ((9 - 8) * 4));
    GPIOA->AFR[1] |= (0x1U << ((9 - 8) * 4));

    GPIOA->MODER &= ~(3U << (10 * 2));
    GPIOA->MODER |=  (2U << (10 * 2));

    GPIOA->AFR[1] &= ~(0xFU << ((10 - 8) * 4));
    GPIOA->AFR[1] |=  (0x1U << ((10 - 8) * 4));

    USART1->BRR = 5000;

    USART1->CR1 |= USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;
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

void uart_write_uint(uint32_t number)
{
    char digits[10];
    uint8_t i = 0;

    if (number == 0)
    {
        uart_write_char('0');
        return;
    }

    while (number != 0)
    {
        digits[i] = number % 10;
        i++;
        number /= 10;
    }

    while (i != 0)
    {
        i--;
        uart_write_char('0' + digits[i]);
    }
}

void uart_write_hex(uint32_t number)
{
    const char hex[] = "0123456789ABCDEF";
    uint8_t digits[8];
    uint8_t i = 0;

    uart_write_char('0');
    uart_write_char('x');

    if (number == 0)
    {
        uart_write_char('0');
    }

    while (number != 0)
    {
        digits[i] = number % 16;
        i++;
        number /= 16;
    }

    while (i != 0)
    {
        i--;
        uart_write_char(hex[digits[i]]);
    }

}

char uart_read_char(void)
{
    while (!(USART1->ISR & USART_ISR_RXNE_RXFNE))
    {
    }

    return USART1->RDR;
}

uint8_t uart_char_available(void)
{
    if (USART1->ISR & USART_ISR_RXNE_RXFNE)
    {
        return 1;
    }

    return 0;
}
