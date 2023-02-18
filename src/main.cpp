#include "main.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"

// Chassis constructor
Drive chassis(
    // Left Chassis Ports (negative port will reverse it!)
    //   the first port is the sensored port (when trackers are not used!)
    {-3, -5, -13}

    // Right Chassis Ports (negative port will reverse it!)
    //   the first port is the sensored port (when trackers are not used!)
    ,
    {8, 10, 19}

    // IMU Port
    ,
    9

    // Wheel Diameter (Remember, 4" wheels are actually 4.125!)
    //    (or tracking wheel diameter)
    ,
    3.25

    // Cartridge RPM
    //   (or tick per rotation if using tracking wheels)
    ,
    600

    // External Gear Ratio (MUST BE DECIMAL)
    //    (or gear ratio of tracking wheel)
    // eg. if your drive is 84:36 where the 36t is powered, your RATIO would
    // be 2.333. eg. if your drive is 36:60 where the 60t is powered, your RATIO
    // would be 0.6.
    ,
    .6
);

pros::Motor catapult(15, true);
//initializes catapult

pros::Motor intake(4);
//initializes intake

pros::ADIButton limitSwitch('F');
pros::ADIDigitalOut endgamePiston('C');

bool catapultState = true;

pros::Controller joystick(CONTROLLER_MASTER);

const int INTAKE_SPEED = 600;
const int CATAPULT_SPEED = 100;

void initialize() {

  pros::delay(
      500); // Stop the user from doing anything while legacy ports configure.

  // Configure your chassis controls
  chassis.toggle_modify_curve_with_controller(
      true); // Enables modifying the controller curve with buttons on the
             // joysticks
  chassis.set_active_brake(0.1); // Sets the active brake kP. We recommend 0.1.
  chassis.set_curve_default(
      0, 0); // Defaults for curve. If using tank, only the first parameter is
             // used. (Comment this line out if you have an SD card!)
  default_constants(); // Set the drive to your own constants from autons.cpp!
  exit_condition_defaults(); // Set the exit conditions to your own constants
                             // from autons.cpp!

  // Autonomous Selector using LLEMU

  
  ez::as::auton_selector.add_autons({
      Auton("Example Drive\n\nDrive forward and come back.", drive_example),
      Auton("Example Turn\n\nTurn 3 times.", turn_example),
      Auton("Drive and Turn\n\nDrive forward, turn, come back. ",
            drive_and_turn),
      Auton("Drive and Turn\n\nSlow down during drive.",
            wait_until_change_speed),
      Auton("Swing Example\n\nSwing, drive, swing.", swing_example),
      Auton("Combine all 3 movements", combining_movements),
      Auton("Interference\n\nAfter driving forward, robot performs differently "
            "if interfered or not.",
            interfered_example),
  });
  

  // Initialize chassis and auton selector
  //chassis.initialize();
  ez::as::initialize();
  chassis.set_drive_brake(MOTOR_BRAKE_COAST);
}


void autonomous() {
  chassis.reset_pid_targets();               // Resets PID targets to 0
  chassis.reset_gyro();                      // Reset gyro position to 0
  chassis.reset_drive_sensor();              // Reset drive sensors to 0
  chassis.set_drive_brake(MOTOR_BRAKE_HOLD); // Set motors to hold.  This helps
                                             // autonomous consistency.

  ez::as::auton_selector
      .call_selected_auton(); // Calls selected auton from autonomous selector.
}

void opcontrol() {
  // This is preference to what you like to drive on.

  while (true) {

    // chassis.tank();                     // Tank control
    chassis.arcade_standard(ez::SPLIT); // Standard split arcade
    // chassis.arcade_standard(ez::SINGLE); // Standard single arcade
    // chassis.arcade_flipped(ez::SPLIT); // Flipped split arcade
    // chassis.arcade_flipped(ez::SINGLE); // Flipped single arcade

    // . . .
    // Put more user control code here!
    // . . .

    if (limitSwitch.get_value()) {
      if (joystick.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
        intake.move_velocity(INTAKE_SPEED);
      } else if (joystick.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
        intake.move_velocity(-INTAKE_SPEED);
      } else {
        intake.move_velocity(0);
      }
    } else if (!limitSwitch.get_value()) {
      if (joystick.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        intake.move_velocity(INTAKE_SPEED);
      } else if (joystick.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        intake.move_velocity(-INTAKE_SPEED);
      } else {
        intake.move_velocity(0);
      }
    }

    if (catapultState) {
      if (joystick.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
        catapult.move_velocity(CATAPULT_SPEED);
      } else if (limitSwitch.get_value()) {
        catapult.move_velocity(0);
      } else {
        catapult.move_velocity(CATAPULT_SPEED);
      }
    } else {

      catapult.move_velocity(0);
    }
     

    // up arrow toggle catapultState
    if (joystick.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
      catapultState = !catapultState;
      pros::delay(200);
    }   

    if(joystick.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
      endgamePiston.set_value(true);
    } else {
      endgamePiston.set_value(false);
    }

    

    pros::delay(ez::util::DELAY_TIME); // This is used for timer calculations!
                                       // Keep this ez::util::DELAY_TIME
  }
}
