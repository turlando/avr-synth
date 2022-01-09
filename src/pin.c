#include <pin.h>

#include <stdint.h>

#include <port.h>
#include <adc.h>

void pin_set_output(const enum pin pin) {
    switch (pin) {
        case PIN_0:  port_d_set_output(PORT_D_PIN_0); break;
        case PIN_1:  port_d_set_output(PORT_D_PIN_1); break;
        case PIN_2:  port_d_set_output(PORT_D_PIN_2); break;
        case PIN_3:  port_d_set_output(PORT_D_PIN_3); break;
        case PIN_4:  port_d_set_output(PORT_D_PIN_4); break;
        case PIN_5:  port_d_set_output(PORT_D_PIN_5); break;
        case PIN_6:  port_d_set_output(PORT_D_PIN_6); break;
        case PIN_7:  port_d_set_output(PORT_D_PIN_6); break;

        case PIN_8:  port_b_set_output(PORT_B_PIN_0); break;
        case PIN_9:  port_b_set_output(PORT_B_PIN_1); break;
        case PIN_10: port_b_set_output(PORT_B_PIN_2); break;
        case PIN_11: port_b_set_output(PORT_B_PIN_3); break;
        case PIN_12: port_b_set_output(PORT_B_PIN_4); break;
        case PIN_13: port_b_set_output(PORT_B_PIN_5); break;

        case PIN_A0: port_c_set_output(PORT_C_PIN_0); break;
        case PIN_A1: port_c_set_output(PORT_C_PIN_1); break;
        case PIN_A2: port_c_set_output(PORT_C_PIN_2); break;
        case PIN_A3: port_c_set_output(PORT_C_PIN_3); break;
        case PIN_A4: port_c_set_output(PORT_C_PIN_4); break;
        case PIN_A5: port_c_set_output(PORT_C_PIN_5); break;
    }
}

void pin_set_input(const enum pin pin) {
    switch (pin) {
        case PIN_0:  port_d_set_input(PORT_D_PIN_0); break;
        case PIN_1:  port_d_set_input(PORT_D_PIN_1); break;
        case PIN_2:  port_d_set_input(PORT_D_PIN_2); break;
        case PIN_3:  port_d_set_input(PORT_D_PIN_3); break;
        case PIN_4:  port_d_set_input(PORT_D_PIN_4); break;
        case PIN_5:  port_d_set_input(PORT_D_PIN_5); break;
        case PIN_6:  port_d_set_input(PORT_D_PIN_6); break;
        case PIN_7:  port_d_set_input(PORT_D_PIN_6); break;

        case PIN_8:  port_b_set_input(PORT_B_PIN_0); break;
        case PIN_9:  port_b_set_input(PORT_B_PIN_1); break;
        case PIN_10: port_b_set_input(PORT_B_PIN_2); break;
        case PIN_11: port_b_set_input(PORT_B_PIN_3); break;
        case PIN_12: port_b_set_input(PORT_B_PIN_4); break;
        case PIN_13: port_b_set_input(PORT_B_PIN_5); break;

        case PIN_A0: port_c_set_input(PORT_C_PIN_0); break;
        case PIN_A1: port_c_set_input(PORT_C_PIN_1); break;
        case PIN_A2: port_c_set_input(PORT_C_PIN_2); break;
        case PIN_A3: port_c_set_input(PORT_C_PIN_3); break;
        case PIN_A4: port_c_set_input(PORT_C_PIN_4); break;
        case PIN_A5: port_c_set_input(PORT_C_PIN_5); break;
    }
}

void pin_set_pullup(const enum pin pin) {
    switch (pin) {
        case PIN_0:  port_d_set_pullup(PORT_D_PIN_0); break;
        case PIN_1:  port_d_set_pullup(PORT_D_PIN_1); break;
        case PIN_2:  port_d_set_pullup(PORT_D_PIN_2); break;
        case PIN_3:  port_d_set_pullup(PORT_D_PIN_3); break;
        case PIN_4:  port_d_set_pullup(PORT_D_PIN_4); break;
        case PIN_5:  port_d_set_pullup(PORT_D_PIN_5); break;
        case PIN_6:  port_d_set_pullup(PORT_D_PIN_6); break;
        case PIN_7:  port_d_set_pullup(PORT_D_PIN_6); break;

        case PIN_8:  port_b_set_pullup(PORT_B_PIN_0); break;
        case PIN_9:  port_b_set_pullup(PORT_B_PIN_1); break;
        case PIN_10: port_b_set_pullup(PORT_B_PIN_2); break;
        case PIN_11: port_b_set_pullup(PORT_B_PIN_3); break;
        case PIN_12: port_b_set_pullup(PORT_B_PIN_4); break;
        case PIN_13: port_b_set_pullup(PORT_B_PIN_5); break;

        case PIN_A0: port_c_set_pullup(PORT_C_PIN_0); break;
        case PIN_A1: port_c_set_pullup(PORT_C_PIN_1); break;
        case PIN_A2: port_c_set_pullup(PORT_C_PIN_2); break;
        case PIN_A3: port_c_set_pullup(PORT_C_PIN_3); break;
        case PIN_A4: port_c_set_pullup(PORT_C_PIN_4); break;
        case PIN_A5: port_c_set_pullup(PORT_C_PIN_5); break;
    }
}

