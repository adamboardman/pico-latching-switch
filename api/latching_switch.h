/*
 * Copyright (c) 2021, Adam Boardman
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef LATCHING_SWITCH_H
#define LATCHING_SWITCH_H

#include <cstdio>
#ifdef MOCK_PICO_PI
#include "test/latching_switch_mocks.h"
#else
#include <output_switch.h>
#include "input_detect.h"
#endif

#define DEBUG_LATCHING_SWITCH
#ifdef  DEBUG_LATCHING_SWITCH
#define latching_switch_debug(fmt, arg...) \
	do {                                   \
        printf(fmt, ##arg);                \
	} while (0)
#else
#define latching_switch_debug(...) do { } while (false)
#endif

class Latching_switch {
public:
	Latching_switch(Output_switch &outputSwitch, Input_detect &inputDetect);

	void switch_to_state(bool desired_state);

	[[nodiscard]] bool get_current_state() const;

	void confirm_or_retry_switch();

private:
	Output_switch &_output_switch;
	Input_detect &_input_detect;
	bool _switch_inverted{};
	bool _last_desired_state{};
	bool _alarm_set{};
};

#endif //LATCHING_SWITCH_H
