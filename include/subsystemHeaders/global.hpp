#include "api.h"
#include "pros/motors.h"
#include "pros/motors.hpp"
#include "pros/rtos.hpp"
// enum class Auton {LeftRed};
// Auton auton = Auton::LeftRed;
// #pragma once

// lv_img_set_src(Logo.c, &Logo.c);
// lv_img_set_src

// Dead Ports: 3, 5, 11, 4, 5, 7

inline pros::Controller Controller(pros::E_CONTROLLER_MASTER);
inline pros::Motor BLM(2, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_ROTATIONS);
inline pros::Motor FLM(20, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_ROTATIONS);
inline pros::Motor BRM(1, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_ROTATIONS);
inline pros::Motor FRM(12, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_ROTATIONS);
inline pros::Motor IntakeMotor(6, pros::E_MOTOR_GEARSET_36, true, pros::E_MOTOR_ENCODER_DEGREES);
inline pros::Motor ExpansionMotor(8, pros::E_MOTOR_GEARSET_06, true);
inline pros::Motor IndexerMotor(17, pros::E_MOTOR_GEARSET_18, false);
inline pros::Motor FlywheelMotor1(19, pros::E_MOTOR_GEARSET_18, false);
inline pros::Motor FlywheelMotor2(18, pros::E_MOTOR_GEARSET_18, false);
inline pros::ADIEncoder LEncoder(1, 2, false);
inline pros::ADIEncoder REncoder(3, 4, true);
inline pros::ADIEncoder MEncoder(5, 6, false);

inline short int LYAxis;
inline short int RYAxis;

inline bool UpdatingController = false;
extern bool intake;

inline unsigned short int GamePhase = 1;
inline unsigned short int Page = 1;
inline unsigned short int Line = 1;
 
inline bool AutonSelecting = false;
inline bool MotorChecking = false;
inline bool KeybindChecking = false;
inline bool NotesChecking = false;

inline unsigned short int autonSelect = 5;

inline char Direction = 'N';
inline bool FlywheelSpinning = false;

/*
    1: Left Quals
    2: Right Quals
    3: Left Elims
    4: Right Elims
    5: No Auton
    6: Programming Skills
*/

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

inline void CIDisplay() {
    Controller.clear();
    pros::delay(50);
    if (!AutonSelecting && !MotorChecking) {
        if (Line == 1) {
            Controller.print(0,0,"Pre-Auton Menu");
            pros::delay(50);
            Controller.print(1,0,"> Auton Select");
            pros::delay(50);
            Controller.print(2,0,"  Motor Check");
            pros::delay(50);
        } else if (Line == 2) {
            Controller.print(0,0,"Pre-Auton Menu");
            pros::delay(50);
            Controller.print(1,0,"  Auton Select");
            pros::delay(50);
            Controller.print(2,0,"> Motor Check");
            pros::delay(50);
        } else if (Line == 3) {
            Controller.print(0, 0, "> Keybindings");
            pros::delay(50);
            Controller.print(1, 0, "  Notes");
            pros::delay(50);
        } else if (Line == 4) {
            Controller.print(0, 0, "  Keybindings");
            pros::delay(50);
            Controller.print(1, 0, "> Notes");
        }
    }

}

