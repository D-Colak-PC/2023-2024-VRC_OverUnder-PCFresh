#include "main.h"
#include "okapi/api.hpp"

#pragma

/**
 * Motor Groups:
 * ------------------
 * 13 (reversed) + 16 = Catapult
 * 17 (normal) + 19 (normal) = Right Drive
 * 18 (reversed) + 20 (reversed) = Left Drive
 * 
 * Motor Ports
 * -------------------------------------------------
 * 1   |
 * 2   | Intake Motor (R1 to start, R2 to stop)
 * 3   | 
 * 4   |
 * 5   | 
 * 6   |
 * 7   |
 * 8   |
 * 9   |
 * 10  |
 * 11  |
 * 12  | Internal Gyroscope
 * 13  | Left Catapult Motor (21432AG, reversed)
 * 14  | 
 * 15  |
 * 16  | Right Catapult Motor (21134AG, normal)
 * 17  | Back Right Drive Motor (normal)
 * 18  | Back Left Drive Motor (reversed)
 * 19  | Front Right Drive Motor (normal)
 * 20  | Front Left Drive Motor (reversed)
 * 21  | Radio
 * 
 * 
 * Sensor Ports
 * ---------------------------------------------------
 * A   |
 * B   |
 * C   |
 * D   |
 * E   |
 * F   |
 * G   |
 * H   | Back Bumper
*/


// drivetrain ports
const int FRONT_RIGHT_DRIVE_PORT = 19;
const int FRONT_LEFT_DRIVE_PORT = 20;
const int BACK_RIGHT_DRIVE_PORT = 17;
const int BACK_LEFT_DRIVE_PORT = 18;

// catapult ports
const int RIGHT_CATAPULT_PORT = 16;
const int LEFT_CATAPULT_PORT = 13;

// intake port
const int INTAKE_PORT = 2;

// sensor ports
const char BACK_BUMPER_PORT = 'h';

// motor declerations
extern pros::MotorGroup left_mg;
extern pros::MotorGroup right_mg;
extern pros::MotorGroup catapult_mg;
extern pros::Motor intake;

// sensor declerations
extern pros::ADIDigitalIn back_bump_sensor;

// controller declerations
extern pros::Controller controller;

// other declerations
extern okapi::ChassisControllerPID chassis;
extern okapi::ADIGyro gyro;



/**
 * This file contains the motor definitions for the robot.
 * 
 */