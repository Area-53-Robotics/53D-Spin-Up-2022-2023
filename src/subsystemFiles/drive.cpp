#include "main.h"
#include "subsystemHeaders/drive.hpp"

/*
?   All functions related to the driving the robot during the driver
?   controlled phase of the match
*/

//* Integer variables to store joystick values from the controller
short int LYAxis;
short int RYAxis;

/*
    * Boolean ariable to store whether the driver has set the robot
    * to drive reversed or not
*/
bool isReverse = false;

/*
    * Joystick curve function; takes the value of a joystick and
    * curves its value to allow for better robot control
*/
float getMotorOutput(int input) {
    return (std::exp(-20/12.7)+std::exp((std::abs(input)-127)/12.7)*(1-std::exp(-20/12.7))) * input;
}

/*
    * Reverses the drivetrain direction from its current direction
    * and displays the direction on the controller
*/
void DirectionToggle() {
    isReverse = !isReverse;
    MainControllerDisplay();
}

void setDriveMotors() {
    /*
        * Updates the joystick variables to the new values of the
        * joysticks
    */
	LYAxis = Controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
	RYAxis = Controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

    /*
        * Joystick deadzone: If the value reported by the joystick is
        * less than 10, it is set to 0. This prevents drift.
    */
    if (abs(LYAxis) < 10) LYAxis = 0;
    if (abs(RYAxis) < 10) RYAxis = 0;

    if (isReverse == false) {
        /*
            * If the drivetrain is set to drive in the normal
            * direction, the motors move according to the curved
            * joystick values
        */
        LMotors.move(getMotorOutput(LYAxis));
        RMotors.move(getMotorOutput(RYAxis));
    } else if (isReverse == true) {
        /*
            * If the drivetrain is set to drive reversed, the motors
            * move according to the negative curved joystick values.
            * Each side of the drivetrain is set to move according to
            * its opposite axis because the driver will be looking at
            * the robot from a new perspective.
        */
        LMotors.move(getMotorOutput(RYAxis) * -1);
        RMotors.move(getMotorOutput(LYAxis) * -1);
    }
}