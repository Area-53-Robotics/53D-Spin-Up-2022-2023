#include "main.h"
#include "sylib/system.hpp"

//* The robot drives the given length at the given velocity
void drive(double length, int velocity) {
	LMotors.move_relative(length, 200);
	RMotors.move_relative(length, 200);
}

//* The robot turns in the given direction at the given length
void turn(char direction, double length, int velocity) {
    if (direction == 'L') {
		LMotors.move_relative(length * -1, 200);
		RMotors.move_relative(length, 200);
    } else if (direction == 'R') {
		LMotors.move_relative(length, 200);
		RMotors.move_relative(length * -1, 200);
    }
}

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
	if (pros::competition::is_connected()) autonSelect = 2;
	setStartingOdomValues();
	Controller.clear();
	switch (autonSelect) {
		case 1:
			//* TLDR: Gets roller & shoots 2 discs into low goal
			//
				//* Last updated 1/21/23
			//
			Controller.print(0, 0, "Left Side Auton");

			//* Rolls the left side roller
			ReverseIntake();
			drive(0.1, 50);
			sylib::delay(250);
			ReverseIntake();

			//* The robot turns toward the low goal
			drive(-0.50, 50);
			sylib::delay(1000);
			PIDTurn(M_PI);

			//* The robot shoots the pre loads into the low goal
			ForwardIntake();
			sylib::delay(500);
			AutonFlywheel(410);
			sylib::delay(4000);
			for (int i = 0; i < 4; i++) {
				Indexer();
				sylib::delay(2000);
			}
			ForwardIntake();
			sylib::delay(50);
			AutonFlywheel(0);
			sylib::delay(1000);

			//* Turns the bot towards the middle of the field
			turn('L', 0.375, 50);
			while(!FRM.is_stopped()) sylib::delay(2);
			drive(-0.5, 50);
			while(!FRM.is_stopped()) sylib::delay(2);

			Controller.print(1, 0, "Auton Completed");
			break;
		case 2:
			//* TLDR: Moves toward & turns roller, shoots 2 discs into low goal
			//
				//* Last updated 2/11/23
			//
			Controller.print(0, 0, "Right Quals Auton");

			//* The robot moves toward and rolls the right side roller
			drive(1.4, 50);
			sylib::delay(1000);
			turn('R', 0.65, 50);
			sylib::delay(1000);
			drive(0.4, 50);
			sylib::delay(1000);
			ReverseIntake();
			sylib::delay(300);
			ReverseIntake();
			sylib::delay(500);

			//* The robot turns toward the low goal
			drive(-0.3, 50);
			sylib::delay(1400);
			turn('L', 0.7, 50);
			sylib::delay(1500);

			//* The robot shoots the pre loads into the low goal
			AutonFlywheel(350);
			sylib::delay(3000);
			for(int i = 0; i < 8; i++) {
				Indexer();
				sylib::delay(1200);
			}

			Controller.print(0,0,"Auton Completed");
			break;
		case 3:
			//
				//* Last updated 1/21/23
			//
			Controller.print(0, 0, "Left Elims Auton");

			//* The robot rolls the color roller
			ReverseIntake();
			drive(0.1, 50);
			sylib::delay(175);
			ReverseIntake();
			drive(-0.1, 50);
			ForwardIntake();

			//* The robot shoots the two pre loads into the high goal
			AutonFlywheel(485);
			PIDTurn(degToRad(80));
			sylib::delay(5000);
			for(int i = 0; i < 5; i++) {
				Indexer();
				sylib::delay(1000);
			}

			Controller.print(1, 0, "Auton Completed");
			/*
				// turn('R', 0.2, 100);
				AutonFlywheel(0);
				while(!FRM.is_stopped()) sylib::delay(2);
				drive(1, 100);
				sylib::delay(1000);
				while(!FRM.is_stopped()) sylib::delay(2);
				drive(1, 100);
				sylib::delay(1000);
				while(!FRM.is_stopped()) sylib::delay(2);
				drive(1, 1000);
				sylib::delay(1000);
				while(!FRM.is_stopped()) sylib::delay(2);
				turn('L', 0.4, 100);
				while(!FRM.is_stopped()) sylib::delay(2);
				AutonFlywheel(300);
				sylib::delay(3000);
				for(int i = 0; i < 5; i++) Indexer();
				ToggleIntake();
				AutonFlywheel(0);
			*/
			break;
		case 4:
			//
				//* Last updated 2/11/23
			//
			
			Controller.print(0, 0, "Right Elims Auton");
			PIDMove(132, 108, false);
			PIDTurn(0);
			drive(0.4, 50);
			sylib::delay(1000);
			ReverseIntake();
			sylib::delay(300);
			ReverseIntake();
			sylib::delay(500);
			drive(-0.3, 50);
			sylib::delay(400);
			PIDTurn(degToRad(150));
			sylib::delay(500);
			AutonFlywheel(460);
			sylib::delay(3000);
			for(int i = 1; i <= 8; i++) {
				Indexer();
				sylib::delay(2500);
			}
			Controller.print(1, 0, "Auton Completed");
			break;
		case 5:
			Controller.print(0, 0, "Full AWP");
			Controller.print(1, 0, "Auton Completed");
			break;
		case 6:
			Controller.print(0, 0, "No Auton Selected");
			break;
		case 7:
			Controller.print(0, 0, "Programming Skills");

			//* Spins the bottom color roller
			drive(0.1, 50);
			SpinSkillsRoller();
			drive(-1.3, 50);
			pros::delay(2000);

			//* Spins the left color roller
			PIDMove(9, 42, false);
			sylib::delay(1000);
			drive(0.1, 50);
			SpinSkillsRoller();

			Expansion(); //!
			/*
				drive(-1, 50);
				PIDMove(36, 42, true);
				pros::delay(1000);
				PIDTurn(degToRad(330));
				AutonFlywheel(500);
				pros::delay(5000);
				for (int i = 0; i < 5; i++) {
					Indexer();
					pros::delay(2000);
				}
			*/

			Controller.print(1, 0, "Skills Complete");
			break;
	}
}