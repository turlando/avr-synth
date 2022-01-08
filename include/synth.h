#ifndef SYNTH_H
#define SYNTH_H

#include <stdint.h>

#define SYNTH_WAVETABLES_COUNT 3

enum synth_wavetable {
    SYNTH_WAVETABLE_NONE,
    SYNTH_WAVETABLE_SIN,
    SYNTH_WAVETABLE_SAW,
};

enum synth_wavetable synth_get_wavetable();
void synth_set_wavetable(enum synth_wavetable wavetable);

void synth_set_frequency(uint16_t frequency);

uint8_t synth_next_sample();

#endif /* SYNTH_H */
