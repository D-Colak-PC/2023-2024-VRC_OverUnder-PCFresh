#include "main.h"

#pragma once

/*
██████╗  ██████╗  ██╗██╗  ██╗██╗  ██╗██████╗ 
╚════██╗██╔═████╗███║██║  ██║██║  ██║██╔══██╗
 █████╔╝██║██╔██║╚██║███████║███████║██████╔╝
██╔═══╝ ████╔╝██║ ██║╚════██║╚════██║██╔══██╗
███████╗╚██████╔╝ ██║     ██║     ██║██████╔╝
╚══════╝ ╚═════╝  ╚═╝     ╚═╝     ╚═╝╚═════╝ 
*/

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
 * 2   | Intake Motor (R1 to start, R2 to stop) [blue]
 * 3   | 
 * 4   |
 * 5   | 
 * 6   | Distance Sensor
 * 7   |
 * 8   |
 * 9   |
 * 10  |
 * 11  |
 * 12  | Internal Gyroscope
 * 13  | Left Catapult Motor (21432AG, reversed) [green]
 * 14  | Left Wing Motor (reversed) [green]
 * 15  | Right Wing Motor (normal) [green]
 * 16  | Right Catapult Motor (21134AG, normal) [green]
 * 17  | Back Right Drive Motor (normal) [green]
 * 18  | Back Left Drive Motor (reversed) [green]
 * 19  | Front Right Drive Motor (normal) [green]
 * 20  | Front Left Drive Motor (reversed) [green]
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

/**
 * Motor Ports
 * Here, we create the motor ports for the robot.
*/
// drivetrain ports
const int BACK_RIGHT_DRIVE_PORT = 17;
const int BACK_LEFT_DRIVE_PORT = 18;
const int FRONT_RIGHT_DRIVE_PORT = 19;
const int FRONT_LEFT_DRIVE_PORT = 20;

// catapult ports
const int LEFT_CATAPULT_PORT = 13;
const int RIGHT_CATAPULT_PORT = 16;

// wing ports
const int LEFT_WING_PORT = 14;
const int RIGHT_WING_PORT = 15;

// intake port
const int INTAKE_PORT = 2;

// sensor ports
const int DISTANCE_PORT = 6;
const int IMU_PORT = 12;

/**
 * Motor declerations
 * Here, we declare the motor objects for the robot.
*/
// drivetrain
extern pros::Motor back_left_drive;
extern pros::Motor back_right_drive;
extern pros::Motor front_left_drive;
extern pros::Motor front_right_drive;

extern pros::MotorGroup left_drive_mg;
extern pros::MotorGroup right_drive_mg;

// catapult
extern pros::Motor left_catapult;
extern pros::Motor right_catapult;
extern pros::MotorGroup catapult_mg;

// wings
extern pros::Motor left_wing;
extern pros::Motor right_wing;
extern pros::MotorGroup wing_mg;

// intake
extern pros::Motor intake;

// sensor declerations
extern pros::Distance distance_sensor;

// controller declerations
extern pros::Controller controller;

// other declerations
extern pros::Imu imu;