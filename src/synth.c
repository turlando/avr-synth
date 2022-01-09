#include <synth.h>

#include <stdint.h>

#include <wave/sin_uint8_256.h>
#include <wave/saw_uint8_256.h>

/* ************************************************************************** */

#define PWM_FREQUENCY (F_CPU) / 256U
#define ACCUMULATOR_STEP(frequency) (frequency) * 65536UL / (PWM_FREQUENCY)

/* ************************************************************************** */

static enum synth_wavetable g_wavetables[SYNTH_OSCILLATORS_COUNT]
    = { SYNTH_WAVETABLE_NONE };

enum synth_wavetable synth_get_wavetable(
    const enum synth_oscillator oscillator
) {
    return g_wavetables[oscillator];
}

void synth_set_wavetable(
    const enum synth_oscillator oscillator,
    const enum synth_wavetable wavetable
) {
    g_wavetables[oscillator] = wavetable;
}

/* ************************************************************************** */

static uint16_t g_accumulators_step[SYNTH_OSCILLATORS_COUNT] = { 0 };
static uint16_t g_frequencies[SYNTH_OSCILLATORS_COUNT] = { 0 };

static uint16_t synth_get_accumulator_step(
    const enum synth_oscillator oscillator
) {
    return g_accumulators_step[oscillator];
}

static void synth_set_accumulator_step(
    const enum synth_oscillator oscillator,
    const uint16_t accumulator_step
) {
    g_accumulators_step[oscillator] = accumulator_step;
}

void synth_set_frequency(
    const enum synth_oscillator oscillator,
    const uint16_t frequency
) {
    g_frequencies[oscillator] = frequency;
    synth_set_accumulator_step(oscillator, ACCUMULATOR_STEP(frequency));
}

/* ************************************************************************** */

static uint8_t g_volumes[SYNTH_OSCILLATORS_COUNT] = { 0 };

uint8_t synth_get_volume(
    const enum synth_oscillator oscillator
) {
    return g_volumes[oscillator];
}

void synth_set_volume(
    const enum synth_oscillator oscillator,
    const uint8_t volume
) {
    g_volumes[oscillator] = volume;
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

static uint8_t synth_next_oscillator_sample(
    const enum synth_oscillator oscillator
) {
    static uint16_t accumulators[SYNTH_OSCILLATORS_COUNT] = { 0 };
    accumulators[oscillator] += synth_get_accumulator_step(oscillator);

    return synth_get_sample(
        synth_get_wavetable(oscillator),
        accumulators[oscillator] >> 8
    );
}

uint8_t synth_next_sample() {
    uint8_t mixer = 0;

    for (uint8_t i = 0; i < SYNTH_OSCILLATORS_COUNT; i++) {
        uint8_t sample
            = synth_next_oscillator_sample(i)
            * synth_get_volume(i) / SYNTH_VOLUME_MAX;
        mixer += sample;
    }

    return mixer;
}
