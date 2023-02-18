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