#include <USART.h>
#include <timer0.h>

#define USART_BAUD 9600

int main(void) {
    USART_init(
        USART_BAUD,
        USART_CS_8,
        USART_P_DISABLED,
        USART_SB_1,
        USART_D_TRANSMIT | USART_D_RECEIVE
    );

    while (1);

    return 0;
}
