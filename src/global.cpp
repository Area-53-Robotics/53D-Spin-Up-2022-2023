#include "main.h"
#include "global.hpp"

/*
?   All motor, sensor, and pneumatic declarations are
?   declared here so that all files can access them.
*/

/*
* This object contains the values used for the flywheel
* control loop.
! Values initialized as "0" or "false" are not used in our
! flywheel controller.
*/
sylib::SpeedControllerInfo flywheel_motor_speed_controller (
    //* Exponential function to calculate kV based on target RPM
    [](double rpm){return rpm * (190 * std::pow(rpm, -1.36));},
    /*
    *   Proportional gain constant; As the difference between
    *   the target RPM and the current motor RPM increases,
    *   the voltage supplied to the motors also increases.
    */
    6,
    0,
    0,
    0,
    false,
    0,
    false,
    0,
    0,
    /*
    *   When the flywheel motors are 75 RPM away from the
    *   target, the flywheel motors will apply max voltage
    *   to the flywheel. This helps the flywheel overcome
    *   inertia loss after each shot.
    */
    750
);

/*
    Dead Ports: 3, 4, 5, 7, 11, 12, 19
    Best Battery: 13
*/

//* Controllers
pros::Controller Controller(pros::E_CONTROLLER_MASTER);
pros::Controller Controller2(pros::E_CONTROLLER_PARTNER);
//* Drive Motors
pros::Motor BLM(2, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor FLM(20, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor BRM(1, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor FRM(10, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_ROTATIONS);
pros::Motor IntakeMotor(13, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor IndexerMotor(6, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
//* Flywheel Motors
sylib::Motor FlywheelMotor1(16, 600, false, flywheel_motor_speed_controller);
sylib::Motor FlywheelMotor2(18, 600, false, flywheel_motor_speed_controller);

//* Drive Motor Groups
pros::Motor_Group LMotors({BLM, FLM});
pros::Motor_Group RMotors({BRM, FRM});

//* Inertial Sensor
pros::Imu IMU(9);

//* Tracking Wheel Encoders
pros::ADIEncoder LEncoder(7, 8, true);
pros::ADIEncoder REncoder(5, 6, false);
pros::ADIEncoder SEncoder(3, 4, false);

pros::ADIDigitalOut ExpansionPistons(2);

/*
*   Integer variable to represent the current game phase:
    1: Pre-Autonomous
    2: Autonomous
    3: Driver Control
*/
unsigned short int GamePhase = 1;