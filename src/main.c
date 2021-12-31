#include <stdint.h>
#include <avr/io.h>

#include <port.h>
#include <timer0.h>
#include <wave/sin_int8_256.h>

/* Tone frequency we want to generate. */
static const uint16_t frequency = 440;

/*
 * PWM frequency when timer is running in fast PWM mode and with no prescaling.
 * Check ATmega328P datasheet section 14.7.3 Fast PWM Mode page 80.
 */
static const uint16_t pwm_frequency = F_CPU / 256;

/*
 * f_out = (f_pwm * step) / (2^counter_size)
 * step = (f_out * (2^counter_size)) / f_pwm
 */
static const uint16_t accumulator_step = frequency * 65536 / pwm_frequency;

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
    static uint16_t accumulator = 0;
    static uint8_t value = 0;

    accumulator += accumulator_step;
    value = 128 + SIN_INT8_256[accumulator >> 8];

    timer0_wait_overflow();
    timer0_set_compare_register_a(value);
    timer0_clear_overflow();
}
