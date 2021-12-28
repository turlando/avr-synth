#include <USART.h>

#include <stdint.h>
#include <avr/io.h>

void USART_init(
    const uint32_t baud,
    const enum USART_character_size character_size,
    const enum USART_parity parity,
    const enum USART_stop_bits stop_bits,
    const enum USART_direction direction
) {
    /* Prescale value for baud rate register. */
    const uint16_t baud_prescale = (F_CPU / 4 / baud - 1) / 2;
    UBRR0H = baud_prescale >> 8;
    UBRR0L = baud_prescale;

    /* Enable double speed operation. */
    UCSR0A |= 1 << U2X0;

    UCSR0C = character_size | stop_bits | parity;
    UCSR0B = direction;
}

void USART_send_byte(const uint8_t data) {
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = data;
}

uint8_t USART_wait_byte() {
    loop_until_bit_is_set(UCSR0A, RXC0);
    return UDR0;
}

void USART_send_string(const char *string) {
    while (*string != '\0') {
        USART_send_byte(*string);
        string++;
    }
}
