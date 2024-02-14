#include "main.h"
#include "devices.h"
#include "lemlib/api.hpp"
#include "chassis.h"

/*
██████╗  ██████╗  ██╗██╗  ██╗██╗  ██╗██████╗ 
╚════██╗██╔═████╗███║██║  ██║██║  ██║██╔══██╗
 █████╔╝██║██╔██║╚██║███████║███████║██████╔╝
██╔═══╝ ████╔╝██║ ██║╚════██║╚════██║██╔══██╗
███████╗╚██████╔╝ ██║     ██║     ██║██████╔╝
╚══════╝ ╚═════╝  ╚═╝     ╚═╝     ╚═╝╚═════╝ 
*/

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */

void printPosition() {
    // loop forever
    while (true) {
        lemlib::Pose pose = chassis.getPose(); // get the current position of the robot
        pros::lcd::print(0, "x: %f", pose.x); // print the x position
        pros::lcd::print(1, "y: %f", pose.y); // print the y position
        pros::lcd::print(2, "heading: %f", pose.theta); // print the heading
        pros::lcd::print(3,  "left wing: %f", left_wing.get_position());
        pros::lcd::print(4, "right wing: %f", right_wing.get_position());
        pros::lcd::print(5, "both wings: %f", wing_mg.get_positions());
        pros::delay(10);
    }
}


void setUpMotors() {
    // setting up wings
    wing_mg.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD); // set brake modes
    wing_mg.brake(); // brake wings
    wing_mg.tare_position(); // set wing positions to 0

    // setting up catapult
    catapult_mg.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD); // set brake modes
    catapult_mg.brake(); // brake catapult
    catapult_mg.tare_position(); // set catapult position to 0

    // setting up intake
    intake.set_brake_mode(pros::E_MOTOR_BRAKE_COAST); // set brake modes
    intake.brake(); // brake intake
    intake.tare_position(); // set intake position to 0

    // setting up drive
    left_drive_mg.set_brake_modes(pros::E_MOTOR_BRAKE_COAST); // set brake modes
    right_drive_mg.set_brake_modes(pros::E_MOTOR_BRAKE_COAST); // set brake modes
    left_drive_mg.tare_position(); // set drive positions to 0
    right_drive_mg.tare_position(); // set drive positions to 0

    // setting up imu
    imu.reset(); // reset imu
}


void initialize() {
	pros::lcd::initialize();

	pros::lcd::set_text(1, "VEX > FTC");

    pros::lcd::set_text(2, "Initializing Motors");
    setUpMotors();
    pros::delay(500);
    pros::lcd::set_text(2, "EZ Dubs (Motors Initialized)");

	pros::lcd::set_text(3, "Initializing LemLib Chassis");
	chassis.calibrate();
    chassis.setPose({0, 0, 0}); // only for testing purposes
	pros::lcd::set_text(3, "EZ Dubs (LemLib Chassis Initialized)");

    pros::Task screenTask(printPosition);


}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit. 
 */


void disabled() {
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
}

