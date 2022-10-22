#include "main.h"

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
	Controller.clear();
	switch (autonSelect) {
		case 1:
			Controller.print(0, 0, "Running Left Quals Auton");
			Controller.print(1, 0, "Auton Completed");
			break;
		case 2:
			Controller.print(0, 0, "Running Right Quals Auton");
			Controller.print(1, 0, "Auton Completed");
			break;
		case 3:
			Controller.print(0, 0, "Running Left Elims Auton");
			Controller.print(1, 0, "Auton Completed");
			break;
		case 4:
			Controller.print(0, 0, "Running Right Elims Auton");
			Controller.print(1, 0, "Auton Completed");
			break;
		case 5:
			Controller.print(0, 0, "No Auton Selected");
			break;
		case 6:
			Controller.print(0, 0, "Running Programming Skills");
			Controller.print(1, 0, "Skills Complete");
			break;
	}
}