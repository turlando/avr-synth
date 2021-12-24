#include <USART.h>

#define USART_BAUD 9600

int main(void) {
    USART_init(USART_BAUD, BIT_8, DISABLED, BIT_1, TRANSMIT | RECEIVE);
    USART_send_string("Hello world!\r\n");

    while (1);

    return 0;
}
