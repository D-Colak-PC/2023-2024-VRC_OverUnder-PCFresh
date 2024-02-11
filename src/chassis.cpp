#include "main.h"
#include "lemlib/api.hpp"
#include "chassis.h"
#include "devices.h"

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

// chassis
lemlib::Chassis chassis(
    drivetrain,
    lateralController,
    angularController,
    odomSensors);