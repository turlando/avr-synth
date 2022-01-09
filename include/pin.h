#ifndef PIN_H
#define PIN_H

#include <stdint.h>

enum pin_state {
    PIN_LOW =  0,
    PIN_HIGH = 1,
};

enum pin {
    PIN_0,  /* Port D, pin 0 */
    PIN_1,  /* Port D, pin 1 */
    PIN_2,  /* Port D, pin 2 */
    PIN_3,  /* Port D, pin 3 */
    PIN_4,  /* Port D, pin 4 */
    PIN_5,  /* Port D, pin 5 */
    PIN_6,  /* Port D, pin 6 */
    PIN_7,  /* Port D, pin 7 */

    PIN_8,  /* Port B, pin 0 */
    PIN_9,  /* Port B, pin 1 */
    PIN_10, /* Port B, pin 2 */
    PIN_11, /* Port B, pin 2 */
    PIN_12, /* Port B, pin 3 */
    PIN_13, /* Port B, pin 4 */

    PIN_A0, /* Port C, pin 0 */
    PIN_A1, /* Port C, pin 1 */
    PIN_A2, /* Port C, pin 2 */
    PIN_A3, /* Port C, pin 3 */
    PIN_A4, /* Port C, pin 4 */
    PIN_A5, /* Port C, pin 5 */
};

void pin_set_output(enum pin pin);
void pin_set_input(enum pin pin);
void pin_set_pullup(enum pin pin);
void pin_set_low(enum pin pin);
void pin_set_high(enum pin pin);

enum pin_state pin_digital_read(enum pin pin);
uint16_t pin_analog_read(enum pin pin);

#endif /* PIN_H */
