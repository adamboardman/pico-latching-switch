/*
 * Copyright (c) 2021, Adam Boardman
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "pico_pi_mocks.h"

#include <algorithm>

std::vector<alarm_callback> mock_alarms;

alarm_id_t add_alarm_in_ms(uint32_t ms, alarm_callback_t callback, void *user_data, bool fire_if_past) {
	alarm_callback mock_alarm(mock_alarms.size(), callback, user_data);
	mock_alarms.push_back(mock_alarm);
	return PICO_ERROR_NONE;
}

void action_alarms() {
	auto alarms_copy(mock_alarms);
	for (auto alarm:alarms_copy) {
		alarm.callback(alarm.id, alarm.user_data);
	}

	if (alarms_copy.size() == mock_alarms.size()) {
		mock_alarms.clear();
	} else {
		while (!alarms_copy.empty()) {
			alarms_copy.erase(alarms_copy.begin());
			mock_alarms.erase(mock_alarms.begin());
		}
	}
}

bool alarm_callback::operator==(const alarm_callback &rhs) const {
	return id == rhs.id &&
		   callback == rhs.callback &&
		   user_data == rhs.user_data;
}

bool alarm_callback::operator!=(const alarm_callback &rhs) const {
	return !(rhs == *this);
}

alarm_callback::alarm_callback(alarm_id_t id, alarm_callback_t callback, void *userData)
:  id(id), callback(callback), user_data(userData) {

}
