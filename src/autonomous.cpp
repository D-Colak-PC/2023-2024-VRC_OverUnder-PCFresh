#include "main.h"
#include "devices.h"
#include "autonomous.h"
#include "chassis.h"
#include <ctime>



/*
██████╗  ██████╗  ██╗██╗  ██╗██╗  ██╗██████╗ 
╚════██╗██╔═████╗███║██║  ██║██║  ██║██╔══██╗
 █████╔╝██║██╔██║╚██║███████║███████║██████╔╝
██╔═══╝ ████╔╝██║ ██║╚════██║╚════██║██╔══██╗
███████╗╚██████╔╝ ██║     ██║     ██║██████╔╝
╚══════╝ ╚═════╝  ╚═╝     ╚═╝     ╚═╝╚═════╝ 
*/

const int TILE_SIZE = 24; // inches
const float ROBOT_LENGTH = 16; // inches
const float ROBOT_WIDTH = 14.5; // inches
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

// 1 for offensive, 2 for defensive, 3 for skills
void autonomous() {
	int current_auton = 2;
	if (current_auton == 1) {
		offensiveAuton();
	} else if (current_auton == 2) {
		defensiveAuton();
	} else if (current_auton == 3) {
		skillsAuton();
	}
}


/**
 * @brief Autonomous code for the offensive placement
 * 
 * Offensive:
 * If robot is on same side as their goal, it is offensive
 * EXP: Red alliance robot on red side, blue alliance robot on blue side
 * 
 * Goal: Score Alliance Ball, then position in the middle to score other balls after autonomous period ends
 */
void offensiveAuton() {
	/**
	 * at in intake
	 * drive forward 2 blocks
	 * outtake
	 * wait 500ms
	 * stop outake
	 * right 90
	 * intake
	 * drive forward 2 blocks
	 * stop intake
	 * drive back 1 block
	 * left 135
	 * outtake
	 * wait 500ms
	 * stop outake
	 * right 90
	 * intake
	 * forward sqrt(2) blocks
	 * stop intake
	 * right 45
	 * open wings
	 * drive back 1 block
	 * left 10
	 * drive back 1 block
	 * wait 500ms
	 * close wings
	 * drive forward 1 block
	 * right 180
	 * drive forward 1 block
	 * outtake
	 * wait 500ms
	 * stop outake
	*/
}

/**
 * @brief Autonomous code for the defensive placement
 * 
 * Defensive:
 * If robot is on opposite side as their goal, it is defensive
 * EXP: Red alliance robot on blue side, blue alliance robot on red side
 * 
 * Goal: Score Alliance Ball, then position in the middle to score other balls after autonomous period ends
 */

void defensiveAuton() {
	chassis.setPose(-ROBOT_LENGTH/2, (TILE_SIZE + ROBOT_WIDTH/2), 270);
	
	chassis.moveToPose((-2.5*TILE_SIZE), (1.5*TILE_SIZE), 270, 4000); // go to goal
	chassis.moveToPose((-2.5*TILE_SIZE), (1.5*TILE_SIZE), 180, 1000); // go to goal
	chassis.waitUntilDone();

	intake.move(-75); // intake to suck in goal
	pros::delay(500);

	chassis.moveToPose((-2.5*TILE_SIZE), TILE_SIZE + 7.5, 180, 2000, {.minSpeed = 100, .earlyExitRange = 1}); // go to goal
	chassis.moveToPose((-2.5*TILE_SIZE), (1.5*TILE_SIZE), 180, 2000, {.forwards = false, .minSpeed = 70}); // go to goal
	chassis.waitUntilDone();
	
	intake.brake();

	chassis.turnTo(-3*TILE_SIZE + 6, 3*TILE_SIZE + 6, 1000); // turn to face middle ball
	chassis.waitUntilDone();

	intake.move(100);

	chassis.moveToPose(-3*TILE_SIZE + 6, 3*TILE_SIZE - 6, 0, 2000); // go to middle ball
	chassis.waitUntilDone();

	pros::delay(200);

	intake.brake();

	

	// chassis.moveToPose(-2*TILE_SIZE, (2*TILE_SIZE), 0, 1000, {.forwards = false}); // back up from right triball
	// chassis.moveToPose(-2*TILE_SIZE, 1.5*TILE_SIZE, -135, 1000); // turn to face goal

	// chassis.moveToPose((-2*TILE_SIZE) - 7.5, 1.5*TILE_SIZE - 7.5, -135, 500, {.minSpeed = 100, .earlyExitRange = 1}); // go to goal
	// chassis.waitUntilDone();

	// intake.move(-50); // outtake at goal

	// chassis.moveToPose(-2*TILE_SIZE, 1.5*TILE_SIZE, -135, 500, {.forwards = false, .minSpeed = 70}); // go to goal
	// chassis.waitUntilDone();

	// intake.brake();


	

	// intake.move(-50); // outtake at goal
	// pros::delay(200);

	// chassis.moveToPose((-2*TILE_SIZE) + (ROBOT_LENGTH/2), TILE_SIZE + (ROBOT_WIDTH/2) + 5, 270, 1000, {.forwards = false}); // back up from at
	// chassis.waitUntilDone();

	// intake.move(150); // intake to suck in right triball

	// chassis.moveToPose(-2*TILE_SIZE, (3*TILE_SIZE) - (ROBOT_LENGTH/2) - 5, 0, 2000); // go to right triball
	// chassis.waitUntilDone();

	// pros::delay(200);

	// intake.brake(); // hold right triball

	// pros::delay(200);
	// chassis.moveToPose(-2*TILE_SIZE, (2*TILE_SIZE), 180, 1000, {.forwards = false, .minSpeed = 60}); // back up from right triball
	// chassis.moveToPose(-2.5*TILE_SIZE, 1.5*TILE_SIZE, -160, 4000); // turn to face goal
	// chassis.waitUntilDone();

	// intake.move(-50); // outtake at goal
	// pros::delay(200);

	// chassis.moveToPose(-2.5*TILE_SIZE, 2*TILE_SIZE, -135, 2000, {.forwards = false}); // back up from goal
	// chassis.waitUntilDone();
}


void skillsAuton() {
	catapult_mg.move_velocity(75);
}