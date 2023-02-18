#include "main.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "config.cpp"

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

  // These are already defaulted to these buttons, but you can change the
  // left/right curve buttons here! chassis.set_left_curve_buttons
  // (pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT); // If
  // using tank, only the left side is used.
  // chassis.set_right_curve_buttons(pros::E_CONTROLLER_DIGITAL_Y,
  // pros::E_CONTROLLER_DIGITAL_A);

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
