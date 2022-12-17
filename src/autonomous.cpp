#include "main.h"
#include "pros/rtos.hpp"

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	GamePhase = 2;
	autonSelect = 4;
	Controller.clear();
	switch (autonSelect) {
		case 1:
			Controller.print(0, 0, "Left Quals Auton");
			drive(0.75, 100);
			turn('R', 1, 100);
			drive(0.3, 100);
			ToggleIntake();
			pros::delay(50);
			ToggleIntake();
			Controller.print(1, 0, "Auton Completed");
			break;
		case 2:
			Controller.print(0, 0, "Right Quals Auton");
			Controller.print(1, 0, "Auton Completed");
			break;
		case 3:
			Controller.print(0, 0, "Left Elims Auton");
			ToggleIntake();
			pros::delay(50);
			ToggleIntake();
			drive(-0.75, 100);
			turn('R', 0.5, 100);
			drive(0.75, 100);
			ToggleIntake();
			pros::delay(50);
			ToggleIntake();
			Controller.print(1, 0, "Auton Completed");
			break;
		case 4:
			Controller.print(0, 0, "Right Elims Auton");
			turn('R', 0.7, 100);
			Controller.print(1, 0, "Auton Completed");
			break;
		case 5:
			Controller.print(0, 0, "No Auton Selected");
			break;
		case 6:
			Controller.print(0, 0, "Programming Skills");
			Controller.print(1, 0, "Skills Complete");
			break;
	}
}