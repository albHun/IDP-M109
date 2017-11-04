#ifndef MOBILITY_CONTROL_HPP
#define MOBILITY_CONTROL_HPP

#include <iostream>
#include <cstdlib>  // For exit()
using namespace std;
#include <robot_instr.h>
#include <robot_link.h>
#include <robot_delay.h>
#include "line_follower.hpp"

class mobility_control {
    robot_link* rlink;
    line_follower* lf;
    int turning_ms;
    int walking_ms;
    int turn_180_ms;
    int speed;
    int slow_speed;
    int turning_speed;

   public:
    mobility_control(robot_link* rl, line_follower* line_f);
    void forward();   // move forward
    void backward();  // move backward
    void stop();
    void turn(char direction);                  // 'l' 'L' for left, 'r' 'R' for right
    void turn_to_left_sensors(char direction);  // align the left sensors
    void steer(char direction);                 // 'l' 'L' for left, 'r' 'R' for right
    void turn_180();                            // make a 180 rotation anticlockwise
    void turn_180_clockwise();                  // make a 180 rotation clockwise
    void forward_with_lf(int cross_to_pass);
    void forward_with_left_sensors(int cross_to_pass);
    //This function will move the robot forward until it has passed pass_cross crosses and meets the next cross
    void move_till_cross();
    void forward_for_time_ms(int ms);
    void left_sandwich();
    friend int reversed_sign(const int& motor_speed);
};

#endif  // MOBILITY_CONTROL_HPP
