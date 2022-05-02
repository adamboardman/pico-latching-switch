/*
 * Copyright (c) 2021, Adam Boardman
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "pico/time.h" //NOLINT
#include "latching_switch.h"

int64_t latching_switch_check_callback(alarm_id_t id, void *the_switch) {
	latching_switch_debug("Latching switch check timer %d fired!\n", (int) id);
	auto latching_switch = static_cast<Latching_switch *>(the_switch);
	latching_switch->confirm_or_retry_switch();
	return 0;
}

Latching_switch::Latching_switch(Output_switch &outputSwitch, Input_detect &inputDetect)
	: _output_switch(outputSwitch), _input_detect(inputDetect) {

}

bool Latching_switch::get_current_state() const {
	return _input_detect.get_current_state();
}

void Latching_switch::switch_to_state(bool desired_state) {
	latching_switch_debug("switch_to_state - from stated: %d, to state: %d\n", get_current_state(), desired_state);
	if (get_current_state() != desired_state) {
		if (_switch_inverted) {
			desired_state = !desired_state;
		}
		_output_switch.set_output_state(desired_state);
		_last_desired_state = desired_state;
		if (!_alarm_set) {
			_alarm_set = true;
			add_alarm_in_ms(1000, latching_switch_check_callback, this, true);
		}
	}
}

void Latching_switch::confirm_or_retry_switch() {
	latching_switch_debug("confirm_or_retry_switch - desired:%d, current:%d\n", _last_desired_state, get_current_state());
	_alarm_set = false;
	if (_last_desired_state != get_current_state()) {
		_switch_inverted = !_switch_inverted;
		switch_to_state(_last_desired_state);
	} else {
		_output_switch.desired_state_achieved();
	}
}
