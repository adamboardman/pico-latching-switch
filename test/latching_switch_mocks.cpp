/*
 * Copyright (c) 2021, Adam Boardman
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "latching_switch_mocks.h"

Mcp23017::Mcp23017(i2c_inst_t *i2c, uint8_t _address) {

}

void Mcp23017::set_bit(int &value, int bit, bool set) {
	if (bit >= 0 && bit <= 15) {
		if (set) {
			value |= (1 << bit);
		} else {
			value &= ~(1 << bit);
		}
	}
}

bool Mcp23017::is_bit_set(int value, int bit) {
	if (bit >= 0 && bit <= 15) {
		return (bool) (0x1 & (value >> bit));
	}
	return false;
}

bool Mcp23017::get_input_pin_value(int pin) const {
	return is_bit_set(last_input, pin);
}

void Mcp23017::set_output_bit_for_pin(int pin, bool set) {
	set_bit(output, pin, set);
}

void Mcp23017::flush_output() {

}

void Mcp23017::set_input_pin_value(int pin, bool set) {
	set_bit(last_input, pin, set);
}

bool Mcp23017::get_output_pin_value(int pin) const {
	return is_bit_set(output, pin);
}
