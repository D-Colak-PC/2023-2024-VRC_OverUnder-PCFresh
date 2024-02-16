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
const float TRACK_WIDTH = 11.625; // 11 + 5/8 in
const int WHEEL_RPM = 200; 
const int CHASE_POWER = 2; // how fast a robot can turn a corner

extern lemlib::Drivetrain drivetrain;
extern lemlib::OdomSensors odomSensors;
extern lemlib::ControllerSettings linearController;
extern lemlib::ControllerSettings angularController;

extern lemlib::Chassis chassis;

void moveWings(int target, int speed, int error_range = 10, int timeout = 50);
void move(int distance, int speed = 200);
void turn(int degrees, int speed = 100, bool left = false);
void intake_roller(int timeout);
void outtake_roller(int timeout);