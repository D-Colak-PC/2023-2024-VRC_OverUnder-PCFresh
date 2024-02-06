#include "main.h"
#include "globals.h"
#include <math.h>

/*
██████╗  ██████╗  ██╗██╗  ██╗██╗  ██╗██████╗ 
╚════██╗██╔═████╗███║██║  ██║██║  ██║██╔══██╗
 █████╔╝██║██╔██║╚██║███████║███████║██████╔╝
██╔═══╝ ████╔╝██║ ██║╚════██║╚════██║██╔══██╗
███████╗╚██████╔╝ ██║     ██║     ██║██████╔╝
╚══════╝ ╚═════╝  ╚═╝     ╚═╝     ╚═╝╚═════╝ 
*/

const int CONTROLLER_UPDATE_FPS = 10; // ms between controller updates

const std::string DRIVE_TYPE = "tank"; // "arcade" or "tank"
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


void opcontrol() {
	bool shooting = false; // Whether the robot is shooting


	while (true) {
		pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0); // Prints status of the emulated screen LCDs
						 
		if (DRIVE_TYPE.compare("arcade") == 0) {
			// Arcade control scheme
			int dir = controller.get_analog(ANALOG_LEFT_Y); // Gets amount forward/backward from left joystick
			int turn = controller.get_analog(ANALOG_RIGHT_X); // Gets the turn left/right from right joystick
			left_mg = dir - turn; // Sets left motor voltage
			right_mg = dir + turn; // Sets right motor voltage
		} else {
			// Tank control scheme
			left_mg = controller.get_analog(ANALOG_LEFT_Y); // Sets left motor voltage
			right_mg = controller.get_analog(ANALOG_RIGHT_Y); // Sets right motor voltage
		}

		/**
		 * @brief intake
		 * If "A" is pressed, start intake
		 */
		if (controller.get_digital(DIGITAL_L1)) { // If "A" is pressed
			intake.move_velocity(750); // Start intake
		} else if (controller.get_digital(DIGITAL_L2)) {
			intake.move_velocity(-750); // Start intake
		} else {
			intake.brake(); // Stop intake
		}

		/**
		 * @brief Toggle shooting
		 * 
		 * if R1 is pressed, start shooting UNTIL R2 is pressed
		 */
		if (controller.get_digital(DIGITAL_R1)) { // If R1 is pressed
			shooting = true; // Set shooting to true
		}
		if (controller.get_digital(DIGITAL_R2)) { // If R2 is pressed
			shooting = false; // Set shooting to fals
		}

		if (shooting) { // If shooting
			catapult_mg.move_velocity(75); // Start catapult
		} else {
			catapult_mg.brake(); // Stop catapult
		}

		pros::delay(CONTROLLER_UPDATE_FPS); // Run for set ms then update
	}
}
