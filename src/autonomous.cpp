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
	Controller.clear();
	// autonSelect = 7;
	std::cout << autonSelect << std::endl;
	switch (autonSelect) {
		case 1:
			pros::delay(50);
			Controller.print(0, 0, "Ur mom weighs auton");
			BackwardsIntake();
			drive(0.1, 50);
			pros::delay(250);
			BackwardsIntake();
			drive(-0.1, 50);
			while(!FRM.is_stopped()) pros::delay(2);
			turn('R', 0.75,50);
			while(!FRM.is_stopped()) pros::delay(2);
			ToggleIntake();
			ToggleFlywheel(400);
			pros::delay(6000);
			Indexer();
			pros::delay(2000);
			Indexer();
			pros::delay(2000);
			Indexer();
			pros::delay(2000);
			Indexer();
			Controller.print(1, 0, "Auton Completed");
			break;
		case 2:
			Controller.print(0, 0, "Right Quals Auton");
			drive(1,50);
			pros::delay(1000);
			turn('R', 0.7,50);
			while(!FRM.is_stopped()) pros::delay(2);
			drive(1,50);
			while(!FRM.is_stopped()) pros::delay(2);
			turn('R',0.7,50);
			while(!FRM.is_stopped()) pros::delay(2);
			drive(1, 50);
			while(!FRM.is_stopped()) pros::delay(2);
			ToggleIntake();
			pros::delay(500);
			ToggleIntake();
			// Copied from Left Quals Auton
			turn('R', 0.8,50);
			while(!FRM.is_stopped()) pros::delay(2);
			ToggleFlywheel(475);
			pros::delay(6000);
			Indexer();
			pros::delay(2000);
			Indexer();
			pros::delay(2000);
			Indexer();
			pros::delay(2000);
			Indexer();
			// Copied from Left Quals Auton
			Controller.print(0,0,"Auton Completed");
			break;
		case 3:
			Controller.print(0, 0, "Left Elims Auton");
			BackwardsIntake();
			drive(0.1, 50);
			while(!FRM.is_stopped()) pros::delay(2);
			// pros::delay(250);
			BackwardsIntake();
			drive(-0.1, 50);
			while(!FRM.is_stopped()) pros::delay(2);
			turn('R', 0.75,50);
			while(!FRM.is_stopped()) pros::delay(2);
			ToggleIntake();
			pros::delay(500);
			ToggleFlywheel(400);
			pros::delay(4000);
			Indexer();
			pros::delay(1000);
			Indexer();
			pros::delay(1000);
			Indexer();
			pros::delay(1000);
			Indexer();
			pros::delay(1000);
			ToggleIntake();
			pros::delay(50);
			ToggleFlywheel(400); // actually turns it off
			pros::delay(1000);
			turn('L', 0.375, 50);
			while(!FRM.is_stopped()) pros::delay(2);
			drive(-0.5, 50);
			while(!FRM.is_stopped()) pros::delay(2);
			/*
			turn('R', 4, 50);
			// drive(3, 50);
			*/
			Controller.print(1, 0, "Auton Completed");
			break;
		case 4:
			Controller.print(0, 0, "Right Elims Auton");
			turn('R', 0.7, 100);
			Controller.print(1, 0, "Auton Completed");
			break;
		case 5:
			Controller.print(0, 0, "Full AWP");
			break;
		case 6:
			Controller.print(0, 0, "No Auton Selected");
			break;
		case 7:
			pros::delay(50);
			Controller.print(0, 0, "Programming Skills");
			drive(0.1,50);
			BackwardsIntake();
			pros::delay(500); // originally 500 msec
			BackwardsIntake();
			drive(-0.2, 50);
			pros::delay(1000);
			turn('R', 0.7,50);
			pros::delay(1000);
			drive(3, 50); // big big important
			pros::delay(1000);
			turn('R', 0.1, 50);
			ToggleFlywheel(363); // og 475
			pros::delay(6000);
			Indexer();
			pros::delay(2000);
			Indexer();
			pros::delay(2000);
			Indexer();
			pros::delay(2000);
			Indexer();
			Expansion();
			Controller.print(1, 0, "Skills Complete");
			break;
	}
}