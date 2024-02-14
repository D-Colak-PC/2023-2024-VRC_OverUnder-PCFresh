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

void openWings() {
	bool left_wing_open;
	bool right_wing_open;
	wing_mg.move_absolute(120, 200);
	while (true) {
		left_wing_open = (left_wing.get_position() < 125) && (left_wing.get_position() > 115);
		right_wing_open = (right_wing.get_position() < 125) && (right_wing.get_position() > 115);
		if (left_wing_open) { // if left wing is open:
			if (right_wing_open) { // if both wings are open, exit loop.
				left_wing.brake(); // edge case where both wings open at exactly the same time
				right_wing.brake(); // stop right wing
				break; // both wings are open, therefore exit loop
			} else { // right wing is not open
				left_wing.brake(); // only brake left wing
			}
		}

		pros::delay(10);
	}
}


void moveWings(int target, int speed, int error_range = 10, int timeout = 50) {
	int left_wing_position = left_wing.get_position();
	int right_wing_position = right_wing.get_position();
	bool left_wing_in_range = (left_wing_position < (target + error_range)) && (left_wing_position > (target - error_range));
	bool right_wing_in_range = (right_wing_position < (target + error_range)) && (right_wing_position > (target - error_range));
	int start_time = pros::millis();

	if (left_wing_in_range && right_wing_in_range) { // dont move if already in position
		return;
	}

	wing_mg.move_absolute(target, speed); // Move to position

	while (pros::millis() - start_time < timeout) { // timeout if something goes wrong.
	 	// if both wings are already braked
		if (left_wing.get_target_velocity() == 0 && right_wing.get_target_velocity() == 0) {
			break; // exit loop
		}

		// if left wing is in range, brake it
		if (left_wing_in_range) {
			left_wing.brake();
		}

		// if right wing is in range, brake it
		if (right_wing_in_range) {
			right_wing.brake();
		}

		// update variables
		left_wing_position = left_wing.get_position();
		right_wing_position = right_wing.get_position();
		left_wing_in_range = (left_wing_position < (target + error_range)) && (left_wing_position > (target - error_range));
		right_wing_in_range = (right_wing_position < (target + error_range)) && (right_wing_position > (target - error_range));

		// small delay to keep PROS happy
		pros::delay(2);
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
			pros::lcd::print(5, "closing wings");
			moveWings(0, -50); // Close wings
		} else if (controller.get_digital(DIGITAL_L1)) { // If "L1" is pressed
			pros::lcd::print(5, "opening wings");
			moveWings(280, 100); // Close wings
		}

		pros::delay(CONTROLLER_UPDATE_FPS); // Run for set ms then update
	}
}
