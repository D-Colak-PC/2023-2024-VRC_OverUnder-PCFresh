#include "main.h"
#include "devices.h"
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
		// Tank control scheme
		left_drive_mg = controller.get_analog(ANALOG_LEFT_Y); // Sets left motor voltage
		right_drive_mg = controller.get_analog(ANALOG_RIGHT_Y); // Sets right motor voltage

		/**
		 * @brief intake
		 * If "A" is pressed, start intake
		 */
		if (controller.get_digital(DIGITAL_R1)) { // If "A" is pressed
			intake.move_velocity(750); // Start intake
		} else if (controller.get_digital(DIGITAL_R2)) {
			intake.move_velocity(-750); // Start intake
		} else {
			intake.brake(); // Stop intake
		}

		/**
		 * @brief Toggle shooting
		 * 
		 * if X is pressed, start shooting UNTIL B is pressed
		 */
		if (controller.get_digital(DIGITAL_X)) { // If X is pressed
			catapult_mg.move_velocity(75); // Start catapult
		}

		if (controller.get_digital(DIGITAL_B)) { // If B is pressed
			catapult_mg.brake(); // Stop catapult
		}

		/**
		 * @brief wings
		 * 
		 * If "L1" is pressed, open wings. If "L2" is pressed, close wings
		 */
		if  (controller.get_digital(DIGITAL_L2)) { // If "L2" is pressed
			wing_mg.move_absolute(0, 200); // Close wings to 0 degrees at 200 velocity
			wing_mg.brake(); // Stop wings
		} else if (controller.get_digital(DIGITAL_L1)) { // If "L1" is pressed
			wing_mg.move_absolute(100, 200); // Open wings to 100 degrees at 200 velocity
			wing_mg.brake(); // Stop wings
		}

		pros::delay(CONTROLLER_UPDATE_FPS); // Run for set ms then update
	}
}
