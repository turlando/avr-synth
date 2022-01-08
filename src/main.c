#include <avr/io.h>
#include <avr/interrupt.h>

#include <port.h>
#include <timer0.h>
#include <wave/sin_int8_256.h>

#define FREQUENCY 440U
#define PWM_FREQUENCY (F_CPU) / 256U
#define ACCUMULATOR_STEP (FREQUENCY) * 65536UL / (PWM_FREQUENCY)

ISR(TIMER0_OVF_vect) {
    static uint16_t accumulator = 0;

    accumulator += ACCUMULATOR_STEP;
    timer0_set_compare_register_a(128 + SIN_INT8_256[accumulator >> 8]);
}

int main(void) {
    port_d_set_output(PORT_D_PIN_6); /* Speaker. Arduino port 6. */

    timer0_init(
        TIMER0_WGM_PWM_FF,
        TIMER0_CS_NO_SCALING,
        TIMER0_COM_CLEAR,
        TIMER0_COM_DISABLED,
        TIMER0_INT_OVERFLOW
    );

    sei();

    while(1);

    return 0;
}
