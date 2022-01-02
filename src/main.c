#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>

#include <port.h>
#include <timer0.h>
#include <wave/saw_int8_256.h>

/* ************************************************************************** */

/*
 * PWM overflow frequency when timer is running in fast PWM mode
 * and with no prescaling.
 * Check ATmega328P datasheet section 14.7.3 Fast PWM Mode page 80.
 */
#define PWM_FREQUENCY F_CPU / 256U

/*
 * PWM overflow period in microseconds.
 * PWM_PERIOD = 1 / PWM_FREQUENCY
 */
#define PWM_PERIOD 16U

/* ************************************************************************** */

/*
 * How to compute the DDS phase accumulator step.
 *
 * f_out = (f_pwm * step) / (2^counter_size)
 * step = (f_out * (2^counter_bits)) / f_pwm
 *
 * Assuming counter_bits = 16.
 * uint16_t must be used to index the wavetable and then truncated
 * to the most significant part by right-shifting by 8 as they
 * have 256 values.
 */
#define DDS_STEP(frequency) (frequency) * 65536 / (PWM_FREQUENCY)

/* ************************************************************************** */

static const uint16_t oscillator_frequency = 207; /* Ab3 */
static const uint16_t oscillator_step = DDS_STEP(oscillator_frequency);

/* ************************************************************************** */

#define VOLUME_MAX 256U

#define ADSR_CYCLES(ms) (ms) * 1000UL / (PWM_PERIOD)
#define ADSR_RATE(cycles, volume_delta) (cycles) / (volume_delta)

static const uint16_t attack_time   = 5000;
static const uint16_t decay_time    = 5000;
static const uint8_t sustain_volume = 127;
static const uint16_t release_time  = 5000;

static const uint32_t attack_cycles = ADSR_CYCLES(attack_time);
static const uint32_t attack_rate = ADSR_RATE(attack_cycles, VOLUME_MAX);

static const uint32_t decay_cycles = ADSR_CYCLES(decay_time);
static const uint32_t decay_rate
    = ADSR_RATE(decay_cycles, VOLUME_MAX - sustain_volume);

static const uint32_t release_cycles = ADSR_CYCLES(release_time);
static const uint32_t release_rate = ADSR_RATE(release_cycles, sustain_volume);

enum adsr_state {
    ADSR_NONE,
    ADSR_ATTACK,
    ADSR_DECAY,
    ADSR_SUSTAIN,
    ADSR_RELEASE
};

/* ************************************************************************** */

#define BUTTON_IS_PRESSED (port_d_get_pin(PORT_D_PIN_2) == PORT_LOW)

enum button_event {
    BUTTON_PRESS,
    BUTTON_IDLE,
    BUTTON_RELEASE,
};

static enum button_event button_read_event() {
    static bool button_was_pressed = false;
    enum button_event button_event = BUTTON_IDLE;

    if (BUTTON_IS_PRESSED == true && button_was_pressed == false) {
        button_was_pressed = true;
        button_event = BUTTON_PRESS;
    } else if (BUTTON_IS_PRESSED == false && button_was_pressed == true) {
        button_was_pressed = false;
        button_event = BUTTON_RELEASE;
    }

    return button_event;
}

/* ************************************************************************** */

static void loop(void);

int main(void) {
    port_d_set_output(PORT_D_PIN_6); /* Speaker. Arduino port 6. */

    port_d_set_input(PORT_D_PIN_2);  /* Button. Arduino port 2. */
    port_d_set_pullup(PORT_D_PIN_2);

    timer0_init(
        TIMER0_WGM_PWM_FF,
        TIMER0_CS_NO_SCALING,
        TIMER0_COM_CLEAR,
        TIMER0_COM_DISABLED
    );

    while (1) loop();
    return 0;
}

static void loop(void) {
    static uint8_t cycles = 0;
    static uint16_t accumulator = 0;

    /* ********************************************************************** */

    static uint32_t volume = 0;
    static uint32_t adsr_cycles = 0;
    static enum adsr_state adsr_state = ADSR_NONE;

    const enum button_event button_event = button_read_event();

    switch (button_event) {
        case BUTTON_PRESS:
            adsr_state = ADSR_ATTACK;
            adsr_cycles = 0;
            break;

        case BUTTON_RELEASE:
            adsr_state = ADSR_RELEASE;
            adsr_cycles = 0;
            break;

        case BUTTON_IDLE:
            adsr_cycles++;
            break;
    }

    switch (adsr_state) {
        case ADSR_NONE:
            volume = 0;
            break;

        case ADSR_ATTACK:
            if (
                adsr_cycles < attack_cycles
                && adsr_cycles > attack_rate * volume
                && volume < VOLUME_MAX
            ) {
                volume++;
            } else if (adsr_cycles >= attack_cycles) {
                adsr_state = ADSR_DECAY;
            }
            break;

        case ADSR_DECAY:
            if (
                adsr_cycles < attack_cycles + decay_cycles
                && adsr_cycles - attack_cycles
                   > decay_rate * (VOLUME_MAX - volume)
                && volume > sustain_volume
            ) {
                volume--;
            } else if (adsr_cycles >= attack_cycles + decay_cycles) {
                adsr_state = ADSR_SUSTAIN;
            }
            break;

        case ADSR_SUSTAIN:
            break;

        case ADSR_RELEASE:
            if (
                adsr_cycles < release_cycles
                && adsr_cycles > release_rate * (sustain_volume - volume)
                && volume > 0
            ) {
                volume--;
            } else if (adsr_cycles >= release_cycles) {
                adsr_state = ADSR_NONE;
            }
            break;
    }

    /* ********************************************************************** */

    /* Truncate accumulator and pick a sample from the wavetable. */
    uint16_t sample = SAW_INT8_256[accumulator >> 8];

    /* Convert from int8_t to uint8_t. */
    uint8_t pwm_value = ((128 + sample) * volume) >> 8;

    /* ********************************************************************** */

    timer0_wait_overflow();
    timer0_set_compare_register_a(pwm_value);
    timer0_clear_overflow();

    /* ********************************************************************** */

    cycles++;
    accumulator += oscillator_step;
}
