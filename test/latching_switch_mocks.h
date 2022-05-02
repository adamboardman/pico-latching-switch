/*
 * Copyright (c) 2021, Adam Boardman
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef TESTS_LIGHT_SWITCH_MOCKS_H
#define TESTS_LIGHT_SWITCH_MOCKS_H

#include "pico_pi_mocks.h"

class Mcp23017 {
public:
	Mcp23017(i2c_inst_t *i2c,  uint8_t _address);

	void set_input_pin_value(int pin, bool set);

	[[nodiscard]] bool get_output_pin_value(int pin) const;

public:
	[[nodiscard]] bool get_input_pin_value(int pin) const;

	void set_output_bit_for_pin(int pin, bool set);

	void flush_output();

private:
	int output{};
	int last_input{};

	static void set_bit(int &value, int bit, bool set);

	static bool is_bit_set(int value, int bit) ;
};



#endif //TESTS_LIGHT_SWITCH_MOCKS_H
