#include "main.h"
#include "globals.h"
#include "okapi/api.hpp"


// motors & motor groups
pros::Motor back_left_drive(BACK_LEFT_DRIVE_PORT, true); // Creates back left drive motor object
pros::Motor back_right_drive(BACK_RIGHT_DRIVE_PORT); // Creates back right drive motor object
pros::Motor front_left_drive(FRONT_LEFT_DRIVE_PORT, true); // Creates front left drive motor object
pros::Motor front_right_drive(FRONT_RIGHT_DRIVE_PORT); // Creates front right drive motor object
pros::MotorGroup left_mg({back_left_drive, front_left_drive}); // Creates left drive motor group with reversed ports 18 & 20
pros::MotorGroup right_mg({back_right_drive, front_right_drive}); // Creates right drive motor group with normal ports 17 & 19
pros::MotorGroup catapult_mg({-LEFT_CATAPULT_PORT, RIGHT_CATAPULT_PORT}); // Creates catapult motor group with reversed port 13 & normal port 16
pros::ADIDigitalIn back_bumper(BACK_BUMPER_PORT); // Creates back bumper sensor object
pros::Motor intake(INTAKE_PORT); // Creates intake motor object

// controller
pros::Controller controller(pros::E_CONTROLLER_MASTER); // Creates controller object for master controller

// sensors
okapi::ADIGyro gyro(1, 1.0); // Creates gyro object on port 1 with a multiplier of 1.0
pros::ADIDigitalIn back_bump_sensor(BACK_BUMPER_PORT); // Creates back bumper sensor object


// LemLib functions
lemlib:: Drivetrain_t drivetrain {
    &left_mg, // left drive train
    &right_mg, // right drive train
    TRACK_WIDTH,    
    WHEEL_DIAMETER,
    WHEEL_RPM
};
/* 
// forward/backward PID
lemlib::ChassisController_t lateralController {
    8, // kP
    30, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    5 // slew rate
};
 
// turning PID
lemlib::ChassisController_t angularController {
    4, // kP
    40, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    0 // slew rate
};
 */

