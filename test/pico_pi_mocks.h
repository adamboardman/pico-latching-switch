/*
 * Copyright (c) 2021, Adam Boardman
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef TESTS_PICO_PI_MOCKS_H
#define TESTS_PICO_PI_MOCKS_H

#include <cstdint>
#include <vector>

typedef struct {
} i2c_hw_t;

struct i2c_inst {
	i2c_hw_t *hw;
	bool restart_on_next;
};

typedef struct i2c_inst i2c_inst_t;

typedef	unsigned int uint;

enum {
	PICO_OK = 0,
	PICO_ERROR_NONE = 0,
	PICO_ERROR_TIMEOUT = -1,
	PICO_ERROR_GENERIC = -2,
	PICO_ERROR_NO_DATA = -3,
};

typedef int32_t alarm_id_t;

typedef int64_t (*alarm_callback_t)(alarm_id_t id, void *user_data);

class alarm_callback {
public:
	alarm_callback(alarm_id_t id, alarm_callback_t callback1, void *userData);

	bool operator==(const alarm_callback &rhs) const;

	bool operator!=(const alarm_callback &rhs) const;

	alarm_id_t id;
	alarm_callback_t callback;
	void *user_data;
};

alarm_id_t add_alarm_in_ms(uint32_t ms, alarm_callback_t callback, void *user_data, bool fire_if_past);

void action_alarms();

extern std::vector<alarm_callback> mock_alarms;

#endif //TESTS_PICO_PI_MOCKS_H
