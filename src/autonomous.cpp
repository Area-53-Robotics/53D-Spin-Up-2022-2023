#include "main.h"
#include "pros/misc.hpp"
#include "pros/rtos.hpp"
#include "sylib/system.hpp"

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
	GamePhase = 7;
	if (pros::competition::is_connected()) autonSelect = 2;
	Controller.clear();
	switch (autonSelect) {
		case 1:
			//* Gets roller & shoots 2 discs into low goal
			//* Last updated 1/21/23
			Controller.print(0, 0, "Ur mom weighs auton");
			BackwardsIntake();
			drive(0.1, 50);
			sylib::delay(250);
			BackwardsIntake();
			drive(-0.50, 50);
			while(!FRM.is_stopped()) sylib::delay(2);
			sylib::delay(1000);
			turn('R', 0.75,50);
			while(!FRM.is_stopped()) sylib::delay(2);
			sylib::delay(2000);
			ToggleIntake();
			sylib::delay(500);
			ToggleFlywheel(410);
			sylib::delay(4000);
			Indexer();
			while(!IndexerMotor.is_stopped()) sylib::delay(2);
			sylib::delay(1000);
			Indexer();
			while(!IndexerMotor.is_stopped()) sylib::delay(2);
			Indexer();
			while(!IndexerMotor.is_stopped()) sylib::delay(2);
			Indexer();
			while(!IndexerMotor.is_stopped()) sylib::delay(2);
			ToggleIntake();
			sylib::delay(50);
			ToggleFlywheel(400); // actually turns it off
			sylib::delay(1000);
			turn('L', 0.375, 50);
			while(!FRM.is_stopped()) sylib::delay(2);
			drive(-0.5, 50);
			while(!FRM.is_stopped()) sylib::delay(2);
			/*
			turn('R', 4, 50);
			// drive(3, 50);
			*/
			Controller.print(1, 0, "Auton Completed");
			break;
		case 2:
			//* Moves toward & turns roller, shoots 2 discs into low goal
			//* Last updated 2/11/23
			Controller.print(0, 0, "Right Quals Auton");
			drive(1.4, 50);
			sylib::delay(1000);
			turn('R', 0.65, 50);
			sylib::delay(1000);
			drive(0.4, 50);
			sylib::delay(1000);
			BackwardsIntake();
			sylib::delay(300);
			BackwardsIntake();
			sylib::delay(500);
			drive(-0.3, 50);
			sylib::delay(1400);
			turn('L', 0.7, 50);
			sylib::delay(1500);
			ToggleFlywheel(350);
			sylib::delay(3000);
			for(int i = 0; i < 8; i++) {
				Indexer();
				sylib::delay(1200);
			}
			Controller.print(0,0,"Auton Completed");
			break;
		case 3:
			//! High Goal Auton - not tested
			//* Last updated 1/21/23
			Controller.print(0, 0, "Left Elims Auton");
			BackwardsIntake();
			drive(0.1, 50);
			sylib::delay(175);
			BackwardsIntake();
			drive(-0.1, 50);
			while(!FRM.is_stopped()) sylib::delay(2);
			/*
			ToggleIntake();
			ToggleFlywheel(485);
			turn('R', 0.05, 100);
			sylib::delay(5000);
			while(!FRM.is_stopped()) sylib::delay(2);
			for(int i = 0; i < 5; i++) {
				Indexer();
				FlywheelMotor1.move_voltage(FlywheelMotor1.get_target_velocity() - 5);
				FlywheelMotor2.move_voltage(FlywheelMotor2.get_target_velocity() - 5);
				sylib::delay(1000);
			}
			*/
			/*
			// turn('R', 0.2, 100);
			ToggleFlywheel(0);
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
			ToggleFlywheel(300);
			sylib::delay(3000);
			for(int i = 0; i < 5; i++) Indexer();
			ToggleIntake();
			ToggleFlywheel(0);
			Controller.print(1, 0, "Auton Completed");
			*/
			break;
		case 4:
			//! High Goal Auton - needs flywheel speed adjusted
			//* Last updated 2/11/23
			Controller.print(0, 0, "Right Elims Auton");
			drive(1.4, 50);
			sylib::delay(1000);
			turn('R', 0.65, 50);
			sylib::delay(1000);
			drive(0.4, 50);
			sylib::delay(1000);
			BackwardsIntake();
			sylib::delay(300);
			BackwardsIntake();
			sylib::delay(500);
			drive(-0.3, 50);
			sylib::delay(400);
			turn('L', 0.09, 50);
			sylib::delay(500);
			// 409 is a good number
			ToggleFlywheel(460);
			// shoot in goal
			sylib::delay(3000);
			for(int i = 1; i <= 8; i++) {
				Indexer();
				std::cout << "Shot #: " << i << "; Power: " << FlywheelMotor1.get_actual_velocity() << std::endl;
				sylib::delay(2500);
			}
			Controller.print(1, 0, "Auton Completed");
			break;
		case 5:
			Controller.print(0, 0, "Full AWP");
			//* Will end up being mostly made of left elims auton values
			//* Last updated ---
			Controller.print(1, 0, "Auton Completed");
			break;
		case 6:
			Controller.print(0, 0, "No Auton Selected");
			break;
		case 7:
			Controller.print(0, 0, "Programming Skills");
			//* Last updated 2/7/23
			BackwardsIntake();
			drive(0.35, 50);
			sylib::delay(500);
			BackwardsIntake();
			drive(-1.2, 50);
			while(!FRM.is_stopped()) sylib::delay(2);
			sylib::delay(1000);
			turn('R', 0.65,50);
			while(!FRM.is_stopped()) sylib::delay(2);
			sylib::delay(2000);
			drive(1, 50);
			BackwardsIntake();
			sylib::delay(500);
			BackwardsIntake();
			sylib::delay(1000);
			drive(1, 50);
			sylib::delay(2200);
			ToggleIntake();
			sylib::delay(500);
			drive(-1, 50);
			sylib::delay(3000);
			turn('R', 0.2, 50);
			sylib::delay(1000);
			ToggleFlywheel(430);
			sylib::delay(4000);
			Indexer();
			while(!IndexerMotor.is_stopped()) sylib::delay(2);
			sylib::delay(1000);
			Indexer();
			while(!IndexerMotor.is_stopped()) sylib::delay(2);
			Indexer();
			while(!IndexerMotor.is_stopped()) sylib::delay(2);
			Indexer();
			while(!IndexerMotor.is_stopped()) sylib::delay(2);
			ToggleIntake();
			sylib::delay(50);
			ToggleFlywheel(420); // actually turns it off
			sylib::delay(1000);
			turn('L', 0.375, 50);
			while(!FRM.is_stopped()) sylib::delay(2);
			sylib::delay(1000);
			Expansion();
			drive(-0.5, 50);
			while(!FRM.is_stopped()) sylib::delay(2);
			/*
				drive(0.1,50);
				BackwardsIntake();
				sylib::delay(500); // originally 500 msec
				BackwardsIntake();
				drive(-0.2, 50);
				sylib::delay(1000);
				turn('R', 0.7,50);
				sylib::delay(1000);
				drive(3, 50); // big big important
				sylib::delay(1000);
				turn('R', 0.1, 50);
				ToggleFlywheel(363); // og 475
				sylib::delay(6000);
				Indexer();
				sylib::delay(2000);
				Indexer();
				sylib::delay(2000);
				Indexer();
				sylib::delay(2000);
				Indexer();
				Expansion();
			*/
			/*
				PIDMove(36, 8, false); // Moves towards roller
				SpinSkillsRoller();
				PIDMove(36, 12, true); // Moves to middle of tile
				ToggleIntake(); // Turns on intake
				PIDTurnTo(12, 12, false); // Turns to bottom left disc
				PIDMove(12, 12, false); // Moves to disc & intakes it
				sylib::delay(4000); // Gives time for the disc to intake
				ToggleIntake(); // Turns off intake
				PIDMove(36, 12, true);
				ToggleIntake(); // Turns on intake for shooting
				SkillsAutoAim(); // Primes flywheel for shooting into bottom high goal
				for(int i = 0; i < 5; i++) Indexer(); // Shoots pre-loads + intaked disc into bottom high goal
				ToggleFlywheel(0); // Turns off flywheel
				PIDMove(36, 36, false); // Moves towards & starts intaking bottom left disc stack
				sylib::delay(3000); // Gives time for discs to intake
				PIDMove(36, 48, false); // Intakes discs that fell off the stack
				sylib::delay(3000); // Gives time for discs to intake
				SkillsAutoAim(); // Primes flywheel for shooting into top high goal
				for(int i = 0; i < 5; i++) Indexer(); // Shoots intaked disc stack into top high goal
				ToggleFlywheel(0); // Turns off flywheel
				ToggleIntake(); // Turns off intake
				PIDMove(36, 36, false); // Aligns bot with second disc stack
				PIDMove(60, 36, false); // Intakes second disc stack
				sylib::delay(3000); // Gives time for discs to intake
				PIDMove(72, 36, false); // Intakes discs that fell off the stack
				sylib::delay(3000); // Gives time for intaked discs
				SkillsAutoAim(); // Primes flywheel for shooting into bottom high goal
				for(int i = 0; i < 5; i++) Indexer(); // Shoots intaked disc stack into bottom high goal
				ToggleIntake(); // Turns off intake
				ToggleFlywheel(0); // Turns off flywheel
				PIDMove(60, 36, true); // Aligns diagonally with the right disc line
				ToggleIntake(); // Turns on intake
				PIDMove(84, 60, false); // Intakes first diagonal disc
				PIDMove(96, 72, false); // Intakes second diagonal disc
				PIDMove(108, 84, false); // Intakes third diagonal disc
				SkillsAutoAim();// Primes flywheel for shooting into bottom high goal
				for(int i = 0; i < 5; i++) Indexer(); // Shoots intaked discs into bottom high goal
				ToggleIntake(); // Turns off intake
				ToggleFlywheel(0); // Turns off flywheel
				PIDMove(132, 112, false); // Gets robot at the same Y as the roller
				PIDMove(135, 112, false); // Gets robot right next to the right roller
				SpinSkillsRoller(); // Spins the roller
				PIDMove(135, 112, true); // Reversing previous movements
				PIDMove(132, 108, false); // Gets robot in the middle of the tile next to the roller
				ToggleIntake();
				PIDMove(108, 108, false); // Starts intaking top right disc stack
				sylib::delay(3000); // Gives time for intaked discs
				PIDMove(96, 108, false); // Intakes discs that fell of the stack
				sylib::delay(3000); // Gives time for intaked discs
				SkillsAutoAim();
				for(int i = 0; i < 5; i++) Indexer(); // Shoots intaked disc stack into ? high goal
				ToggleIntake(); // Turns intake off
				ToggleFlywheel(0); // Turns Flywheel off
				PIDMove(108, 108, false);
				ToggleIntake(); // Turns intake on
				PIDMove(120, 120, false); // Intakes 2nd to top right disc
				PIDMove(132, 132, false); // Intakes top right disc
				sylib::delay(3000); // Gives time for intaked discs
				PIDMove(108, 108, true); // Aligns on the X coordinate with roller
				PIDMove(108, 135, false); // Puts the robot against the roller
				SpinSkillsRoller(); // Spins the roller
				PIDMove(108, 108, true);
			*/

			Controller.print(1, 0, "Skills Complete");
			break;
	}
}