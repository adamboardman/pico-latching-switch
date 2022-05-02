/*
 * Copyright (c) 2021, Adam Boardman
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <catch2/catch_test_macros.hpp>
#include <cstdarg>

#include "latching_switch.h"
#include "pico_pi_mocks.h"

TEST_CASE("Switch On - On/Off pins correct", "[light_switch]") {
	Mcp23017 mcp_in(nullptr, 0x1);
	Mcp23017 mcp_out(nullptr, 0x2);

	Latching_switch a_switch(mcp_out,0,1,mcp_in,0);
	REQUIRE(a_switch.get_current_state() == false);
	a_switch.invert_switch();
	REQUIRE(mcp_out.get_output_pin_value(0) == false);
	REQUIRE(mcp_out.get_output_pin_value(1) == true);
	mcp_in.set_input_pin_value(0, true); //Pretend light switch did switch
	action_alarms();
	REQUIRE(mcp_out.get_output_pin_value(0) == false);
	REQUIRE(mcp_out.get_output_pin_value(1) == false);
	REQUIRE(a_switch.get_current_state() == true);
}

TEST_CASE("Switch Light On - On/Off pins inverted", "[light_switch]") {
	Mcp23017 mcp_in(nullptr, 0x1);
	Mcp23017 mcp_out(nullptr, 0x2);

	Latching_switch a_switch(mcp_out,0,1,mcp_in,0);
	REQUIRE(a_switch.get_off_pin() == 0);
	REQUIRE(a_switch.get_on_pin() == 1);
	REQUIRE(a_switch.get_current_state() == false);
	a_switch.invert_switch();
	REQUIRE(mcp_out.get_output_pin_value(0) == false);
	REQUIRE(mcp_out.get_output_pin_value(1) == true);
	action_alarms();
	REQUIRE(a_switch.get_off_pin() == 1);
	REQUIRE(a_switch.get_on_pin() == 0);
	REQUIRE(mcp_out.get_output_pin_value(0) == true);
	REQUIRE(mcp_out.get_output_pin_value(1) == false);
	mcp_in.set_input_pin_value(0, true); //Pretend light switch only switched after pin swapping
	action_alarms();
	REQUIRE(mcp_out.get_output_pin_value(0) == false);
	REQUIRE(mcp_out.get_output_pin_value(1) == false);
	REQUIRE(a_switch.get_current_state() == true);
}
