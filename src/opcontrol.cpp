#include "main.h"
#include "chassis.h"
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

	while (true) {
		// Tank control scheme
		left_drive_mg = controller.get_analog(ANALOG_LEFT_Y); // Sets left motor voltage
		right_drive_mg = controller.get_analog(ANALOG_RIGHT_Y); // Sets right motor voltage

		/**
		 * @brief intake
		 * If "R1" is pressed, run intake. If "R2" is pressed, reverse intake
		 */
		if (controller.get_digital(DIGITAL_R1)) { // If "R1" is pressed
			if (distance_sensor.get() >= 30) { // If ball is more than 30 mm away
				intake.move_velocity(750); // run intake
			} else {
				intake.brake(); // Stop intake so ball doesn't get stuck inside intake
			}

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
if (controller.get_digital(DIGITAL_X)) { // If "X" is pressed
    catapult_mg.move_velocity(75); // Run the catapult at 75 velocity
    while (!controller.get_digital(DIGITAL_B)) {} // While B is not pressed, do nothing
    catapult_mg.move_velocity(0); // Stop the catapult once B is pressed
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
