#include "main.h"
#include "globals.h"
#include "okapi/api.hpp"

/*
██████╗  ██████╗  ██╗██╗  ██╗██╗  ██╗██████╗ 
╚════██╗██╔═████╗███║██║  ██║██║  ██║██╔══██╗
 █████╔╝██║██╔██║╚██║███████║███████║██████╔╝
██╔═══╝ ████╔╝██║ ██║╚════██║╚════██║██╔══██╗
███████╗╚██████╔╝ ██║     ██║     ██║██████╔╝
╚══════╝ ╚═════╝  ╚═╝     ╚═╝     ╚═╝╚═════╝ 
*/

// motors & motor groups
pros::Motor back_left_drive(BACK_LEFT_DRIVE_PORT, pros::E_MOTOR_GEARSET_18, true); // Creates back left drive motor object
pros::Motor back_right_drive(BACK_RIGHT_DRIVE_PORT, pros::E_MOTOR_GEARSET_18, false); // Creates back right drive motor object
pros::Motor front_left_drive(FRONT_LEFT_DRIVE_PORT, pros::E_MOTOR_GEARSET_18, true); // Creates front left drive motor object
pros::Motor front_right_drive(FRONT_RIGHT_DRIVE_PORT, pros::E_MOTOR_GEARSET_18, false); // Creates front right drive motor object
pros::Motor catapult_left(LEFT_CATAPULT_PORT,  pros::E_MOTOR_GEARSET_18, true); // Creates left catapult motor object
pros::Motor catapult_right(RIGHT_CATAPULT_PORT, pros::E_MOTOR_GEARSET_18, false); // Creates right catapult motor object
pros::MotorGroup left_mg({back_left_drive, front_left_drive}); // Creates left drive motor group with reversed ports 18 & 20
pros::MotorGroup right_mg({back_right_drive, front_right_drive}); // Creates right drive motor group with normal ports 17 & 19
pros::MotorGroup catapult_mg({catapult_left, catapult_right}); // Creates catapult motor group with reversed port 13 & normal port 16
pros::Motor intake(INTAKE_PORT, pros::E_MOTOR_GEARSET_06, true); // Creates intake motor object

// controller
pros::Controller controller(pros::E_CONTROLLER_MASTER); // Creates controller object for master controller

// sensors
// pros::ADIGyro gyro(12); // Creates gyro object
pros::ADIDigitalIn back_bump_sensor(BACK_BUMPER_PORT); // Creates back bumper sensor object

/*
// LemLib functions
lemlib:: Drivetrain_t drivetrain {
    &left_mg, // left drive train
    &right_mg, // right drive train
    TRACK_WIDTH,    
    WHEEL_DIAMETER,
    WHEEL_RPM
};


// forward/backward PID
lemlib::ChassisController_t lateralController {
    8, // kP
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

// odometry (sensors)
lemlib::OdomSensors_t sensors {
    nullptr, // vertical tracking wheel 1
    nullptr, // vertical tracking wheel 2
    nullptr, // horizontal tracking wheel 1
    nullptr, // horizontal tracking wheel 2
    &gyro, // gyro
};

// chassis
lemlib::Chassis chassis {
    &drivetrain, // drivetrain
    &lateralController, // forward/backward PID
    &angularController, // turning PID
    &sensors // odometry
};

*/
