#include "main.h"
#include "pros/misc.h"
#include "pros/misc.hpp"

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

	bool L1Button;
	bool L2Button;
	bool R1Button;
	bool R2Button;

	if(!pros::competition::is_connected()) {
		// competition_initialize();
		// autonSelect = 3;
		// autonomous();
	}
	
	while (true) {



		L1Button = Controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
		L2Button = Controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2);
		R1Button = Controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
		R2Button = Controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2);

		setDriveMotors();
		
		if (Controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) DirectionToggle();
		if (Controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B)) Expansion();
		if (Controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) ToggleFlywheelSpeed();
		if (Controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) SpinRoller();
		if (Controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) Indexer();
		if (Controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) ToggleFlywheel(FlywheelMotorSpeed);
		if (Controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) BackwardsIntake();
		if (Controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) ToggleIntake();

		if ((Controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)
			|| Controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2) 
			|| Controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)
			|| Controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2))
			&& L1Button && L2Button && R1Button && R2Button) {
				odomKillSwitch();
			}
	
		/*
		if(Controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) FlySpeedInc100();
		if(Controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) FlySpeedDec100();
		if(Controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) FlySpeedInc10();
		if(Controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) FlySpeedDec10();
		*/

		pros::delay(20);

	}
}