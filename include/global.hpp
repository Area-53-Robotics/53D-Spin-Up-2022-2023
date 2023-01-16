#include "api.h"
#include "pros/motors.h"
#include "competition_initialize.hpp"
#include "pros/rtos.hpp"

// enum class Auton {LeftRed};
// Auton auton = Auton::LeftRed;
// #pragma once

// lv_img_set_src(Logo.c, &Logo.c);
// lv_img_set_src

// Dead Ports: 3, 4, 5, 7, 11, 12, 19

inline pros::Controller Controller(pros::E_CONTROLLER_MASTER);
inline pros::Motor BLM(10, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_ROTATIONS);
inline pros::Motor FLM(20, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_ROTATIONS);
inline pros::Motor BRM(2, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_ROTATIONS);
inline pros::Motor FRM(1, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_ROTATIONS);
inline pros::Motor IntakeMotor(16, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
inline pros::Motor IndexerMotor(13, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);
inline pros::Motor FlywheelMotor1(6, pros::E_MOTOR_GEARSET_06, false);
inline pros::Motor FlywheelMotor2(18, pros::E_MOTOR_GEARSET_06, false);

inline short int LYAxis;
inline short int RYAxis;

inline bool UpdatingController = false;

inline unsigned short int GamePhase = 1;

inline unsigned short int autonSelect = 6;

/*
    1: Left Quals
    2: Right Quals
    3: Left Elims
    4: Right Elims
    5: Full Autonomous Win Point
    6: No Auton
    7: Programming Skills
*/

inline char Direction = 'N';
inline bool FlywheelSpinning = false;
inline bool intakeOn = false;

// /*
// Function v0
inline void ControllerDisplay() {
    Controller.clear();
    pros::delay(50);
    Controller.print(0, 0, "Driver Display");
    pros::delay(50);
    if (Direction == 'N') Controller.print(1, 0, "Direction: Normal");
    else if (Direction == 'R') Controller.print(1, 0, "Direction: Reverse");
    pros::delay(50);
    if (FlywheelSpinning) Controller.print(2, 0, "Flywheel: On");
    else if (!FlywheelSpinning) Controller.print(2, 0, "Flywheel: Off");
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
        IntakeMotor.move(127); // Max: 127
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
    } else if (FlywheelSpinning) {
        FlywheelMotor1.brake();
        FlywheelMotor2.brake();
        FlywheelSpinning = false;
    }
}

inline void Indexer() {
    IndexerMotor.move_absolute(45.0, 200);
    while (!((IndexerMotor.get_position() < 50) && (IndexerMotor.get_position() > 40))) {
        pros::delay(2);
    }
    IndexerMotor.move_absolute(0.0, 200);
    while (!((IndexerMotor.get_position() < 5) && (IndexerMotor.get_position() > -5))) {
        pros::delay(2);
    }
}

inline void Expansion() {
    IndexerMotor.move_absolute(130.0, 200);
    while (!((IndexerMotor.get_position() < 50) && (IndexerMotor.get_position() > 40))) {
        pros::delay(2);
    }
    Controller.rumble(".");
    pros::delay(50);
    Controller.clear();
    pros::delay(50);
    Controller.print(0, 0, "Expanded");
}
// */