#ifndef USART_H
#define USART_H

#include <stdint.h>
#include <avr/io.h>

enum USART_character_size {
    BIT_5 = 0 << UCSZ01 | 0 << UCSZ00,
    BIT_6 = 0 << UCSZ01 | 1 << UCSZ00,
    BIT_7 = 1 << UCSZ01 | 0 << UCSZ00,
    BIT_8 = 1 << UCSZ01 | 1 << UCSZ00,
};

enum USART_parity {
    DISABLED = 0 << UPM01 | 0 << UPM00,
    EVEN     = 1 << UPM01 | 0 << UPM00,
    ODD      = 1 << UPM01 | 1 << UPM00,
};

enum USART_stop_bits {
    BIT_1 = 0 << USBS0,
    BIT_2 = 1 << USBS0,
};

enum USART_direction {
    TRANSMIT = 1 << TXEN0,
    RECEIVE  = 1 << RXEN0,
};

void USART_init(
    uint32_t baud,
    enum USART_character_size character_size,
    enum USART_parity parity,
    enum USART_stop_bits stop_bits,
    enum USART_direction direction
);

void USART_send_byte(uint8_t data);
uint8_t USART_wait_byte();

void USART_send_string(const char *string);

#endif /* USART_ H */
