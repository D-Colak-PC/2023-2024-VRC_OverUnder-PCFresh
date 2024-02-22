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
lemlib::Drivetrain drivetrain {
    &left_drive_mg, // left drive train
    &right_drive_mg, // right drive train
	TRACK_WIDTH, // track width
    lemlib::Omniwheel::NEW_4, // wheel diameter
    WHEEL_RPM, // wheel rpm
	CHASE_POWER // chase power
};

// odometry and sensors to help with PID
lemlib::OdomSensors odomSensors {
    nullptr,
    nullptr,
    nullptr,
    nullptr,
    &imu // imu
};

// forward/backward PID
lemlib::ControllerSettings linearController {
    10, // kP
	0, // kI
    3, // kD
	3, // antiWindup
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    2 // slew rate (max acceleration)
};
 
// turning PID
lemlib::ControllerSettings angularController {
    3, // kP
	0, // kI
	15, // kD
	3, // antiWindup 
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    0 // slew rate (max acceleration) (0 = no limit)
};

// chassis
lemlib::Chassis chassis (
    drivetrain,
    linearController,
    angularController,
    odomSensors
);


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
    const float amt_to_move = distance * 360 / 4;
    
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


void intake_move(int speed, int timeout) {
	intake.move_velocity(speed);
	pros::delay(timeout);
	intake.brake();
};