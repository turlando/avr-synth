#include <avr/io.h>
#include <avr/interrupt.h>

#include <port.h>
#include <timer0.h>
#include <synth.h>

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

    synth_set_wavetable(SYNTH_WAVETABLE_SIN);
    synth_set_frequency(440);

    while(1);

    return 0;
}

ISR(TIMER0_OVF_vect) {
    timer0_set_compare_register_a(synth_next_sample());
}
