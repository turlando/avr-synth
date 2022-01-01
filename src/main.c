#include <stdint.h>
#include <avr/io.h>

#include <port.h>
#include <timer0.h>
#include <wave/saw_int8_256.h>

/* ************************************************************************** */

/*
 * PWM frequency when timer is running in fast PWM mode and with no prescaling.
 * Check ATmega328P datasheet section 14.7.3 Fast PWM Mode page 80.
 */
#define PWM_FREQUENCY F_CPU / 256

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

/* Number of voices. */
#define OSCILLATORS_COUNT 2

/* Volume of each oscillators is divided by 2^OSCILLATOR_ATTENUATION. */
#define OSCILLATOR_ATTENUATION 1

/* Voices frequency. */
static const uint16_t oscillator_frequency = 440;

/*
 * Low Frequency Oscillator frequency.
 * It is used to modulate the phase shift over time of the second oscillator.
 * The phase of the second oscillator sweeps from 0% to 100% at such frequency.
 */
static const uint16_t lfo_frequency = 1;

static const uint16_t oscillator_step = DDS_STEP(oscillator_frequency);
static const uint16_t lfo_step = DDS_STEP(lfo_frequency);

/* ************************************************************************** */

static void loop(void);

int main(void) {
    port_d_set_output(PORT_D_PIN_6);

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
    static uint16_t accumulators[OSCILLATORS_COUNT] = {0};
    uint16_t mixer = 0;

    for (uint8_t i = 0; i < OSCILLATORS_COUNT; i++) {
        /* No phase shift for the first oscillator by multiplying by zero. */
        accumulators[i] += oscillator_step + (lfo_step * i);

        /* Truncate 16 bits step to most significant 8 bits. */
        uint8_t step = accumulators[i] >> 8;

        /*
         * Before adding a given sample in the wavetable to the output
         * mixer we right-shift it by 1 in order to attenuate the oscillator
         * volume and avoid clipping the output.
         */
        mixer += SAW_INT8_256[step] >> OSCILLATOR_ATTENUATION;
    }

    /* Convert from int8_t to uint8_t. */
    uint8_t pwm_value = 128 + mixer;

    timer0_wait_overflow();
    timer0_set_compare_register_a(pwm_value);
    timer0_clear_overflow();
}
