#include <button.h>

#include <stdbool.h>

#include <pin.h>

#define BUTTON_IS_PRESSED(pin) (pin_digital_read(pin) == PIN_LOW)

enum button_event button_get_event(const enum pin pin) {
    static bool were_pressed[PIN_COUNT] = { false };

    const bool is_pressed = BUTTON_IS_PRESSED(pin);
    const bool was_pressed = were_pressed[pin];

    if (is_pressed == true && was_pressed == false) {
        were_pressed[pin] = true;
        return BUTTON_PRESSED;
    }

    if (is_pressed == false && was_pressed == true) {
        were_pressed[pin] = false;
        return BUTTON_RELEASED;
    }

    return BUTTON_IDLE;
}
