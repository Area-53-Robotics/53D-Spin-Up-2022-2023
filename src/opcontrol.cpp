#include "main.h"

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
	/*
	*	Starts driver control with the flywheel off and the
	*	flywheel motor speed at 340 RPM.
	*/
	FlywheelSpinning = false;
	FlywheelMotorSpeed = 340;

	//* Initializes the driver controller display
	MainControllerDisplay();
	Controller.rumble(".");

	//* Initializes controller button boolean variables
	bool L1Button;
	bool L2Button;
	bool R1Button;
	bool R2Button;
	bool DownButton;
	bool BButton;

	//
		if(!pros::competition::is_connected()) {
			// competition_initialize();
			autonSelect = 1;
			setStartingOdomValues();
			autonomous();
		}

		/*
		FlywheelMotor1.set_velocity_custom_controller(450);
		FlywheelMotor2.set_velocity_custom_controller(450);
		*/

		// PIDMove(0, 72, false);
		// PIDTurn(degToRad(120));

		// TODO: Test OP Control Flywheel with new control loop & increase kP as needed
		// ToggleFlywheel(350);
		// targetFWMSpeed = 350;
	//
	while (true) {

		/*
		*	Sets the button booleans to represent whether their
		*	respective buttons are being pressed or not
		*/
		L1Button = Controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
		L2Button = Controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2);
		R1Button = Controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
		R2Button = Controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2);
		DownButton = Controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN);
		BButton = Controller.get_digital(pros::E_CONTROLLER_DIGITAL_B);

		//* Moves the motors according to the joystick values
		setDriveMotors();

		//* When Button X is pressed, the direction of the robot is switched
		if (Controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) DirectionToggle();
		//* When Button B is pressed while the down button is pressed the expansion mechanism is triggered
		if (Controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B) && DownButton) Expansion();
		//* When Button A is pressed the target speed of the flywheel motors is switched
		if (Controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) ToggleFlywheelSpeed();
		//* When Button Y is pressed the roller spins enough to turn a color roller 1/3 of its circumference
		if (Controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) SpinRoller();
		//* When Button R1 is pressed and the indexer has stopped moving, the indexer rotates 360 degrees
		if (Controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1) && IndexerMotor.is_stopped()) Indexer();
		//* When Button R2 is pressed the flywheel is toggled from off to on and vice-versa
		if (Controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) ToggleFlywheelStatus();
		//* When Button Left is pressed the target flywheel motor speed is set to 600 RPM
		if (Controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) FlywheelMotorSpeed = 600;

		//* Pressing all the bumper buttons at once kills the odometry background task
		if ((Controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)
			|| Controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2) 
			|| Controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)
			|| Controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2))
			&& L1Button && L2Button && R1Button && R2Button) {
				odomKillSwitch();
			}
		
		/*
		* If the L1 button is being held, the intake will move at full power in the normal direction
		* If the L2 button is being held, the intake will move at full power in the reverse direction
		* Otherwise, the intake will not move
		*/
		if (Controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
			IntakeMotor.move(127);
			intakeStatus = 1;
		}
		else if (Controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
			IntakeMotor.move(-127);
			intakeStatus = 2;
		}
		else {
			IntakeMotor.brake();
			intakeStatus = 0;
		}
		

		/*
			if (Controller2.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) DecDiscCount();
			if (Controller2.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) IncDiscCount();
			if (Controller2.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_A)) MotorTempDisplay1();
			if (Controller2.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_X)) MotorTempDisplay2();
			if (Controller2.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) MotorTempDisplay3();

			if(Controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) FlySpeedInc100();
			if(Controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) FlySpeedDec100();
			if(Controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) FlySpeedInc10();
			if(Controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) FlySpeedDec10();
		*/
	
		sylib::delay(20);

	}
}