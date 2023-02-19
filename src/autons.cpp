#include "main.h"
#include <cmath>
#include <type_traits>
#include <vector>

/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////


const int DRIVE_SPEED = 110; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
const int TURN_SPEED  = 90;
const int SWING_SPEED = 90;



///
// Constants
///

// It's best practice to tune constants when the robot is empty and with heavier game objects, or with lifts up vs down.
// If the objects are light or the cog doesn't change much, then there isn't a concern here.

void default_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void one_mogo_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void two_mogo_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void exit_condition_defaults() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}

void modified_exit_condition() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}



///
// Drive Example
///
void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater then the slew distance + a few inches


  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_drive_pid(-12, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-12, DRIVE_SPEED);
  chassis.wait_drive();
}



///
// Turn Example
///
void turn_example() {
  // The first parameter is target degrees
  // The second parameter is max speed the robot will drive at


  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();
}



///
// Combining Turn + Drive
///
void drive_and_turn() {
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_drive();
}



///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  // wait_until will wait until the robot gets to a desired position


  // When the robot gets to 6 inches, the robot will travel the remaining distance at a max speed of 40
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_until(6);
  chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  // When the robot gets to -6 inches, the robot will travel the remaining distance at a max speed of 40
  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_until(-6);
  chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  chassis.wait_drive();
}



///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is target degrees
  // The third parameter is speed of the moving side of the drive


  chassis.set_swing_pid(ez::LEFT_SWING, 45, SWING_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_until(12);

  chassis.set_swing_pid(ez::RIGHT_SWING, 0, SWING_SPEED);
  chassis.wait_drive();
}



///
// Auto that tests everything
///
void combining_movements() {
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_swing_pid(ez::RIGHT_SWING, -45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_drive();
}



///
// Interference example
///
void tug (int attempts) {
  for (int i=0; i<attempts-1; i++) {
    // Attempt to drive backwards
    printf("i - %i", i);
    chassis.set_drive_pid(-12, 127);
    chassis.wait_drive();

    // If failsafed...
    if (chassis.interfered) {
      chassis.reset_drive_sensor();
      chassis.set_drive_pid(-2, 20);
      pros::delay(1000);
    }
    // If robot successfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, robot will drive forward and turn 90 degrees. 
// If interfered, robot will drive forward and then attempt to drive backwards. 
void interfered_example() {
 chassis.set_drive_pid(24, DRIVE_SPEED, true);
 chassis.wait_drive();

 if (chassis.interfered) {
   tug(3);
   return;
 }

 chassis.set_turn_pid(90, TURN_SPEED);
 chassis.wait_drive();
}



// . . .
// Make your own autonomous functions here!
// . . .

float initX = 0, initY = 0;
float targetX = 4, targetY = 2.5;
int currentHeading = 135;
int targetHeading = 225;
float tolerance = 0.1;
int Kp_lin = 20;
float Kp_turn = 1.7;

//this determines how long (how many frames) the animation will run. 400 frames takes around 30 seconds to compute.
int numOfFrames = 120;
int dt = 50;   // ms, interval between frames

float currentPos [2] = {initX, initY};
float targetPos [2] = {targetX, targetY};

float find_min_angle (float targetHeading, float currentHeading) {
  float turnAngle = targetHeading - currentHeading;
  if (turnAngle > 180 || turnAngle < -180) {
    turnAngle = -1 * turnAngle/std::abs(turnAngle) * (360 - abs(turnAngle));
  }
  return turnAngle;
}

vector<float> move_to_pose_step (vector<float> currentPos, float currentHeading, vector<float>targetPos, float targetHeading, float Kp_lin, float Kp_turn) {
  int r = 1;
  int turnMax = 100; 
  int linMax = 70;
  float currentX = currentPos[0], currentY = currentPos[1];
  float targetX = targetPos[0], targetY = targetPos[1];
  
  // the angle between the line connecting the robot's current position to the target point and the x axis
  float absTargetAngle = std::atan2 ((targetY-currentY), (targetX-currentX)) *180/3.14;

  // keep absTargetAngle between 0 and 360
  if (absTargetAngle < 0) {
    absTargetAngle += 360;
  }
    
  // naming convention consistent with the book
  float D = std::sqrt(std::pow((targetX-currentX), 2)  + std::pow((targetY-currentY), 2));
  float alpha = find_min_angle(absTargetAngle, targetHeading);
  float errorTerm1 = find_min_angle(absTargetAngle, currentHeading);

  float beta = std::atan(r/D) *180/3.14;

  if (alpha < 0) {
    beta *= -1;
  }

  float turnError;
  if (std::abs(alpha) < std::abs(beta))
    turnError = errorTerm1 + alpha;
  else
    turnError = errorTerm1 + beta;

  // apply proportional control to find linear and turn velocities
  float linearVel = Kp_lin * D;
  float turnVel = Kp_turn * turnError;

  // when close enough to the target
  bool closeToTarget = false;

  if (D < tolerance)
    closeToTarget = true;

  if (closeToTarget) {
    //apply equation 3.13 from Wheeled Mobile Robotics: From Fundamentals Towards Autonomous Systems
    linearVel =  Kp_lin * D * std::cos(turnError * 3.14/180) / std::abs(std::cos(turnError * 3.14/180));  //in pct
    // when close enough to the target, overwrite the turn error output from intermediate direction calculations to prevent oscillations
    turnError = find_min_angle(targetHeading, currentHeading);
    turnVel = Kp_turn * std::atan(std::tan(turnError * 3.14/180)) *180/3.14;
  }

  /*
  // cap the velocities
  if (np.abs(linearVel) > linMax)
    linearVel = np.sign(linearVel) * linMax
  if (np.abs(turnVel) > turnMax)
    turnVel = np.sign(turnVel) * turnMax
    */

  // prioritize turning
  if (linearVel > (100 - std::abs(turnVel)))
    linearVel = 100 - std::abs(turnVel);
  // don't prioritize turning
  if (linearVel > 100)
     linearVel = 100;

  vector<float> b;
  b.push_back(linearVel);
  b.push_back(turnVel);
  return b;
}