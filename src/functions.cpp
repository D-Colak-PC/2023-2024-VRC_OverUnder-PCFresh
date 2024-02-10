#include "main.h"
#include "devices.h"
#include "functions.h"

/*
██████╗  ██████╗  ██╗██╗  ██╗██╗  ██╗██████╗ 
╚════██╗██╔═████╗███║██║  ██║██║  ██║██╔══██╗
 █████╔╝██║██╔██║╚██║███████║███████║██████╔╝
██╔═══╝ ████╔╝██║ ██║╚════██║╚════██║██╔══██╗
███████╗╚██████╔╝ ██║     ██║     ██║██████╔╝
╚══════╝ ╚═════╝  ╚═╝     ╚═╝     ╚═╝╚═════╝ 
*/

/*
void move(int vel = 100, bool backwards, int time) {
    if (backwards) {
        left_mg.move_velocity(-vel);
        right_mg.move_velocity(-vel);
    } else {
        left_mg.move_velocity(vel);
        right_mg.move_velocity(vel);
    }
    pros::delay(time);
    left_mg.brake();
    right_mg.brake();
}
*/

/*


void turn(int degree, bool clockwise = true) {
    int error_rate = 5;

    if (clockwise) {
        left_mg.move_relative(-degree, 100);
        right_mg.move_relative(degree, 100);

        while (left_mg.get_position() > -degree + error_rate) {
            pros::delay(10);
        }
    } else {
        left_mg.move_relative(degree, 100);
        right_mg.move_relative(-degree, 100);

        while (left_mg.get_position() < degree - error_rate) {
            pros::delay(10);
        }
    }

    left_mg.break();
    right_mg.break();
}
*/
