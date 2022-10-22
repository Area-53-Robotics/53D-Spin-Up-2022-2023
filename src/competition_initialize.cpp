#include "main.h"

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
	CIDisplay();
	while (true) {
		if(Controller.get_digital_new_press(DIGITAL_DOWN)) DownPressed();
		if(Controller.get_digital_new_press(DIGITAL_UP)) UpPressed();
		if(Controller.get_digital_new_press(DIGITAL_A)) APressed();
		if(Controller.get_digital_new_press(DIGITAL_B)) BPressed();

		pros::delay(20);
	}
}