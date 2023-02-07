#include "api.h"
#include "utilHeaders/misc.hpp"
#include "competition_initialize.hpp"
#include "sylib/sylib.hpp"

// enum class Auton {LeftRed};
// Auton auton = Auton::LeftRed;
// #pragma once

// lv_img_set_src(Logo.c, &Logo.c);
// lv_img_set_src

// Dead Ports: 3, 4, 5, 7, 11, 12, 19

inline sylib::SpeedControllerInfo flywheel_motor_speed_controller (
    [](double rpm){return 5;}, // kV function
    1, // kP
    1, // kI
    1, // kD
    0, // kH
    false, // anti-windup enabled
    0, // anti-windup range
    false, // p controller bounds threshold enabled
    0, // p controller bounds cutoff enabled
    1, // kP2 for when over threshold
    0 // range to target to apply max voltage
);

inline pros::Controller Controller(pros::E_CONTROLLER_MASTER);
inline pros::Motor BLM(2, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_ROTATIONS);
inline pros::Motor FLM(8, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_ROTATIONS);
inline pros::Motor BRM(10, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_ROTATIONS);
inline pros::Motor FRM(1, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_ROTATIONS);
inline pros::Motor IntakeMotor(6, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
inline pros::Motor IndexerMotor(13, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
inline sylib::Motor FlywheelMotor1(16, 600, false);
inline sylib::Motor FlywheelMotor2(18, 600, false);

inline pros::Imu IMU(9);
inline pros::ADIEncoder LEncoder(7, 8, true);
// inline pros::ADIEncoder REncoder(3, 4, false);
inline pros::ADIEncoder SEncoder(1, 2, false);

inline short int LYAxis;
inline short int RYAxis;

inline bool UpdatingController = false;

inline unsigned short int GamePhase = 1;

/*
    1: Left Quals
    2: Right Quals
    3: Left Elims
    4: Right Elims
    5: Full Autonomous Win Point
    6: No Auton
    7: Programming Skills
*/
inline unsigned short int autonSelect = 3;

inline bool isReverse = false;
inline bool FlywheelSpinning = false;
inline bool intakeOn = false;

inline int FlywheelMotorSpeed = 363;

const double FlywheelRadius = 2.5;

// /*
// Function v0
inline void ControllerDisplay() {
    Controller.clear();
    sylib::delay(50);
    if (isReverse == false) Controller.print(0, 0, "Direction: Normal");
    else if (isReverse == true) Controller.print(0, 0, "Direction: Reverse");
    sylib::delay(50);
    if (FlywheelSpinning) Controller.print(1, 0, "Flywheel: On");
    else if (!FlywheelSpinning) Controller.print(1, 0, "Flywheel: Off");
    sylib::delay(50);
    Controller.print(2, 0, "FlySpeed = %d", FlywheelMotorSpeed);
}

inline void waitUntilMoveAbsolute(pros::Motor Motor, double position, int velocity) {
    int count = 1;
    Motor.move_absolute(position, velocity);
    while (!((Motor.get_position() < (position + 5)) && (Motor.get_position() > (position - 5))) && count < 1000) {
        count++;
        sylib::delay(2);
    }
}

inline void drive(double length, int velocity) {
    /*
    BLM.set_position_target_relative(normalMotorRevToTicks(length), velocity);
    FLM.set_position_target_relative(normalMotorRevToTicks(length), velocity);
    BRM.set_position_target_relative(normalMotorRevToTicks(length), velocity);
    FRM.set_position_target_relative(normalMotorRevToTicks(length), velocity);
    */
    BLM.move_relative(length, 200);
    FLM.move_relative(length, 200);
    BRM.move_relative(length, 200);
    FRM.move_relative(length, 200);
}

inline void turn(char direction, double length, int velocity) {
    /*
    if (direction == 'L') {
        BLM.set_position_target_relative(normalMotorRevToTicks(length * -1), velocity);
        FLM.set_position_target_relative(normalMotorRevToTicks(length * -1), velocity);
        BRM.set_position_target_relative(normalMotorRevToTicks(length), velocity);
        FRM.set_position_target_relative(normalMotorRevToTicks(length), velocity);
    } else if (direction == 'R') {
        BLM.set_position_target_relative(normalMotorRevToTicks(length), velocity);
        FLM.set_position_target_relative(normalMotorRevToTicks(length), velocity);
        BRM.set_position_target_relative(normalMotorRevToTicks(length * -1), velocity);
        FRM.set_position_target_relative(normalMotorRevToTicks(length * -1), velocity);
    }
    */
    if (direction == 'L') {
        BLM.move_relative(length * -1, 200);
        FLM.move_relative(length * -1, 200);
        BRM.move_relative(length, 200);
        FRM.move_relative(length, 200);
    } else if (direction == 'R') {
        BLM.move_relative(length, 200);
        FLM.move_relative(length, 200);
        BRM.move_relative(length * -1, 200);
        FRM.move_relative(length * -1, 200);
    }
}
// */