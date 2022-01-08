#include <port.h>

#include <avr/io.h>

/* ************************************************************************** */

void port_b_set_output(const enum port_b_pin pins) {
    DDRB |= pins;
}

void port_b_set_input(const enum port_b_pin pins) {
    DDRB &= ~pins;
}

void port_b_set_pullup(const enum port_b_pin pins) {
    PORTB |= pins;
}

void port_b_set_high(const enum port_b_pin pins) {
    PORTB |= pins;
}

void port_b_set_low(const enum port_b_pin pins) {
    PORTB &= ~pins;
}

enum port_state port_b_get_pin(const enum port_b_pin pin) {
    return PINB & pin;
}

/* ************************************************************************** */

void port_c_set_output(const enum port_c_pin pins) {
    DDRC |= pins;
}

void port_c_set_input(const enum port_c_pin pins) {
    DDRC &= ~pins;
}

void port_c_set_pullup(const enum port_c_pin pins) {
    PORTC |= pins;
}

void port_c_set_high(const enum port_c_pin pins) {
    PORTC |= pins;
}

void port_c_set_low(const enum port_c_pin pins) {
    PORTC &= ~pins;
}

enum port_state port_c_get_pin(const enum port_c_pin pin) {
    return PINC & pin;
}

/* ************************************************************************** */

void port_d_set_output(const enum port_d_pin pins) {
    DDRD |= pins;
}

void port_d_set_input(const enum port_d_pin pins) {
    DDRD &= ~pins;
}

void port_d_set_high(const enum port_d_pin pins) {
    PORTD |= pins;
}

void port_d_set_pullup(const enum port_d_pin pins) {
    PORTD |= pins;
}

void port_d_set_low(const enum port_d_pin pins) {
    PORTD &= ~pins;
}

enum port_state port_d_get_pin(const enum port_d_pin pin) {
    return PIND & pin;
}
