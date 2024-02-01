#include "main.h"
#include "motors.h"
#include "okapi/api.hpp"


// motors & motor groups

pros::MotorGroup left_mg({-BACK_LEFT_DRIVE_PORT, -FRONT_LEFT_DRIVE_PORT}); // Creates left drive motor group with reversed ports 18 & 20
pros::MotorGroup right_mg({BACK_RIGHT_DRIVE_PORT, FRONT_RIGHT_DRIVE_PORT}); // Creates right drive motor group with normal ports 17 & 19
pros::MotorGroup catapult_mg({-LEFT_CATAPULT_PORT, RIGHT_CATAPULT_PORT}); // Creates catapult motor group with reversed port 13 & normal port 16
pros::adi::DigitalIn back_bumper(BACK_BUMPER_PORT); // Creates back bumper sensor object
pros::Motor intake(INTAKE_PORT); // Creates intake motor object

// controller
pros::Controller controller(pros::E_CONTROLLER_MASTER); // Creates controller object for master controller

// bumpers
pros::adi::DigitalIn BR_bumper(TRIGGER_BR);
pros::adi::DigitalIn TR_bumper(TRIGGER_TR);
pros::adi::DigitalIn BL_bumper(TRIGGER_BL);
pros::adi::DigitalIn TL_bumper(TRIGGER_TL);

// sensors
okapi::ADIGyro gyro(1, 1.0); // Creates gyro object on port 1 with a multiplier of 1.0
pros::adi::DigitalIn back_bump_sensor(BACK_BUMPER_PORT); // Creates back bumper sensor object

// create robot in okapi
using namespace okapi;

auto chassis = ChassisControllerBuilder()
    .withMotors({-BACK_LEFT_DRIVE_PORT, -FRONT_LEFT_DRIVE_PORT}, {BACK_RIGHT_DRIVE_PORT, FRONT_RIGHT_DRIVE_PORT})
    .withDimensions(AbstractMotor::gearset::green, {{4_in, 11.5_in}, imev5GreenTPR})
    .withGains(
        {0.001, 0, 0.0001}, // Distance controller gains
        {0.001, 0, 0.0001}, // Turn controller gains
        {0.001, 0, 0.0001}  // Angle controller gains (helps drive straight)
    )
    .withOdometry() // use the same scales as the chassis (above)
    .buildOdometry();



