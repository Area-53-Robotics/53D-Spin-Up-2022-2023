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
    BLM.set_is_reversed(true);
	FLM.set_is_reversed(true);
    IntakeMotor.set_is_reversed(true);
    IndexerMotor.set_is_reversed(true);
    */

	IMU.reset(true);

	autonSelect = 7;

	switch (autonSelect) {
        case 1:
            // Left Quals
            posX = 16;
            posY = 9;
            IMU.set_heading(-90);
            break;
        case 2:
            // Right Quals
            posX = 135;
            posY = 138;
            IMU.set_heading(-180);
            break;
        case 3:
            // Left Elims
            posX = 16;
            posY = 9;
            IMU.set_heading(-90);
            break;
        case 4:
            // Right Elims
            posX = 135;
            posY = 138;
            IMU.set_heading(-180);
            break;
        case 5:
            // Full Autonomous Win Point
            posX = 135;
            posY = 138;
            IMU.set_heading(-180);
            break;
        case 6:
            // No Auton
            posX = 135;
            posY = 138;
            IMU.set_heading(-180);
            break;
        case 7:
            // Programming Skills
            posX = 16;
            posY = 9;
            IMU.set_heading(-90);
            break;
    }
    orientation = degToRad(360 - IMU.get_heading());
	simplifyAngle(orientation);
    lastOrientation = orientation;
    avgTheta = orientation + (deltaTheta / 2);
	
	// pros::Task Odometry(runOdometry);
	// pros::Task OdomDataCollection(odomDataCollection);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}