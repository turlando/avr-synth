#ifndef PORT_H
#define PORT_H

enum port_state {
    PORT_LOW  = 0,
    PORT_HIGH = 1,
};

enum port_b_pin {
    PORT_B_PIN_0 = 1 << 0, /* Arduino pin 8 */
    PORT_B_PIN_1 = 1 << 1, /* Arduino pin 9 */
    PORT_B_PIN_2 = 1 << 2, /* Arduino pin 10 */
    PORT_B_PIN_3 = 1 << 3, /* Arduino pin 11 */
    PORT_B_PIN_4 = 1 << 4, /* Arduino pin 12 */
    PORT_B_PIN_5 = 1 << 5, /* Arduino pin 13 */
};

enum port_c_pin {
    PORT_C_PIN_0 = 1 << 0, /* Arduino pin A0 */
    PORT_C_PIN_1 = 1 << 1, /* Arduino pin A1 */
    PORT_C_PIN_2 = 1 << 2, /* Arduino pin A2 */
    PORT_C_PIN_3 = 1 << 3, /* Arduino pin A3 */
    PORT_C_PIN_4 = 1 << 4, /* Arduino pin A4 */
    PORT_C_PIN_5 = 1 << 5, /* Arduino pin A5 */
};

enum port_d_pin {
    PORT_D_PIN_0 = 1 << 0, /* Arduino pin 0 */
    PORT_D_PIN_1 = 1 << 1, /* Arduino pin 1 */
    PORT_D_PIN_2 = 1 << 2, /* Arduino pin 2 */
    PORT_D_PIN_3 = 1 << 3, /* Arduino pin 3 */
    PORT_D_PIN_4 = 1 << 4, /* Arduino pin 4 */
    PORT_D_PIN_5 = 1 << 5, /* Arduino pin 5 */
    PORT_D_PIN_6 = 1 << 6, /* Arduino pin 6 */
    PORT_D_PIN_7 = 1 << 7, /* Arduino pin 7 */
};

void port_b_set_output(enum port_b_pin pins);
void port_b_set_input(enum port_b_pin pins);

void port_c_set_output(enum port_c_pin pins);
void port_c_set_input(enum port_c_pin pins);

void port_d_set_output(enum port_d_pin pins);
void port_d_set_input(enum port_d_pin pins);
void port_d_set_high(enum port_d_pin pins);
void port_d_set_low(enum port_d_pin pins);
void port_d_set_pullup(enum port_d_pin pins);
enum port_state port_d_get_pin(enum port_d_pin pin);

#endif /* PORT_H */
