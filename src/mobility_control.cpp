#include <iostream>
#include <robot_instr.h>
#include <robot_link.h>
#include <robot_delay.h>
#include "robot_functions.hpp"
#include "mobility_control.hpp"

using namespace std;

void mobility_control::forward() {
    rlink->command(MOTOR_1_GO, speed);
    rlink->command(MOTOR_2_GO, speed);
}

void mobility_control::stop() {
    rlink->command(MOTOR_1_GO, 0);
    rlink->command(MOTOR_2_GO, 0);
}

void mobility_control::move_till_cross() {
    lf->line_following_output(rlink->request(READ_INPUT_7));
    while (!(lf->sensor_readings[0] && lf->sensor_readings[1])) {
        // Unless both front sensors detect white, repeat doing this
        if ((!lf->sensor_readings[0]) && (!lf->sensor_readings[1])) {
            // Both front sensors are black
            // rlink->command(BOTH_MOTORS_GO_SAME, speed);
            // TODO: failure recovery
        }

        else if ((!lf->sensor_readings[0]) && (lf->sensor_readings[1])) {
            // Left motor is black and right motor is white
            // Steer right
            // rlink->command(BOTH_MOTORS_GO_OPPOSITE, slow_speed);
            steer('R');
        }

        else if ((lf->sensor_readings[0]) && (!lf->sensor_readings[1])) {
            // Left motor is white and right motor is black
            // Steer left
            // rlink->command(BOTH_MOTORS_GO_OPPOSITE, reversed_sign(slow_speed));
            steer('L');
        }
        lf->line_following_output(rlink->request(READ_INPUT_7));
    }
}

void mobility_control::move_across_cross() {
    lf->line_following_output(rlink->request(READ_INPUT_7));
    while (lf->sensor_readings[0] || lf->sensor_readings[1]) {
        if ((lf->sensor_readings[0]) && (lf->sensor_readings[1])) {
            rlink->command(BOTH_MOTORS_GO_OPPOSITE, speed);
        } else if ((!lf->sensor_readings[0]) && (lf->sensor_readings[1])) {
            // Left motor is black and right motor is white
            // Steer left
            // rlink->command(BOTH_MOTORS_GO_OPPOSITE, slow_speed);
            steer('L');
        }

        else if ((lf->sensor_readings[0]) && (!lf->sensor_readings[1])) {
            // Left motor is white and right motor is black
            // Steer right
            // rlink->command(BOTH_MOTORS_GO_OPPOSITE, reversed_sign(slow_speed));
            steer('R');
        }
        lf->line_following_output(rlink->request(READ_INPUT_7));
    }
}

void mobility_control::forward_with_lf(int cross_to_pass) {
    for (int i = 0; i < cross_to_pass; i++) {
        move_till_cross();
        move_across_cross();
    }
    // move_till_cross();
}

void mobility_control::turn(char direction) {
    if (direction == 'l' || direction == 'L') {
        // Turn left
        rlink->command(BOTH_MOTORS_GO_OPPOSITE, slow_speed);
        delay(turning_ms);
        rlink->command(BOTH_MOTORS_GO_OPPOSITE, 0);
    } else if (direction == 'r' || direction == 'R') {
        // Turn right
        rlink->command(BOTH_MOTORS_GO_OPPOSITE, reversed_sign(slow_speed));
        delay(turning_ms);
        rlink->command(BOTH_MOTORS_GO_OPPOSITE, 0);
    }
}

void mobility_control::steer(char direction) {
    if (direction == 'l' || direction == 'L') {
        // Steer left
        rlink->command(BOTH_MOTORS_GO_OPPOSITE, slow_speed);
    } else if (direction == 'r' || direction == 'R') {
        // Steer right
        rlink->command(BOTH_MOTORS_GO_OPPOSITE, reversed_sign(slow_speed));
    }
}

// TODO: correct the directions, e.g. BOTH_MOTOR_GO_WHICH_WAY

void mobility_control::demo_start_and_align_ball(int ball_num) {
    forward_with_lf(ball_num);  // TODO: Adapt to the playground
    turn('R');
    forward();
    delay(1000); // TODO: calibrate the time
    stop();
}