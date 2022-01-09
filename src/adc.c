#include <adc.h>

#include <stdint.h>
#include <avr/io.h>

void adc_init(
    const enum adc_voltage_reference voltage_reference,
    const enum adc_prescaler prescaler,
    const enum adc_result_adjust result_adjust
) {
    ADMUX |= voltage_reference << 6;
    ADCSRA |= prescaler;
    ADMUX |= result_adjust << 5;
    ADCSRA |= 1 << ADEN;
}

void adc_set_input(const enum adc_input input) {
    ADMUX = (ADMUX & 0xf0) | input;
}

void adc_start_conversion(void) {
    ADCSRA |= (1 << ADSC);
}

void adc_wait_conversion(void) {
    loop_until_bit_is_clear(ADCSRA, ADSC);
}

uint8_t adc_read_low(void) {
    return ADCL;
}

uint8_t adc_read_high(void) {
    return ADCH;
}

uint16_t adc_read_all(void) {
    return ADC;
}
