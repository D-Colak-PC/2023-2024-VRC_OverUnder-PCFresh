#include "main.h"
#include "lemlib/api.hpp"
#include "devices.h"

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

void moveWings(int target, int speed, int error_range = 10, int timeout = 50);
void move(int distance, int speed = 200);
void turn(int degrees, int speed = 100, bool left = false);
void intake_roller(int timeout);
void outtake_roller(int timeout);