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

	while (true) {

		// competition_initialize();
		// autonomous();

		setDriveMotors();
		
		if (Controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) DirectionToggle();
		if (Controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) Expansion();
		if (Controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) Indexer();
		if (Controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) ToggleFlywheel(600);
		if (Controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) ToggleIntake();

		pros::delay(20);

	}
}