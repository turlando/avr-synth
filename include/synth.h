#ifndef SYNTH_H
#define SYNTH_H

#include <stdint.h>

/* ************************************************************************** */

#define SYNTH_OSCILLATORS_COUNT 2

enum synth_oscillator {
    SYNTH_OSCILLATOR_A,
    SYNTH_OSCILLATOR_B,
};

/* ************************************************************************** */

#define SYNTH_WAVETABLES_COUNT 3

enum synth_wavetable {
    SYNTH_WAVETABLE_NONE,
    SYNTH_WAVETABLE_SIN,
    SYNTH_WAVETABLE_SAW,
};

/* ************************************************************************** */

enum synth_wavetable synth_get_wavetable(enum synth_oscillator oscillator);

void synth_set_wavetable(
    const enum synth_oscillator oscillator,
    const enum synth_wavetable wavetable
);

/* ************************************************************************** */

void synth_set_frequency(
    enum synth_oscillator oscillator,
    uint16_t frequency
);

/* ************************************************************************** */

uint8_t synth_next_sample(enum synth_oscillator oscillator);

/* ************************************************************************** */

#endif /* SYNTH_H */
