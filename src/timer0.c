#include <timer0.h>

#include <avr/io.h>

void timer0_init(
    const enum timer0_waveform_generation_mode waveform_generation_mode,
    const enum timer0_clock_select clock_select,
    const enum timer0_compare_output_mode compare_output_a_mode,
    const enum timer0_compare_output_mode compare_output_b_mode
) {
    TCCR0A |= waveform_generation_mode & 0x00FF;
    TCCR0B |= waveform_generation_mode >> 8;

    TCCR0B |= clock_select;

    TCCR0A |= compare_output_a_mode << 6;
    TCCR0A |= compare_output_b_mode << 4;
}

/* Drives OC0A, which is PD6, which is Arduino pin 6. */
void timer0_set_compare_register_a(const uint8_t value) {
    OCR0A = value;
}

/* Drives OC0B, which is PD5, which is Arduino pin 5. */
void timer0_set_compare_register_b(const uint8_t value) {
    OCR0B = value;
}

void timer0_wait_overflow() {
    loop_until_bit_is_set(TIFR0, TOV0);
}

void timer0_clear_overflow() {
    TIFR0 |= (1 << TOV0);
}
