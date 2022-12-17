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
	bool AButton;
	bool XButton_old;
	bool YButton_old;
	bool AButton_old;

	while (true) {

		/*
		if(Controller.get_digital_new_press(DIGITAL_DOWN)) DownPressed();
		if(Controller.get_digital_new_press(DIGITAL_UP)) UpPressed();
		if(Controller.get_digital_new_press(DIGITAL_A)) APressed();
		if(Controller.get_digital_new_press(DIGITAL_B)) BPressed();

		pros::screen::print(pros::E_TEXT_MEDIUM, 1, "AutonSelecting: %d", AutonSelecting);
		pros::screen::print(pros::E_TEXT_MEDIUM, 2, "MotorChecking: %d", MotorChecking);
		pros::screen::print(pros::E_TEXT_MEDIUM, 3, "Page: %d", Page);
		pros::screen::print(pros::E_TEXT_MEDIUM, 4, "Line: %d", Line);
		*/	

		XButton = Controller.get_digital(DIGITAL_X);
		YButton = Controller.get_digital(DIGITAL_Y);
		AButton = Controller.get_digital(DIGITAL_A);

		setDriveMotors();
		// 2.375
		// learned a lesson, spent yesterday unscrewing the drivetrain to fix a lock when it was just a nut interfering
		
		if (XButton && !XButton_old) DirectionToggle();
		if (YButton && !YButton_old) ToggleIntake();
		if (AButton && !AButton_old) Expansion();

		XButton_old = XButton;
		YButton_old = YButton;
		AButton_old = AButton;

		pros::delay(20);

	}
}