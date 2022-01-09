#ifndef BUTTON_H
#define BUTTON_H

#include <pin.h>

enum button_event {
    BUTTON_PRESSED,
    BUTTON_IDLE,
    BUTTON_RELEASED
};

enum button_event button_get_event(enum pin pin);

#endif /* BUTTON_H */