inline void AutonSelect() {
    Controller.clear();
    pros::delay(50);
    if (Line == 1) {
        switch (autonSelect) {
            case 1:
                Controller.print(0, 0, "> X Left Quals");
                pros::delay(50);
                Controller.print(1, 0, "    Right Quals");
                pros::delay(50);
                Controller.print(2, 0, "    Left Elims");
                pros::delay(50);
                break;
            case 2:
                Controller.print(0, 0, ">   Left Quals");
                pros::delay(50);
                Controller.print(1, 0, "  X Right Quals");
                pros::delay(50);
                Controller.print(2, 0, "    Left Elims");
                pros::delay(50);
                break;
            case 3:
                Controller.print(0, 0, ">   Left Quals");
                pros::delay(50);
                Controller.print(1, 0, "    Right Quals");
                pros::delay(50);
                Controller.print(2, 0, "  X Left Elims");
                pros::delay(50);
                break;
            default:
                Controller.print(0, 0, ">   Left Quals");
                pros::delay(50);
                Controller.print(1, 0, "    Right Quals");
                pros::delay(50);
                Controller.print(2, 0, "    Left Elims");
                pros::delay(50);
                break;
        }
    } else if (Line == 2) {
        switch (autonSelect) {
            case 1:
                Controller.print(0, 0, "  X Left Quals");
                pros::delay(50);
                Controller.print(1, 0, ">   Right Quals");
                pros::delay(50);
                Controller.print(2, 0, "    Left Elims");
                pros::delay(50);
                break;
            case 2:
                Controller.print(0, 0, "    Left Quals");
                pros::delay(50);
                Controller.print(1, 0, "> X Right Quals");
                pros::delay(50);
                Controller.print(2, 0, "    Left Elims");
                pros::delay(50);
                break;
            case 3:
                Controller.print(0, 0, "    Left Quals");
                pros::delay(50);
                Controller.print(1, 0, ">   Right Quals");
                pros::delay(50);
                Controller.print(2, 0, "  X Left Elims");
                pros::delay(50);
                break;
            default:
                Controller.print(0, 0, "    Left Quals");
                pros::delay(50);
                Controller.print(1, 0, ">   Right Quals");
                pros::delay(50);
                Controller.print(2, 0, "    Left Elims");
                pros::delay(50);
                break;
        }
    } else if (Line == 3) {
        switch (autonSelect) {
            case 1:
                Controller.print(0, 0, "  X Left Quals");
                pros::delay(50);
                Controller.print(1, 0, "    Right Quals");
                pros::delay(50);
                Controller.print(2, 0, ">   Left Elims");
                pros::delay(50);
                break;
            case 2:
                Controller.print(0, 0, "    Left Quals");
                pros::delay(50);
                Controller.print(1, 0, "  X Right Quals");
                pros::delay(50);
                Controller.print(2, 0, ">   Left Elims");
                pros::delay(50);
                break;
            case 3:
                Controller.print(0, 0, "    Left Quals");
                pros::delay(50);
                Controller.print(1, 0, "    Right Quals");
                pros::delay(50);
                Controller.print(2, 0, "> X Left Elims");
                pros::delay(50);
                break;
            default:
                Controller.print(0, 0, "    Left Quals");
                pros::delay(50);
                Controller.print(1, 0, "    Right Quals");
                pros::delay(50);
                Controller.print(2, 0, ">   Left Elims");
                pros::delay(50);
                break;
        }
    } else if (Line == 4) {
        switch (autonSelect) {
            case 4:
                Controller.print(0, 0, "> X Right Elims");
                pros::delay(50);
                Controller.print(1, 0, "    No Auton");
                pros::delay(50);
                Controller.print(2, 0, "    P-Skills");
                pros::delay(50);
                break;
            case 5:
                Controller.print(0, 0, ">   Right Elims");
                pros::delay(50);
                Controller.print(1, 0, "  X No Auton");
                pros::delay(50);
                Controller.print(2, 0, "    P-Skills");
                pros::delay(50);
                break;
            case 6:
                Controller.print(0, 0, ">   Right Elims");
                pros::delay(50);
                Controller.print(1, 0, "    No Auton");
                pros::delay(50);
                Controller.print(2, 0, "  X P-Skills");
                pros::delay(50);
                break;
            default:
                Controller.print(0, 0, ">   Right Elims");
                pros::delay(50);
                Controller.print(1, 0, "    No Auton");
                pros::delay(50);
                Controller.print(2, 0, "    P-Skills");
                pros::delay(50);
                break;
        }
    } else if (Line == 5) {
        switch (autonSelect) {
            case 4:
                Controller.print(0, 0, "  X Right Elims");
                pros::delay(50);
                Controller.print(1, 0, ">   No Auton");
                pros::delay(50);
                Controller.print(2, 0, "    P-Skills");
                pros::delay(50);
                break;
            case 5:
                Controller.print(0, 0, "    Right Elims");
                pros::delay(50);
                Controller.print(1, 0, "> X No Auton");
                pros::delay(50);
                Controller.print(2, 0, "    P-Skills");
                pros::delay(50);
                break;
            case 6:
                Controller.print(0, 0, "    Right Elims");
                pros::delay(50);
                Controller.print(1, 0, ">   No Auton");
                pros::delay(50);
                Controller.print(2, 0, "  X P-Skills");
                pros::delay(50);
                break;
            default:
                Controller.print(0, 0, "    Right Elims");
                pros::delay(50);
                Controller.print(1, 0, ">   No Auton");
                pros::delay(50);
                Controller.print(2, 0, "    P-Skills");
                pros::delay(50);
                break;
        }
    } else if (Line == 6) {
        switch (autonSelect) {
            case 4:
                Controller.print(0, 0, "  X Right Elims");
                pros::delay(50);
                Controller.print(1, 0, "    No Auton");
                pros::delay(50);
                Controller.print(2, 0, ">   P-Skills");
                pros::delay(50);
                break;
            case 5:
                Controller.print(0, 0, "    Right Elims");
                pros::delay(50);
                Controller.print(1, 0, "  X No Auton");
                pros::delay(50);
                Controller.print(2, 0, ">   P-Skills");
                pros::delay(50);
                break;
            case 6:
                Controller.print(0, 0, "    Right Elims");
                pros::delay(50);
                Controller.print(1, 0, "    No Auton");
                pros::delay(50);
                Controller.print(2, 0, "> X P-Skills");
                pros::delay(50);
                break;
            default:
                Controller.print(0, 0, "    Right Elims");
                pros::delay(50);
                Controller.print(1, 0, "    No Auton");
                pros::delay(50);
                Controller.print(2, 0, ">   P-Skills");
                pros::delay(50);
                break;
        }
    }
}

