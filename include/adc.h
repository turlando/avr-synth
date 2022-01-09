#ifndef ADC_H
#define ADC_H

#include <stdint.h>

enum adc_voltage_reference {
    /*                               REFS1  | REFS0 */
    ADC_VOLTAGE_REFERENCE_AREF     = 0 << 1 | 0 << 0,
    ADC_VOLTAGE_REFERENCE_AVCC     = 1 << 1 | 1 << 0,
    ADC_VOLTAGE_REFERENCE_INTERNAL = 1 << 1 | 1 << 0
};

enum adc_prescaler {
    /*                      ADPS2  | ADPS0  | ADPS 0 */
    ADC_PRESCALER_DIV_2   = 0 << 2 | 0 << 1 | 0 << 1,
    ADC_PRESCALER_DIV_4   = 0 << 2 | 1 << 1 | 0 << 0,
    ADC_PRESCALER_DIV_8   = 0 << 2 | 1 << 1 | 1 << 1,
    ADC_PRESCALER_DIV_16  = 1 << 2 | 0 << 1 | 0 << 0,
    ADC_PRESCALER_DIV_32  = 1 << 2 | 0 << 1 | 1 << 0,
    ADC_PRESCALER_DIV_64  = 1 << 2 | 1 << 1 | 0 << 0,
    ADC_PRESCALER_DIV_128 = 1 << 2 | 1 << 1 | 1 << 0,
};

enum adc_result_adjust {
    /*                        ADLAR */
    ADC_RESULT_ADJUST_RIGHT = 0,
    ADC_RESULT_ADJUST_LEFT  = 1,
};

enum adc_input {
    /*              MUX3   | MUX2   | MUX1   | MUX0 */
    ADC_INPUT_0   = 0 << 3 | 0 << 2 | 0 << 1 | 0 << 0,
    ADC_INPUT_1   = 0 << 3 | 0 << 2 | 0 << 1 | 1 << 0,
    ADC_INPUT_2   = 0 << 3 | 0 << 2 | 1 << 1 | 0 << 0,
    ADC_INPUT_3   = 0 << 3 | 0 << 2 | 1 << 1 | 1 << 0,
    ADC_INPUT_4   = 0 << 3 | 1 << 2 | 0 << 1 | 0 << 0,
    ADC_INPUT_5   = 0 << 3 | 1 << 2 | 0 << 1 | 1 << 0,
    ADC_INPUT_6   = 0 << 3 | 1 << 2 | 1 << 1 | 0 << 0,
    ADC_INPUT_7   = 0 << 3 | 1 << 2 | 1 << 1 | 1 << 0,
    ADC_INPUT_8   = 1 << 3 | 0 << 2 | 0 << 1 | 0 << 0,
    ADC_INPUT_VBG = 1 << 3 | 1 << 2 | 1 << 1 | 0 << 0,
    ADC_INPUT_GND = 1 << 3 | 1 << 2 | 1 << 1 | 1 << 0,
};

void adc_init(
    const enum adc_voltage_reference voltage_reference,
    const enum adc_prescaler prescaler,
    const enum adc_result_adjust result_adjust
);

void adc_set_input(const enum adc_input input);

void adc_start_conversion(void);
void adc_wait_conversion(void);

uint8_t adc_read_low(void);
uint8_t adc_read_high(void);
uint16_t adc_read_all(void);

#endif /* ADC_H */
