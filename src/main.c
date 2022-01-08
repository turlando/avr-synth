#include <stdbool.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include <pin.h>
#include <timer0.h>
#include <synth.h>

/* Configuration ************************************************************ */

#define SPEAKER_PIN PIN_6

#define BUTTON_A_PIN PIN_4
#define BUTTON_B_PIN PIN_2

/* Main ********************************************************************* */

void loop(void);

int main(void) {
    pin_set_output(SPEAKER_PIN);

    pin_set_input(BUTTON_A_PIN);
    pin_set_pullup(BUTTON_A_PIN);

    timer0_init(
        TIMER0_WGM_PWM_FF,
        TIMER0_CS_NO_SCALING,
        TIMER0_COM_CLEAR,
        TIMER0_COM_DISABLED,
        TIMER0_INT_OVERFLOW
    );

    sei();

    synth_set_frequency(440);

    while(1) loop();

    return 0;
}

/* Interrupts *************************************************************** */

ISR(TIMER0_OVF_vect) {
    timer0_set_compare_register_a(synth_next_sample());
}

/* Buttons ****************************************************************** */

#define BUTTONS_COUNT 2

#define BUTTON_IS_PRESSED(pin) (pin_get_state(pin) == PIN_LOW)

enum button {
    BUTTON_A,
    BUTTON_B,
};

static const enum pin BUTTON_PIN[BUTTONS_COUNT] = {
    BUTTON_A_PIN,
    BUTTON_B_PIN,
};

enum button_event {
    BUTTON_PRESSED,
    BUTTON_IDLE,
    BUTTON_RELEASED,
};

static enum button_event button_read_event(const enum button button) {
    static bool buttons_were_pressed[BUTTONS_COUNT] = { false };
    enum button_event button_event = BUTTON_IDLE;

    if (
            BUTTON_IS_PRESSED(BUTTON_PIN[button]) == true
            && buttons_were_pressed[button] == false
    ) {
        buttons_were_pressed[button] = true;
        button_event = BUTTON_PRESSED;
    } else if (
            BUTTON_IS_PRESSED(BUTTON_PIN[button]) == false
            && buttons_were_pressed[button] == true
    ) {
        buttons_were_pressed[button] = false;
        button_event = BUTTON_RELEASED;
    }

    return button_event;
}

/* ************************************************************************** */

void switch_to_next_wavetable() {
    enum synth_wavetable current = synth_get_wavetable();
    enum synth_wavetable next = (current + 1) % SYNTH_WAVETABLES_COUNT;
    synth_set_wavetable(next);
}

/* Event loop *************************************************************** */

void loop(void) {
    const enum button_event button_event = button_read_event(BUTTON_A);

    switch (button_event) {
        case BUTTON_PRESSED:
            switch_to_next_wavetable();
        case BUTTON_IDLE:
            break;
        case BUTTON_RELEASED:
            break;
    }
}
