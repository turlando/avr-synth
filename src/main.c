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

/* Number of voices. */
#define OSCILLATORS_COUNT 1

/* Volume of each oscillators is divided by 2^OSCILLATOR_ATTENUATION. */
#define OSCILLATOR_ATTENUATION 0

/* Voices frequency. */
static const uint16_t oscillator_frequency = 207; /* Ab3 */

/*
 * Low Frequency Oscillator frequency unscaled. This value is then divided by
 * lfo_scale to obtain the effective frequency.
 */
static const uint16_t lfo_frequency = 1;
static const uint8_t lfo_scale = 8;

static const uint16_t oscillator_step = DDS_STEP(oscillator_frequency);
static const uint16_t lfo_step = DDS_STEP(lfo_frequency);

/* ************************************************************************** */

#define VOLUME_MAX 255U

#define ADSR_CYCLES(ms) (ms) * 1000UL / (PWM_PERIOD)
#define ADSR_RATE(cycles, volume_delta) (cycles) / volume_delta

static const uint32_t attack_cycles = ADSR_CYCLES(5000);
static const uint32_t attack_rate = ADSR_RATE(attack_cycles, VOLUME_MAX);

/* ************************************************************************** */

#define BUTTON_IS_PRESSED (port_d_get_pin(PORT_D_PIN_2) == PORT_LOW)

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
    static uint16_t accumulator = 0;
    static uint8_t cycles = 0;

    /* ********************************************************************** */

    accumulator += oscillator_step;

    uint8_t step = accumulator >> 8;
    uint16_t mixer = SAW_INT8_256[step];

    /* ********************************************************************** */

    static uint32_t volume = 0;
    static uint32_t adsr_cycles = 0;
    static bool button_was_pressed = false;

    if (BUTTON_IS_PRESSED == true && button_was_pressed == false) {
        button_was_pressed = true;
        adsr_cycles = 0;
    } else if (BUTTON_IS_PRESSED == false && button_was_pressed == true) {
        button_was_pressed = false;
        adsr_cycles = 0;
    } else {
        adsr_cycles++;
    }

    if (
        button_was_pressed == true
        && adsr_cycles < attack_cycles
        && adsr_cycles > attack_rate * volume
        && volume < VOLUME_MAX
    ) {
        volume++;
    } else if (button_was_pressed == false) {
        volume = 0;
    }

    /* ********************************************************************** */

    //uint8_t pwm_value = BUTTON_IS_PRESSED ? 128 + mixer : 0;
    uint8_t pwm_value = ((128 + mixer) * volume) >> 8;

    /* ********************************************************************** */

    timer0_wait_overflow();
    timer0_set_compare_register_a(pwm_value);
    timer0_clear_overflow();

    /* ********************************************************************** */

    cycles++;
}
