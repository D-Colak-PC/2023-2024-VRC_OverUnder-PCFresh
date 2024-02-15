#include "chassis.h"

/*
██████╗  ██████╗  ██╗██╗  ██╗██╗  ██╗██████╗ 
╚════██╗██╔═████╗███║██║  ██║██║  ██║██╔══██╗
 █████╔╝██║██╔██║╚██║███████║███████║██████╔╝
██╔═══╝ ████╔╝██║ ██║╚════██║╚════██║██╔══██╗
███████╗╚██████╔╝ ██║     ██║     ██║██████╔╝
╚══════╝ ╚═════╝  ╚═╝     ╚═╝     ╚═╝╚═════╝ 
*/

// creation of drivetrain
lemlib::Drivetrain_t drivetrain = {
    &left_drive_mg, // left drive train
    &right_drive_mg, // right drive train
    WHEEL_DIAMETER, // wheel diameter
    TRACK_WIDTH, // track (from center of left wheel to center of right wheel)
    WHEEL_RPM // wheel rpm
};

// odometry and sensors to help with PID
lemlib::OdomSensors_t odomSensors {
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    &imu // imu
};

// forward/backward PID
lemlib::ChassisController_t lateralController {
    10, // kP
    30, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    5 // slew rate
};
 
// turning PID
lemlib::ChassisController_t angularController {
    4, // kP
    40, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    0 // slew rate
};

// chassis
lemlib::Chassis chassis(
    drivetrain,
    lateralController,
    angularController,
    odomSensors);


void moveWings(int target, int speed, int error_range, int timeout) {
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
};


void move(int distance, int speed) { // distance is in inches
    const float amt_to_move = distance * 360 / WHEEL_DIAMETER;
    
    left_drive_mg.move_relative(amt_to_move, speed);
    right_drive_mg.move_relative(amt_to_move, speed);
    
    while (front_left_drive.get_target_position() && front_right_drive.get_target_position()) {
        pros::delay(10);
    }
    
    left_drive_mg.brake();
    right_drive_mg.brake();
	
}


void turn(int degrees, int speed, bool left) { // degrees is in degrees
	if (left) {
		degrees *= -1;
	}

	left_drive_mg.move_relative(-degrees * 3.5, speed);
	right_drive_mg.move_relative(degrees * 3.5, speed);

	while (front_left_drive.get_target_velocity() && front_right_drive.get_target_velocity()) {
		pros::delay(10);
	}

	left_drive_mg.brake();
	right_drive_mg.brake();
};


void intake_roller(int timeout) {
	intake.move_velocity(200);
	pros::delay(timeout);
	intake.brake();
};


void outtake_roller(int timeout) {
	intake.move_velocity(-200);
	pros::delay(timeout);
	intake.brake();
};