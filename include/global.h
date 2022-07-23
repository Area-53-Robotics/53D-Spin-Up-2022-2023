#include "pros/adi.hpp"
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
pros::ADIEncoder LEncoder(1, 2, false);
pros::ADIEncoder REncoder(3, 4, true);
pros::ADIEncoder MEncoder(5, 6, false);

int LYAxis;
int RYAxis;

int GamePhase = 1;
int Page = 1;
int Line = 1;

bool AutonSelecting = false;
bool MotorChecking = false;

int autonSelect = 5;
/*
    1: Left Quals
    2: Right Quals
    3: Left Elims
    4: Right Elims
    5: No Auton
    6: Programming Skills
*/

// Function v0
void CIDisplay() {
    Controller.clear();
    if (!AutonSelecting && !MotorChecking && Line == 1) {
        Controller.print(0,0,"Pre-Autonomous Menu");
        Controller.print(1,0,"> Auton Select");
        Controller.print(2,0,"  Motor Check");
    } else if (!AutonSelecting && !MotorChecking && Line == 2) {
        Controller.print(0,0,"Pre-Autonomous Menu");
        Controller.print(1,0,"  Auton Select");
        Controller.print(2,0,"> Motor Check");
    }
}

void AutonSelect() {
    Controller.clear();
    if (Line == 1) {
        switch (autonSelect) {
            case 1:
                Controller.print(0, 0, "> X Left Quals");
                Controller.print(1, 0, "    Right Quals");
                Controller.print(2, 0, "    Left Elims");
                break;
            case 2:
                Controller.print(0, 0, ">   Left Quals");
                Controller.print(1, 0, "  X Right Quals");
                Controller.print(2, 0, "    Left Elims");
                break;
            case 3:
                Controller.print(0, 0, ">   Left Quals");
                Controller.print(1, 0, "    Right Quals");
                Controller.print(2, 0, "  X Left Elims");
                break;
            default:
                Controller.print(0, 0, ">   Left Quals");
                Controller.print(1, 0, "    Right Quals");
                Controller.print(2, 0, "    Left Elims");
                break;
        }
    } else if (Line == 2) {
        switch (autonSelect) {
            case 1:
                Controller.print(0, 0, "  X Left Quals");
                Controller.print(1, 0, ">   Right Quals");
                Controller.print(2, 0, "    Left Elims");
                break;
            case 2:
                Controller.print(0, 0, "    Left Quals");
                Controller.print(1, 0, "> X Right Quals");
                Controller.print(2, 0, "    Left Elims");
                break;
            case 3:
                Controller.print(0, 0, "    Left Quals");
                Controller.print(1, 0, ">   Right Quals");
                Controller.print(2, 0, "  X Left Elims");
                break;
            default:
                Controller.print(0, 0, "    Left Quals");
                Controller.print(1, 0, ">   Right Quals");
                Controller.print(2, 0, "    Left Elims");
                break;
        }
    } else if (Line == 3) {
        switch (autonSelect) {
            case 1:
                Controller.print(0, 0, "  X Left Quals");
                Controller.print(1, 0, "    Right Quals");
                Controller.print(2, 0, ">   Left Elims");
                break;
            case 2:
                Controller.print(0, 0, "    Left Quals");
                Controller.print(1, 0, "  X Right Quals");
                Controller.print(2, 0, ">   Left Elims");
                break;
            case 3:
                Controller.print(0, 0, "    Left Quals");
                Controller.print(1, 0, "    Right Quals");
                Controller.print(2, 0, "> X Left Elims");
                break;
            default:
                Controller.print(0, 0, "    Left Quals");
                Controller.print(1, 0, "    Right Quals");
                Controller.print(2, 0, ">   Left Elims");
                break;
        }
    } else if (Line == 4) {
        switch (autonSelect) {
            case 4:
                Controller.print(0, 0, "> X Right Elims");
                Controller.print(1, 0, "    No Auton");
                Controller.print(2, 0, "    P-Skills");
                break;
            case 5:
                Controller.print(0, 0, ">   Right Elims");
                Controller.print(1, 0, "  X No Auton");
                Controller.print(2, 0, "    P-Skills");
                break;
            case 6:
                Controller.print(0, 0, ">   Right Elims");
                Controller.print(1, 0, "    No Auton");
                Controller.print(2, 0, "  X P-Skills");
                break;
            default:
                Controller.print(0, 0, ">   Right Elims");
                Controller.print(1, 0, "    No Auton");
                Controller.print(2, 0, "    P-Skills");
                break;
        }
    } else if (Line == 5) {
        switch (autonSelect) {
            case 4:
                Controller.print(0, 0, "  X Right Elims");
                Controller.print(1, 0, ">   No Auton");
                Controller.print(2, 0, "    P-Skills");
                break;
            case 5:
                Controller.print(0, 0, "    Right Elims");
                Controller.print(1, 0, "> X No Auton");
                Controller.print(2, 0, "    P-Skills");
                break;
            case 6:
                Controller.print(0, 0, "    Right Elims");
                Controller.print(1, 0, ">   No Auton");
                Controller.print(2, 0, "  X P-Skills");
                break;
            default:
                Controller.print(0, 0, "    Right Elims");
                Controller.print(1, 0, ">   No Auton");
                Controller.print(2, 0, "    P-Skills");
                break;
        }
    } else if (Line == 6) {
        switch (autonSelect) {
            case 4:
                Controller.print(0, 0, "  X Right Elims");
                Controller.print(1, 0, "    No Auton");
                Controller.print(2, 0, ">   P-Skills");
                break;
            case 5:
                Controller.print(0, 0, "    Right Elims");
                Controller.print(1, 0, "  X No Auton");
                Controller.print(2, 0, ">   P-Skills");
                break;
            case 6:
                Controller.print(0, 0, "    Right Elims");
                Controller.print(1, 0, "    No Auton");
                Controller.print(2, 0, "> X P-Skills");
                break;
            default:
                Controller.print(0, 0, "    Right Elims");
                Controller.print(1, 0, "    No Auton");
                Controller.print(2, 0, ">   P-Skills");
                break;
        }
    }
}

