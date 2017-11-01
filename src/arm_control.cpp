#include <iostream>
#include <cstdlib>  // For exit()
using namespace std;
#include <robot_instr.h>
#include <robot_link.h>
#include <robot_delay.h>
#include "arm_control.hpp"
#include "robot_functions.hpp"

arm_control::arm_control(robot_link* rl) {
        rlink = rl;
	rot_speed = 80;
}

void arm_control::extend() {
	// Set bit 0 to 0
	rlink->command(WRITE_PORT_1, 0b11111110 & rlink->request(READ_PORT_1));
	cout << "Extend\n";
}

void arm_control::contract() {
	// Set bit 0 to 1
	rlink->command(WRITE_PORT_1, 0b00000001 | rlink->request(READ_PORT_1));
	cout << "Contract\n";
}

void arm_control::grab() {
	// Set bit 1 to 0
	rlink->command(WRITE_PORT_1, 0b11111101 & rlink->request(READ_PORT_1));
	cout << "Grab\n";
}

void arm_control::release() {
	// Set bit 1 to 1
	rlink->command(WRITE_PORT_1, 0b00000010 | rlink->request(READ_PORT_1));
	cout << "Release\n";
}

void arm_control::right(int ms) {
	rlink->command(MOTOR_3_GO, rot_speed);
	delay(ms);
	rlink->command(MOTOR_3_GO, 0);
}

void arm_control::left(int ms) {
	rlink->command(MOTOR_3_GO, reversed_sign(rot_speed));
	delay(ms);
	rlink->command(MOTOR_3_GO, 0);
}
