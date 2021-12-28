#include <port.h>

#include <avr/io.h>

void port_b_set_output(enum port_b_pin pins) {
    DDRB |= pins;
}

void port_b_set_input(enum port_b_pin pins) {
    DDRB &= ~pins;
}

void port_c_set_output(enum port_c_pin pins) {
    DDRC |= pins;
}

void port_c_set_input(enum port_c_pin pins) {
    DDRC &= ~pins;
}

void port_d_set_output(enum port_d_pin pins) {
    DDRD |= pins;
}

void port_d_set_input(enum port_d_pin pins) {
    DDRD &= pins;
}
