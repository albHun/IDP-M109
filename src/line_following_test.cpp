#include <iostream>
#include <cstdlib>  // For exit()
using namespace std;
#include <robot_instr.h>
#include <robot_link.h>
#include <robot_delay.h>
#include "robot_functions.hpp"

#define ROBOT_NUM  7                         // The id number (see below)
// robot_link  rlink;                            // datatype for the robot link
custom_robot_link  rlink;  // Our customized robot_link class

int main() {
	rlink.lf.line_following_output(rlink.request(READ_PORT_7));
	bool* lf_sensors = rlink.lf.sensor_readings;
	if (lf_sensors[0] && lf_sensors[1]) { //both front sensors read black
		rlink.mc.forward();
	}
	else {
		rlink.mc.stop();
	}
	return 0;
}