inline void MotorCheck() {
    Controller.clear();
    pros::delay(50);
    if (Page == 1) {
        Controller.print(0,0,"BLM: %d °C", BLM.get_temperature());
        pros::delay(50);
        Controller.print(1,0,"FLM: %d °C", FLM.get_temperature());
        pros::delay(50);
        Controller.print(2,0,"BRM: %d °C", BRM.get_temperature());
        pros::delay(50);
    } else if (Page == 2) {
        Controller.print(0,0,"FRM: %d °C", FRM.get_temperature());
        pros::delay(50);
        Controller.print(1, 0, "Intake: %d °C", IntakeMotor.get_temperature());
        pros::delay(50);
        Controller.print(2, 0, "Indexer: %d °C", IndexerMotor.get_temperature());
        pros::delay(50);
    } else if (Page == 3) {
        Controller.print(0, 0, "FWM1: %d °C", FlywheelMotor1.get_temperature());
        pros::delay(50);
        Controller.print(1, 0, "FWM2: %d °C", FlywheelMotor2.get_temperature());
        pros::delay(50);
    }
}

inline void KeybindCheck() {
    Controller.clear();
    pros::delay(50);
    if (Page == 1) {
        Controller.print(0, 0, "X: Reverse");
        pros::delay(50);
        Controller.print(1, 0, "Y: Roller");
        pros::delay(50);
        Controller.print(2, 0, "A: Expansion");
        pros::delay(50);
    } else if (Page == 2) {
        Controller.print(0, 0, "B: (N/A)");
        pros::delay(50);
        Controller.print(1, 0, "Up: (N/A)");
        pros::delay(50);
        Controller.print(2, 0, "Down: (N/A)");
        pros::delay(50);
    } else if (Page == 3) {
        Controller.print(0, 0, "Left: (N/A)");
        pros::delay(50);
        Controller.print(1, 0, "Right: (N/A)");
        pros::delay(50);
        Controller.print(2, 0, "L1: (N/A)");
        pros::delay(50);
    } else if (Page == 4) {
        Controller.print(0, 0, "L2: (N/A)");
        pros::delay(50);
        Controller.print(1, 0, "R1: (N/A)");
        pros::delay(50);
        Controller.print(2, 0, "R2: (N/A)");
        pros::delay(50);
    }
}

