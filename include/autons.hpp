#pragma once

#include "EZ-Template/drive/drive.hpp"
#include <tuple>
#include <vector>

extern Drive chassis;

extern pros::Motor catapult;
//initializes catapult

extern pros::Motor intake;
//initializes intake

extern pros::ADIButton limitSwitch;
extern pros::ADIDigitalOut endgamePiston;

const int INTAKE_SPEED = 600;
const int CATAPULT_SPEED = 100;

void drive_example();
void turn_example();
void drive_and_turn();
void wait_until_change_speed();
void swing_example();
void combining_movements();
void interfered_example();

void default_constants();
void one_mogo_constants();
void two_mogo_constants();
void exit_condition_defaults();
void modified_exit_condition();
void awp();
std::vector<float> move_to_pose_step(std::vector<float> currentPos, float currentHeading, std::vector<float> targetPos, float targetHeading, float Kp_lin, float Kp_turn);