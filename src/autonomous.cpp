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
	int current_auton = 1;
	// int start_time = std::time(0);
	pros::delay(2000);

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

	chassis.setPose(0, 0, 0);
	chassis.moveTo(0, 24, 1000);
	controller.set_text(0, 0, "trolling");
	move(24); // inches
	outtake_roller(500); // ms
	turn(90); // degrees, right
	intake.move_velocity(200);
	move(24);
	intake.brake();
	move(-12);
	turn(135, true); // degrees, left
	outtake_roller(500);
	turn(90);
	intake.move_velocity(200);
	move(24 * sqrt(2));
	intake.brake();
	turn(45);
	moveWings(280, 100);
	move(-12);
	turn(10, true);
	move(-12);
	pros::delay(500);
	moveWings(0, -50);
	move(12);
	turn(180);
	move(12);
	outtake_roller(500);
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
	chassis.moveTo(100, 0, 1000);
}


void skillsAuton() {
	catapult_mg.move_velocity(75);
}