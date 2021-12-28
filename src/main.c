#include <util/delay.h>

#include <port.h>
#include <timer0.h>
#include <USART.h>

#define USART_BAUD 9600

int main(void) {
    USART_init(
        USART_BAUD,
        USART_CS_8,
        USART_P_DISABLED,
        USART_SB_1,
        USART_D_TRANSMIT | USART_D_RECEIVE
    );

    USART_send_string("Hello world!\r\n");

    port_d_set_output(PORT_D_PIN_5 | PORT_D_PIN_6);

    timer0_init(
        TIMER0_WGM_PWM_FF,
        TIMER0_CS_NO_SCALING,
        TIMER0_COM_CLEAR,
        TIMER0_COM_CLEAR
    );

    while (1) {
        uint8_t i = 0;
        do {
            timer0_set_compare_register_a(i);
            timer0_set_compare_register_b(255 - i);
            i++;
            _delay_ms(5);
        } while (i > 0);

        do {
            timer0_set_compare_register_a(i);
            timer0_set_compare_register_b(255 - i);
            i--;
            _delay_ms(5);
        } while (i > 0);
    }

    return 0;
}
