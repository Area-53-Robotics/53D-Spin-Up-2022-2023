#include "main.h"
#include "pros/misc.h"
#include "pros/screen.h"
#include "pros/screen.hpp"

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	ControllerDisplay();
	Controller.rumble(".");
	bool XButton;
	bool YButton;
	bool XButton_old;
	bool YButton_old;

	double matchTimer = 90;

	while (true) {

		// competition_initialize();
		// autonomous();

		XButton = Controller.get_digital(DIGITAL_X);
		YButton = Controller.get_digital(DIGITAL_Y);
		AButton = Controller.get_digital(DIGITAL_A);

		setDriveMotors();
		
		if (XButton && !XButton_old) DirectionToggle();
		if (YButton && !YButton_old) ToggleIntake();
		if (AButton && !AButton_old && matchTimer < 15) Expansion();

		XButton_old = XButton;
		YButton_old = YButton;
		AButton_old = AButton;

		matchTimer -= 0.20;

		pros::delay(20);

	}
}