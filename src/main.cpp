#include "main.h"

const int INTAKE_PORT = 2;
const int RIGHT_CATAPULT_PORT = 16;
const int LEFT_CATAPULT_PORT = 13;
const int FRONT_RIGHT_DRIVE_PORT = 19;
const int FRONT_LEFT_DRIVE_PORT = 20;
const int BACK_RIGHT_DRIVE_PORT = 17;
const int BACK_LEFT_DRIVE_PORT = 18;
const char BACK_BUMPER_PORT = 'h';

const int CONTROLLER_UPDATE_FPS = 10; // ms between controller updates

const std::string DRIVE_TYPE = "tank"; // "arcade" or "tank"


pros::MotorGroup left_mg({-BACK_LEFT_DRIVE_PORT, -FRONT_LEFT_DRIVE_PORT}); // Creates left drive motor group with reversed ports 18 & 20
pros::MotorGroup right_mg({BACK_RIGHT_DRIVE_PORT, FRONT_RIGHT_DRIVE_PORT}); // Creates right drive motor group with normal ports 17 & 19
pros::MotorGroup catapult_mg({-LEFT_CATAPULT_PORT, RIGHT_CATAPULT_PORT}); // Creates catapult motor group with reversed port 13 & normal port 16
pros::adi::DigitalIn back_bumper(BACK_BUMPER_PORT); // Creates back bumper sensor object

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
/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello PROS User!");

	pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER); // Creates controller object for master controller	


	while (true) {
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0); // Prints status of the emulated screen LCDs
						 
		if (DRIVE_TYPE.compare("arcade") == 0) {
			// Arcade control scheme
			int dir = master.get_analog(ANALOG_LEFT_Y); // Gets amount forward/backward from left joystick
			int turn = master.get_analog(ANALOG_RIGHT_X); // Gets the turn left/right from right joystick
			left_mg = dir - turn; // Sets left motor voltage
			right_mg = dir + turn; // Sets right motor voltage
			pros::delay(CONTROLLER_UPDATE_FPS); // Run for set ms then update
		} else {
			// Tank control scheme
			left_mg = master.get_analog(ANALOG_LEFT_Y); // Sets left motor voltage
			right_mg = master.get_analog(ANALOG_RIGHT_Y); // Sets right motor voltage
			pros::delay(CONTROLLER_UPDATE_FPS); // Run for set ms then update
		}
	}
}