void pin_set_low(const enum pin pin) {
    switch (pin) {
        case PIN_0:  port_d_set_low(PORT_D_PIN_0); break;
        case PIN_1:  port_d_set_low(PORT_D_PIN_1); break;
        case PIN_2:  port_d_set_low(PORT_D_PIN_2); break;
        case PIN_3:  port_d_set_low(PORT_D_PIN_3); break;
        case PIN_4:  port_d_set_low(PORT_D_PIN_4); break;
        case PIN_5:  port_d_set_low(PORT_D_PIN_5); break;
        case PIN_6:  port_d_set_low(PORT_D_PIN_6); break;
        case PIN_7:  port_d_set_low(PORT_D_PIN_6); break;

        case PIN_8:  port_b_set_low(PORT_B_PIN_0); break;
        case PIN_9:  port_b_set_low(PORT_B_PIN_1); break;
        case PIN_10: port_b_set_low(PORT_B_PIN_2); break;
        case PIN_11: port_b_set_low(PORT_B_PIN_3); break;
        case PIN_12: port_b_set_low(PORT_B_PIN_4); break;
        case PIN_13: port_b_set_low(PORT_B_PIN_5); break;

        case PIN_A0: port_c_set_low(PORT_C_PIN_0); break;
        case PIN_A1: port_c_set_low(PORT_C_PIN_1); break;
        case PIN_A2: port_c_set_low(PORT_C_PIN_2); break;
        case PIN_A3: port_c_set_low(PORT_C_PIN_3); break;
        case PIN_A4: port_c_set_low(PORT_C_PIN_4); break;
        case PIN_A5: port_c_set_low(PORT_C_PIN_5); break;
    }
}

void pin_set_high(const enum pin pin) {
    switch (pin) {
        case PIN_0:  port_d_set_high(PORT_D_PIN_0); break;
        case PIN_1:  port_d_set_high(PORT_D_PIN_1); break;
        case PIN_2:  port_d_set_high(PORT_D_PIN_2); break;
        case PIN_3:  port_d_set_high(PORT_D_PIN_3); break;
        case PIN_4:  port_d_set_high(PORT_D_PIN_4); break;
        case PIN_5:  port_d_set_high(PORT_D_PIN_5); break;
        case PIN_6:  port_d_set_high(PORT_D_PIN_6); break;
        case PIN_7:  port_d_set_high(PORT_D_PIN_6); break;

        case PIN_8:  port_b_set_high(PORT_B_PIN_0); break;
        case PIN_9:  port_b_set_high(PORT_B_PIN_1); break;
        case PIN_10: port_b_set_high(PORT_B_PIN_2); break;
        case PIN_11: port_b_set_high(PORT_B_PIN_3); break;
        case PIN_12: port_b_set_high(PORT_B_PIN_4); break;
        case PIN_13: port_b_set_high(PORT_B_PIN_5); break;

        case PIN_A0: port_c_set_high(PORT_C_PIN_0); break;
        case PIN_A1: port_c_set_high(PORT_C_PIN_1); break;
        case PIN_A2: port_c_set_high(PORT_C_PIN_2); break;
        case PIN_A3: port_c_set_high(PORT_C_PIN_3); break;
        case PIN_A4: port_c_set_high(PORT_C_PIN_4); break;
        case PIN_A5: port_c_set_high(PORT_C_PIN_5); break;
    }
}

enum pin_state pin_digital_read(const enum pin pin) {
    switch (pin) {
        case PIN_0:  return (enum pin_state) port_d_get_pin(PORT_D_PIN_0);
        case PIN_1:  return (enum pin_state) port_d_get_pin(PORT_D_PIN_1);
        case PIN_2:  return (enum pin_state) port_d_get_pin(PORT_D_PIN_2);
        case PIN_3:  return (enum pin_state) port_d_get_pin(PORT_D_PIN_3);
        case PIN_4:  return (enum pin_state) port_d_get_pin(PORT_D_PIN_4);
        case PIN_5:  return (enum pin_state) port_d_get_pin(PORT_D_PIN_5);
        case PIN_6:  return (enum pin_state) port_d_get_pin(PORT_D_PIN_6);
        case PIN_7:  return (enum pin_state) port_d_get_pin(PORT_D_PIN_6);

        case PIN_8:  return (enum pin_state) port_b_get_pin(PORT_B_PIN_0);
        case PIN_9:  return (enum pin_state) port_b_get_pin(PORT_B_PIN_1);
        case PIN_10: return (enum pin_state) port_b_get_pin(PORT_B_PIN_2);
        case PIN_11: return (enum pin_state) port_b_get_pin(PORT_B_PIN_3);
        case PIN_12: return (enum pin_state) port_b_get_pin(PORT_B_PIN_4);
        case PIN_13: return (enum pin_state) port_b_get_pin(PORT_B_PIN_5);

        case PIN_A0: return (enum pin_state) port_c_get_pin(PORT_C_PIN_0);
        case PIN_A1: return (enum pin_state) port_c_get_pin(PORT_C_PIN_1);
        case PIN_A2: return (enum pin_state) port_c_get_pin(PORT_C_PIN_2);
        case PIN_A3: return (enum pin_state) port_c_get_pin(PORT_C_PIN_3);
        case PIN_A4: return (enum pin_state) port_c_get_pin(PORT_C_PIN_4);
        case PIN_A5: return (enum pin_state) port_c_get_pin(PORT_C_PIN_5);

        default: return -1;
    }
}

static enum adc_input pin_to_adc_input(const enum pin pin) {
    switch (pin) {
        case PIN_A0: return ADC_INPUT_0;
        case PIN_A1: return ADC_INPUT_1;
        case PIN_A2: return ADC_INPUT_2;
        case PIN_A3: return ADC_INPUT_3;
        case PIN_A4: return ADC_INPUT_4;
        case PIN_A5: return ADC_INPUT_5;
        default: return -1;
    }
}

uint16_t pin_analog_read(const enum pin pin) {
    enum adc_input input = pin_to_adc_input(pin);
    adc_set_input(input);
    adc_start_conversion();
    adc_wait_conversion();
    return adc_read_all() & 0x3FF;
}
