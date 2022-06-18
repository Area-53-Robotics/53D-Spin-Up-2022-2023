#include "pros/apix.h"
#include "pros/motors.h"
#include "pros/motors.hpp"
#include "pros/rotation.hpp"

// lv_img_set_src(Logo.c, &Logo.c);
// lv_img_set_src

pros::Controller Controller(pros::E_CONTROLLER_MASTER);
pros::Motor BLM(1, pros::E_MOTOR_GEARSET_18, true);
pros::Motor FLM(2, pros::E_MOTOR_GEARSET_18, true);
pros::Motor BRM(3, pros::E_MOTOR_GEARSET_18, false);
pros::Motor FRM(4, pros::E_MOTOR_GEARSET_18, false);
pros::Rotation LEncoder(1, false);
pros::Rotation REncoder(2, false);
pros::Rotation MEncoder(3, false);

int LYAxis;
int RYAxis;

int GamePhase = 1;
int Page = 1;
int Line = 1;

bool AutonSelecting = false;
bool MotorChecking = false;

// Function v0
void CIDisplay() {
    if (!AutonSelecting && !MotorChecking && Line == 1) {
        Controller.print(0,0,"Pre-Autonomous");
        Controller.print(1,0,"> Auton Select");
        Controller.print(2,0,"  Motor Check");
    } else if (!AutonSelecting && !MotorChecking && Line == 2) {
        Controller.print(0,0,"Pre-Autonomous");
        Controller.print(1,0,"  Auton Select");
        Controller.print(2,0,"> Motor Check");
    }
}

void AutonSelect() {}

void MotorCheck() {
    if (Page == 1) {
        Controller.print(0,0,"BLM: ",BLM.get_temperature());
        Controller.print(1,0,"FLM: ",FLM.get_temperature());
        Controller.print(2,0,"BRM: ",BRM.get_temperature());
    } else if (Page == 2) {
        Controller.print(0,0,"FRM: ",FRM.get_temperature());
    }
}

// Button-Pressed Functions
void DownPressed() {
    if (GamePhase == 1 && !AutonSelecting && !MotorChecking && Line == 1) {
        Line = 2;
        CIDisplay();
    } else if (GamePhase == 1 && !AutonSelecting && !MotorChecking && Line == 2) {
        Line = 1;
        CIDisplay();
    }
}
void UpPressed() {
    if (GamePhase == 1 && !AutonSelecting && !MotorChecking && Line == 1) {
        Line = 2;
        CIDisplay();
    } else if (GamePhase == 1 && !AutonSelecting && !MotorChecking && Line == 2) {
        Line = 1;
        CIDisplay();
    }
}
void APressed() {
    if (GamePhase == 1 && !AutonSelecting && !MotorChecking && Line == 1) {
        AutonSelecting = true;
        AutonSelect();
    } else if (GamePhase == 1 && !AutonSelecting && !MotorChecking && Line == 2) {
        MotorChecking = true;
        MotorCheck();
    }
}
void BPressed() {
    if (AutonSelecting || MotorChecking) {
        AutonSelecting = false;
        MotorChecking = false;
        CIDisplay();
    }
}