void MotorCheck() {
    Controller.clear();
    if (Page == 1) {
        Controller.print(0,0,"BLM: ",BLM.get_temperature()," C");
        Controller.print(1,0,"FLM: ",FLM.get_temperature()," C");
        Controller.print(2,0,"BRM: ",BRM.get_temperature()," C");
    } else if (Page == 2) {
        Controller.print(0,0,"FRM: ",FRM.get_temperature()," C");
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
    } else if (GamePhase == 1 && AutonSelecting && !MotorChecking && (Line < 7)) {
        Line++;
        AutonSelect();
    } else if (GamePhase == 1 && !AutonSelecting && MotorChecking && (Page == 1)) {
        Page = 2;
        AutonSelect();
    }
}

void UpPressed() {
    if (GamePhase == 1 && !AutonSelecting && !MotorChecking && Line == 1) {
        Line = 2;
        CIDisplay();
    } else if (GamePhase == 1 && !AutonSelecting && !MotorChecking && Line == 2) {
        Line = 1;
        CIDisplay();
    } else if (GamePhase == 1 && AutonSelecting && !MotorChecking && (Line > 1)) {
        Line--;
        AutonSelect();
    } else if (GamePhase == 1 && !AutonSelecting && MotorChecking && (Page == 2)) {
        Page = 1;
        AutonSelect();
    }
}

void APressed() {
    if (GamePhase == 1 && !AutonSelecting && !MotorChecking && Line == 1) {
        AutonSelecting = true;
        Line = autonSelect;
        AutonSelect();
    } else if (GamePhase == 1 && !AutonSelecting && !MotorChecking && Line == 2) {
        MotorChecking = true;
        Page = 1;
        MotorCheck();
    } else if (GamePhase == 1 && AutonSelecting && !MotorChecking) {
        switch (Line) {
            case 1: autonSelect = 1; break;
            case 2: autonSelect = 2; break;
            case 3: autonSelect = 3; break;
            case 4: autonSelect = 4; break;
            case 5: autonSelect = 5; break;
            case 6: autonSelect = 6; break;
        }
        AutonSelect();
    }
}

void BPressed() {
    if (GamePhase == 1 && AutonSelecting) {
        AutonSelecting = false;
        Line = 2;
        CIDisplay();
    } else if (GamePhase == 1 && MotorChecking) {
        MotorChecking = false;
        Line = 1;
        CIDisplay();
    }
}