inline void NotesCheck() {
    Controller.clear();
    pros::delay(50);
    if (Page == 1) {
        Controller.print(0, 0, "Left Auton is ");
        pros::delay(50);
        Controller.print(1, 0, "the only auton");
        pros::delay(50);
        Controller.print(2, 0, "that works    ");
        pros::delay(50);
    } else if (Page == 2) {
        Controller.print(0, 0, "oh also the   ");
        pros::delay(50);
        Controller.print(1, 0, "Left Elims    ");
        pros::delay(50);
        Controller.print(2, 0, "Auton         ");
        pros::delay(50);
    }
}

// Button-Pressed Functions
inline void DownPressed() {
    if (GamePhase == 1 && !AutonSelecting && !MotorChecking && !KeybindChecking && !NotesChecking && (Line < 4)) {
        Line++;
        CIDisplay();
    } else if (GamePhase == 1 && AutonSelecting && !MotorChecking && !KeybindChecking && !NotesChecking && (Line < 7)) {
        Line++;
        AutonSelect();
    } else if (GamePhase == 1 && !AutonSelecting && MotorChecking && !KeybindChecking && !NotesChecking && (Page < 3)) {
        Page++;
        MotorCheck();
    } else if (GamePhase == 1 && !AutonSelecting && !MotorChecking && KeybindChecking && !NotesChecking && (Page < 4)) {
        Page++;
        KeybindCheck();
    } else if (GamePhase == 1 && !AutonSelecting && !MotorChecking && !KeybindChecking && NotesChecking && (Page < 2)) {
        Page++;
        NotesCheck();
    }
}

inline void UpPressed() {
    if (GamePhase == 1 && !AutonSelecting && !MotorChecking && !KeybindChecking && !NotesChecking && (Line > 1)) {
        Line--;
        CIDisplay();
    } else if (GamePhase == 1 && AutonSelecting && !MotorChecking && !KeybindChecking && !NotesChecking && (Line > 1)) {
        Line--;
        AutonSelect();
    } else if (GamePhase == 1 && !AutonSelecting && MotorChecking && !KeybindChecking && !NotesChecking && (Page > 1)) {
        Page--;
        MotorCheck();
    } else if (GamePhase == 1 && !AutonSelecting && !MotorChecking && KeybindChecking && !NotesChecking && (Page > 1)) {
        Page--;
        KeybindCheck();
    } else if (GamePhase == 1 && !AutonSelecting && !MotorChecking && !KeybindChecking && NotesChecking && (Page > 1)) {
        Page--;
        NotesCheck();
    }
}

inline void APressed() {
    if (GamePhase == 1 && !AutonSelecting && !MotorChecking && !KeybindChecking && !NotesChecking) {
        if (Line == 1) {
            AutonSelecting = true;
            Line = autonSelect;
            AutonSelect();
        } else if (Line == 2) {
            MotorChecking = true;
            Page = 1;
            MotorCheck();
        } else if (Line == 3) {
            KeybindChecking = true;
            Page = 1;
            KeybindCheck();
        } else if (Line == 4) {
            NotesChecking = true;
            Page = 1;
            NotesCheck();
        }
    } else if (GamePhase == 1 && AutonSelecting && !MotorChecking && !KeybindChecking && !NotesChecking) {
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

inline void BPressed() {
    if (GamePhase == 1) {
        if (AutonSelecting) {
            AutonSelecting = false;
            Line = 2;
            CIDisplay();
        } else if (MotorChecking) {
            MotorChecking = false;
            Line = 3;
            CIDisplay();
        } else if (KeybindChecking) {
            KeybindChecking = false;
            Line = 4;
            CIDisplay();
        } else if (NotesChecking) {
            NotesChecking = false;
            Line = 1;
            CIDisplay();
        }
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

inline bool intakeOn = false;

inline void ToggleIntake() {
    if (!intakeOn) {
        IntakeMotor.move(127); // Max: 127
    }
    else if (intakeOn) {
        IntakeMotor.brake();
    }
    intakeOn = !intakeOn;
}

inline void Expansion() {
    ExpansionMotor.move_absolute(90, 600);
}
// */