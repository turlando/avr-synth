#include <synth.h>

#include <stdint.h>

#include <wave/sin_int8_256.h>

#define FREQUENCY 440U
#define PWM_FREQUENCY (F_CPU) / 256U
#define ACCUMULATOR_STEP (FREQUENCY) * 65536UL / (PWM_FREQUENCY)

uint8_t synth_next_sample() {
    static uint16_t accumulator = 0;
    accumulator += ACCUMULATOR_STEP;
    return 128 + SIN_INT8_256[accumulator >> 8];
}
