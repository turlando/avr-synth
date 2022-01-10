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

#define SYNTH_WAVETABLES_COUNT 4

enum synth_wavetable {
    SYNTH_WAVETABLE_NONE,
    SYNTH_WAVETABLE_SIN,
    SYNTH_WAVETABLE_TRI,
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

#define SYNTH_VOLUME_MAX 255U

void synth_set_volume(
    const enum synth_oscillator oscillator,
    const uint8_t volume
);

/* ************************************************************************** */

uint8_t synth_next_sample();

/* ************************************************************************** */

#endif /* SYNTH_H */
