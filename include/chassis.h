#include "main.h"
#include "lemlib/api.hpp"

/*
██████╗  ██████╗  ██╗██╗  ██╗██╗  ██╗██████╗ 
╚════██╗██╔═████╗███║██║  ██║██║  ██║██╔══██╗
 █████╔╝██║██╔██║╚██║███████║███████║██████╔╝
██╔═══╝ ████╔╝██║ ██║╚════██║╚════██║██╔══██╗
███████╗╚██████╔╝ ██║     ██║     ██║██████╔╝
╚══════╝ ╚═════╝  ╚═╝     ╚═╝     ╚═╝╚═════╝ 
*/


// variables for lemlib PID:
const int WHEEL_DIAMETER = 4;
const double TRACK_WIDTH = 11.625; // 11 + 5/8 inches
const int WHEEL_RPM = 200; 

extern lemlib::Drivetrain_t drivetrain;
extern lemlib::OdomSensors_t odomSensors;
extern lemlib::ChassisController_t lateralController;
extern lemlib::ChassisController_t angularController;

extern lemlib::Chassis chassis;
