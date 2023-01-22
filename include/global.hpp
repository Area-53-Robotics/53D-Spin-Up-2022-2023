#include "api.h"
#include "pros/misc.hpp"
#include "competition_initialize.hpp"

// enum class Auton {LeftRed};
// Auton auton = Auton::LeftRed;
// #pragma once

// lv_img_set_src(Logo.c, &Logo.c);
// lv_img_set_src

// Dead Ports: 3, 4, 5, 7, 11, 12, 19

inline pros::Controller Controller(pros::E_CONTROLLER_MASTER);
inline pros::Motor BLM(2, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_ROTATIONS);
inline pros::Motor FLM(8, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_ROTATIONS);
inline pros::Motor BRM(10, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_ROTATIONS);
inline pros::Motor FRM(1, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_ROTATIONS);
inline pros::Motor IntakeMotor(6, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
inline pros::Motor IndexerMotor(13, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
inline pros::Motor FlywheelMotor1(16, pros::E_MOTOR_GEARSET_06, false);
inline pros::Motor FlywheelMotor2(18, pros::E_MOTOR_GEARSET_06, false);
inline pros::Imu IMU(9);
inline pros::ADIEncoder LEncoder(1, 2, true);
// inline pros::ADIEncoder REncoder(3, 4, false);
inline pros::ADIEncoder SEncoder(5, 6, false);

inline short int LYAxis;
inline short int RYAxis;

inline bool UpdatingController = false;

inline unsigned short int GamePhase = 1;

inline unsigned short int autonSelect = 3;

/*
    1: Left Quals
    2: Right Quals
    3: Left Elims
    4: Right Elims
    5: Full Autonomous Win Point
    6: No Auton
    7: Programming Skills
*/

inline bool isReverse = false;
inline bool FlywheelSpinning = false;
inline bool intakeOn = false;

inline int FlywheelMotorSpeed = 363;

const double FiywheelRadius = 2.5;

// /*
// Function v0
inline void ControllerDisplay() {
    Controller.clear();
    pros::delay(50);
    if (isReverse == false) Controller.print(0, 0, "Direction: Normal");
    else if (isReverse == true) Controller.print(0, 0, "Direction: Reverse");
    pros::delay(50);
    if (FlywheelSpinning) Controller.print(1, 0, "Flywheel: On");
    else if (!FlywheelSpinning) Controller.print(1, 0, "Flywheel: Off");
    pros::delay(50);
    Controller.print(2, 0, "FlySpeed = %d", FlywheelMotorSpeed);
}

inline void waitUntilMoveAbsolute(pros::Motor Motor, double position, int velocity) {
    int count = 1;
    Motor.move_absolute(position, velocity);
    while (!((Motor.get_position() < (position + 5)) && (Motor.get_position() > (position - 5))) && count < 100) {
        count++;
        pros::delay(2);
    }
}

inline void drive(double length, int percent) {
    BLM.move_relative(length, percent);
    FLM.move_relative(length, percent);
    BRM.move_relative(length, percent);
    FRM.move_relative(length, percent);
}

inline void turn(char direction, double length, int percent) {
    if (direction == 'L') {
        BLM.move_relative(length * -1, percent);
        FLM.move_relative(length * -1, percent);
        BRM.move_relative(length, percent);
        FRM.move_relative(length, percent);
    } else if (direction == 'R') {
        BLM.move_relative(length, percent);
        FLM.move_relative(length, percent);
        BRM.move_relative(length * -1, percent);
        FRM.move_relative(length * -1, percent);
    }
}

inline void ToggleIntake() {
    if (!intakeOn) {
        IntakeMotor.move(127);
    }
    else if (intakeOn) {
        IntakeMotor.brake();
    }
    intakeOn = !intakeOn;
}

inline void BackwardsIntake() {
    if (!intakeOn) {
        IntakeMotor.move_velocity(-200);
    }
    else if (intakeOn) {
        IntakeMotor.brake();
    }
    intakeOn = !intakeOn;
}

inline void ToggleFlywheel(int velocity) {
    if (!FlywheelSpinning) {
        FlywheelSpinning = true;
        FlywheelMotor1.move_velocity(velocity);
        FlywheelMotor2.move_velocity(velocity);
        /*
        FlywheelMotor1.move_velocity(FlywheelMotorSpeed);
        FlywheelMotor2.move_velocity(FlywheelMotorSpeed);
        */
    } else if (FlywheelSpinning) {
        FlywheelMotor1.brake();
        FlywheelMotor2.brake();
        FlywheelSpinning = false;
    }
    ControllerDisplay();
}

inline void ToggleFlywheelSpeed() {
    if (FlywheelMotorSpeed == 363) FlywheelMotorSpeed = 600;
    else if (FlywheelMotorSpeed == 600) FlywheelMotorSpeed = 363;
    ControllerDisplay();
}

inline void Indexer() {
    waitUntilMoveAbsolute(IndexerMotor, 55, 200);
    waitUntilMoveAbsolute(IndexerMotor, 0, 200);
}

inline void Expansion() {
    waitUntilMoveAbsolute(IndexerMotor, 150, 200);
    // IndexerMotor.move_absolute(130.0, 200);
    Controller.rumble(".");
    pros::delay(50);
    Controller.clear();
    pros::delay(50);
    Controller.print(0, 0, "Expanded");
}

inline void SpinRoller() {
    ToggleIntake();
    pros::delay(333);
    ToggleIntake();
}

inline void FlySpeedInc100() {
    FlywheelMotorSpeed += 100;
    ControllerDisplay();
}

inline void FlySpeedDec100() {
    FlywheelMotorSpeed -= 100;
    ControllerDisplay();
}

inline void FlySpeedInc10() {
    FlywheelMotorSpeed += 10;
    ControllerDisplay();
}

inline void FlySpeedDec10() {
    FlywheelMotorSpeed -= 10;
    ControllerDisplay();
}
// */