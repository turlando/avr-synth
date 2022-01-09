#include <stdbool.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <pin.h>
#include <adc.h>
#include <timer0.h>
#include <button.h>
#include <synth.h>

/* Configuration ************************************************************ */

#define BUTTON_B_PIN PIN_2
#define SPEAKER_PIN  PIN_6
#define KNOB_A_PIN   PIN_A2
#define KNOB_B_PIN   PIN_A4
#define BUTTON_A_PIN PIN_4

/* Main ********************************************************************* */

void loop(void);

int main(void) {
    pin_set_input(BUTTON_A_PIN);
    pin_set_pullup(BUTTON_A_PIN);

    pin_set_input(BUTTON_B_PIN);
    pin_set_pullup(BUTTON_B_PIN);

    pin_set_input(KNOB_A_PIN);
    pin_set_input(KNOB_B_PIN);

    pin_set_output(SPEAKER_PIN);

    timer0_init(
        TIMER0_WGM_PWM_FF,
        TIMER0_CS_NO_SCALING,
        TIMER0_COM_CLEAR,
        TIMER0_COM_DISABLED,
        TIMER0_INT_OVERFLOW
    );

    adc_init(
        ADC_VOLTAGE_REFERENCE_AREF,
        ADC_PRESCALER_DIV_128,
        ADC_RESULT_ADJUST_RIGHT
    );

    sei();

    synth_set_wavetable(SYNTH_OSCILLATOR_A, SYNTH_WAVETABLE_SIN);
    synth_set_frequency(SYNTH_OSCILLATOR_A, 0);
    synth_set_volume(SYNTH_OSCILLATOR_A, 127);

    synth_set_wavetable(SYNTH_OSCILLATOR_B, SYNTH_WAVETABLE_SAW);
    synth_set_frequency(SYNTH_OSCILLATOR_B, 0);
    synth_set_volume(SYNTH_OSCILLATOR_B, 127);

    while(1) loop();

    return 0;
}

/* Interrupts *************************************************************** */

ISR(TIMER0_OVF_vect) {
    timer0_set_compare_register_a(synth_next_sample());
}

/* Helper functions ********************************************************* */

void set_next_wavetable(const enum synth_oscillator oscillator) {
    const enum synth_wavetable current = synth_get_wavetable(oscillator);
    synth_set_wavetable(oscillator, (current + 1) % SYNTH_WAVETABLES_COUNT);
}

/* Main event loop ********************************************************** */

void loop(void) {
    const enum button_event button_a = button_get_event(BUTTON_A_PIN);
    const enum button_event button_b = button_get_event(BUTTON_B_PIN);

    const uint16_t knob_a = pin_analog_read(KNOB_A_PIN);
    const uint16_t knob_b = pin_analog_read(KNOB_B_PIN);

    synth_set_frequency(SYNTH_OSCILLATOR_A, knob_a);
    synth_set_frequency(SYNTH_OSCILLATOR_B, knob_b);

    if (button_a == BUTTON_PRESSED)
        set_next_wavetable(SYNTH_OSCILLATOR_A);

    if (button_b == BUTTON_PRESSED)
        set_next_wavetable(SYNTH_OSCILLATOR_B);
}
