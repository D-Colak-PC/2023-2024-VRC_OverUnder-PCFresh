#include "main.h"
#include "devices.h"

/*
██████╗  ██████╗  ██╗██╗  ██╗██╗  ██╗██████╗ 
╚════██╗██╔═████╗███║██║  ██║██║  ██║██╔══██╗
 █████╔╝██║██╔██║╚██║███████║███████║██████╔╝
██╔═══╝ ████╔╝██║ ██║╚════██║╚════██║██╔══██╗
███████╗╚██████╔╝ ██║     ██║     ██║██████╔╝
╚══════╝ ╚═════╝  ╚═╝     ╚═╝     ╚═╝╚═════╝ 
*/

// motors & motor groups
pros::Motor back_left_drive(BACK_LEFT_DRIVE_PORT, pros::E_MOTOR_GEARSET_18, true); // Creates back left drive motor object
pros::Motor back_right_drive(BACK_RIGHT_DRIVE_PORT, pros::E_MOTOR_GEARSET_18, false); // Creates back right drive motor object
pros::Motor front_left_drive(FRONT_LEFT_DRIVE_PORT, pros::E_MOTOR_GEARSET_18, true); // Creates front left drive motor object
pros::Motor front_right_drive(FRONT_RIGHT_DRIVE_PORT, pros::E_MOTOR_GEARSET_18, false); // Creates front right drive motor object
pros::MotorGroup left_drive_mg({back_left_drive, front_left_drive}); // Creates left drive motor group with reversed ports 18 & 20
pros::MotorGroup right_drive_mg({back_right_drive, front_right_drive}); // Creates right drive motor group with normal ports 17 & 19

pros::Motor left_catapult(LEFT_CATAPULT_PORT,  pros::E_MOTOR_GEARSET_18, false); // Creates left catapult motor object
pros::Motor right_catapult(RIGHT_CATAPULT_PORT, pros::E_MOTOR_GEARSET_18, false); // Creates right catapult motor object
pros::MotorGroup catapult_mg({left_catapult, right_catapult}); // Creates catapult motor group with reversed port 13 & normal port 16

pros::Motor left_wing(LEFT_WING_PORT, pros::E_MOTOR_GEARSET_36, false); // Creates left wing motor object
pros::Motor right_wing(RIGHT_WING_PORT, pros::E_MOTOR_GEARSET_36, true); // Creates right wing motor object
pros::MotorGroup wing_mg({left_wing, right_wing}); // Creates wing motor group with reversed port 14 & normal port 15

pros::Motor intake(INTAKE_PORT, pros::E_MOTOR_GEARSET_06, true); // Creates intake motor object

// sensors
pros::Imu imu(IMU_PORT); // Creates imu object
pros::Distance distance_sensor(DISTANCE_PORT); // Creates back bumper sensor object

// controller
pros::Controller controller(pros::E_CONTROLLER_MASTER); // Creates controller object for master controller
