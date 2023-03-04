#include "main.h"

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "I was pressed!" and nothing.
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "Hello 53D!");

	pros::lcd::register_btn1_cb(on_center_button);

	sylib::initialize();

	/*
	*	Plays an intro gif on the brain while the inertial sensor
	*	calibrates
	*/
	lv_obj_t* obj = lv_obj_create(lv_scr_act(), NULL);
	lv_obj_set_size(obj, 480, 270);
	lv_obj_set_style(obj, &lv_style_transp); // make the container invisible
	lv_obj_align(obj, NULL, LV_ALIGN_CENTER, 0, 0);
	Gif gif("/usd/JJBA.gif", obj);
	IMU.reset(true);
	pros::delay(5250);
	gif.clean();

	//* Resets all of the tracking wheel encoders
	LEncoder.reset();
	REncoder.reset();
	SEncoder.reset();

	/*
	*	Sets the odometry and flywheel control tasks to run in the
	*	background of the program
	*/
	pros::Task Odometry(runOdometry);
	pros::Task FlywheelControl(FlywheelController);

	//
		// pros::Task OdomDataCollection(odomDataCollection);
		// pros::Task dataCollection(printTestValue);
	//

}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
	/*
	*	Plays a gif on the brain during the disabled phase
	*/
	if (GamePhase == 3) {
		lv_obj_t* obj = lv_obj_create(lv_scr_act(), NULL);
		lv_obj_set_size(obj, 272, 350);
		lv_obj_set_style(obj, &lv_style_transp); // make the container invisible
		lv_obj_align(obj, NULL, LV_ALIGN_CENTER, 0, 0);
		Gif gif("/usd/Alien.gif", obj);
	}
}