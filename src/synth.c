#include <synth.h>

#include <stdint.h>

#include <wave/sin_uint8_256.h>
#include <wave/saw_uint8_256.h>

/* ************************************************************************** */

#define PWM_FREQUENCY (F_CPU) / 256U
#define ACCUMULATOR_STEP(frequency) (frequency) * 65536UL / (PWM_FREQUENCY)

/* ************************************************************************** */

static enum synth_wavetable g_wavetable = SYNTH_WAVETABLE_NONE;

enum synth_wavetable synth_get_wavetable() {
    return g_wavetable;
}

void synth_set_wavetable(const enum synth_wavetable wavetable) {
    g_wavetable = wavetable;
}

/* ************************************************************************** */

static uint16_t g_accumulator_step = 0;
static uint16_t g_frequency = 0;

static uint16_t synth_get_accumulator_step() {
    return g_accumulator_step;
}

static void synth_set_accumulator_step(const uint16_t accumulator_step) {
    g_accumulator_step = accumulator_step;
}

void synth_set_frequency(const uint16_t frequency) {
    g_frequency = frequency;
    synth_set_accumulator_step(ACCUMULATOR_STEP(frequency));
}

/* ************************************************************************** */

static int8_t synth_get_sample(
    const enum synth_wavetable wavetable,
    const uint8_t i
) {
    switch (wavetable) {
        case SYNTH_WAVETABLE_NONE:
            return 0;
        case SYNTH_WAVETABLE_SIN:
            return WAVE_SIN_UINT8_256[i];
        case SYNTH_WAVETABLE_SAW:
            return WAVE_SAW_UINT8_256[i];
    }

    return 0;
}

/* ************************************************************************** */

uint8_t synth_next_sample() {
    static uint16_t accumulator = 0;
    accumulator += synth_get_accumulator_step();
    return synth_get_sample(synth_get_wavetable(), accumulator >> 8);
}
