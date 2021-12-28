#ifndef TIMER0_H
#define TIMER0_H

#include <stdint.h>

/* 16 bits representing TCCR0B << 8 | TCCR0A */
enum timer0_waveform_generation_mode {
    /*                     WGM02   | WGM01  | WGM00 */
    TIMER0_WGM_NORMAL    = 0 << 11 | 0 << 1 | 0 << 0,
    TIMER0_WGM_PWM_PC_FF = 0 << 11 | 0 << 1 | 1 << 0, /* Phase correct PWM, TOP = 0xFF */
    TIMER0_WGM_CTC       = 0 << 11 | 1 << 1 | 0 << 0,
    TIMER0_WGM_PWM_FF    = 0 << 11 | 1 << 1 | 1 << 0, /* Fast PWM, TOP = 0xFF */
    TIMER0_WGM_PWM_PC_R  = 1 << 11 | 0 << 1 | 1 << 0, /* Phase correct PWM, TOP = OCRA */
    TIMER0_WGM_PWM_R     = 1 << 11 | 1 << 1 | 1 << 0, /* FAST PWM, TOP = OCRA */
};

enum timer0_clock_select {
    /*            CS02   | CS01   | CS00 */
    TIMER0_CS_NO_CLOCK    = 0 << 2 | 0 << 1 | 0 << 0,
    TIMER0_CS_NO_SCALING  = 0 << 2 | 0 << 1 | 1 << 0,
    TIMER0_CS_DIV_8       = 0 << 2 | 1 << 1 | 0 << 0,
    TIMER0_CS_DIV_64      = 0 << 2 | 1 << 1 | 1 << 0,
    TIMER0_CS_DIV_256     = 1 << 2 | 0 << 1 | 0 << 0,
    TIMER0_CS_DIV_1024    = 1 << 2 | 0 << 1 | 1 << 0,
    TIMER0_CS_EXT_FALLING = 1 << 2 | 1 << 1 | 0 << 0,
    TIMER0_CS_EXT_RISING  = 1 << 2 | 1 << 1 | 0 << 0,
};

/* To be shifted by 6 for COM0An and by 4 for COM0Bn */
enum timer0_compare_output_mode {
    /*         COM0x1 | COM0x0 */
    TIMER0_COM_DISABLED = 0 << 1 | 0 << 0,
    TIMER0_COM_TOGGLE   = 0 << 1 | 1 << 0,
    TIMER0_COM_CLEAR    = 1 << 1 | 0 << 0,
    TIMER0_COM_SET      = 1 << 1 | 1 << 0,
};

void timer0_init(
    enum timer0_waveform_generation_mode waveform_generation_mode,
    enum timer0_clock_select clock_select,
    enum timer0_compare_output_mode compare_output_a_mode,
    enum timer0_compare_output_mode compare_output_b_mode
);

/* Drives OC0A, which is PD6, which is Arduino output 6 */
void timer0_set_compare_register_a(uint8_t value);

/* Drives OC0B, which is PD5, which is Arduino output 5 */
void timer0_set_compare_register_b(uint8_t value);

#endif /* TIMER0_H */
