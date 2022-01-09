#include <stdbool.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include <pin.h>
#include <timer0.h>
#include <synth.h>

/* Configuration ************************************************************ */

#define SPEAKER_PIN PIN_6

/* Main ********************************************************************* */

void loop(void);

int main(void) {
    pin_set_output(SPEAKER_PIN);

    timer0_init(
        TIMER0_WGM_PWM_FF,
        TIMER0_CS_NO_SCALING,
        TIMER0_COM_CLEAR,
        TIMER0_COM_DISABLED,
        TIMER0_INT_OVERFLOW
    );

    sei();

    synth_set_wavetable(SYNTH_OSCILLATOR_A, SYNTH_WAVETABLE_SAW);
    synth_set_frequency(SYNTH_OSCILLATOR_A, 262);
    synth_set_volume(SYNTH_OSCILLATOR_A, 127);

    synth_set_wavetable(SYNTH_OSCILLATOR_B, SYNTH_WAVETABLE_SAW);
    synth_set_frequency(SYNTH_OSCILLATOR_B, 330);
    synth_set_volume(SYNTH_OSCILLATOR_B, 127);

    while(1) loop();

    return 0;
}

/* Interrupts *************************************************************** */

ISR(TIMER0_OVF_vect) {
    timer0_set_compare_register_a(synth_next_sample());
}

/* Main event loop ********************************************************** */

void loop(void) {}
