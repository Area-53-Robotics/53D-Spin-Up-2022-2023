#include "main.h"

inline unsigned short int Page = 1;
inline unsigned short int Line = 1;
 
inline bool AutonSelecting = false;
inline bool MotorChecking = false;
inline bool KeybindChecking = false;
inline bool NotesChecking = false;

void CIDisplay() {
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

void AutonSelect() {
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
                Controller.print(1, 0, "    Full AWP");
                pros::delay(50);
                Controller.print(2, 0, "    No Auton");
                pros::delay(50);
                break;
            case 5:
                Controller.print(0, 0, ">   Right Elims");
                pros::delay(50);
                Controller.print(1, 0, "  X Full AWP");
                pros::delay(50);
                Controller.print(2, 0, "    No Auton");
                pros::delay(50);
                break;
            case 6:
                Controller.print(0, 0, ">   Right Elims");
                pros::delay(50);
                Controller.print(1, 0, "    Full AWP");
                pros::delay(50);
                Controller.print(2, 0, "  X No Auton");
                pros::delay(50);
                break;
            default:
                Controller.print(0, 0, ">   Right Elims");
                pros::delay(50);
                Controller.print(1, 0, "    Full AWP");
                pros::delay(50);
                Controller.print(2, 0, "    No Auton");
                pros::delay(50);
                break;
        }
    } else if (Line == 5) {
        switch (autonSelect) {
            case 4:
                Controller.print(0, 0, "  X Right Elims");
                pros::delay(50);
                Controller.print(1, 0, ">   Full AWP");
                pros::delay(50);
                Controller.print(2, 0, "    No Auton");
                pros::delay(50);
                break;
            case 5:
                Controller.print(0, 0, "    Right Elims");
                pros::delay(50);
                Controller.print(1, 0, "> X Full AWP");
                pros::delay(50);
                Controller.print(2, 0, "    No Auton");
                pros::delay(50);
                break;
            case 6:
                Controller.print(0, 0, "    Right Elims");
                pros::delay(50);
                Controller.print(1, 0, ">   Full AWP");
                pros::delay(50);
                Controller.print(2, 0, "  X No Auton");
                pros::delay(50);
                break;
            default:
                Controller.print(0, 0, "    Right Elims");
                pros::delay(50);
                Controller.print(1, 0, ">   Full AWP");
                pros::delay(50);
                Controller.print(2, 0, "    No Auton");
                pros::delay(50);
                break;
        }
    } else if (Line == 6) {
        switch (autonSelect) {
            case 4:
                Controller.print(0, 0, "  X Right Elims");
                pros::delay(50);
                Controller.print(1, 0, "    Full AWP");
                pros::delay(50);
                Controller.print(2, 0, ">   No Auton");
                pros::delay(50);
                break;
            case 5:
                Controller.print(0, 0, "    Right Elims");
                pros::delay(50);
                Controller.print(1, 0, "  X Full AWP");
                pros::delay(50);
                Controller.print(2, 0, ">   No Auton");
                pros::delay(50);
                break;
            case 6:
                Controller.print(0, 0, "    Right Elims");
                pros::delay(50);
                Controller.print(1, 0, "    Full AWP");
                pros::delay(50);
                Controller.print(2, 0, "> X No Auton");
                pros::delay(50);
                break;
            default:
                Controller.print(0, 0, "    Right Elims");
                pros::delay(50);
                Controller.print(1, 0, "    Full AWP");
                pros::delay(50);
                Controller.print(2, 0, ">   No Auton");
                pros::delay(50);
                break;
        }
    } else if (Line == 7) {
        switch (autonSelect) {
            case 7:
                Controller.print(0, 0, "> X P-Skills");
                pros::delay(50);
                break;
            default:
                Controller.print(0, 0, ">   P-Skills");
                pros::delay(50);
                break;
        }
    }
}

void MotorCheck() {
    Controller.clear();
    pros::delay(50);
    if (Page == 1) {
        Controller.print(0,0,"BLM: %f °C", BLM.get_temperature());
        pros::delay(50);
        Controller.print(1,0,"FLM: %f °C", FLM.get_temperature());
        pros::delay(50);
        Controller.print(2,0,"BRM: %f °C", BRM.get_temperature());
        pros::delay(50);
    } else if (Page == 2) {
        Controller.print(0,0,"FRM: %f °C", FRM.get_temperature());
        pros::delay(50);
        Controller.print(1, 0, "Intake: %f °C", IntakeMotor.get_temperature());
        pros::delay(50);
        Controller.print(2, 0, "Indexer: %f °C", IndexerMotor.get_temperature());
        pros::delay(50);
    } else if (Page == 3) {
        Controller.print(0, 0, "FWM1: %f °C", FlywheelMotor1.get_temperature());
        pros::delay(50);
        Controller.print(1, 0, "FWM2: %f °C", FlywheelMotor2.get_temperature());
        pros::delay(50);
    }
}

void KeybindCheck() {
    Controller.clear();
    pros::delay(50);
    if (Page == 1) {
        Controller.print(0, 0, "X: Reverse");
        pros::delay(50);
        Controller.print(1, 0, "Y: (N/A)");
        pros::delay(50);
        Controller.print(2, 0, "A: Toggle Flywheel Speed");
        pros::delay(50);
    } else if (Page == 2) {
        Controller.print(0, 0, "B: Expansion");
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
        Controller.print(2, 0, "L1: Backwards Intake");
        pros::delay(50);
    } else if (Page == 4) {
        Controller.print(0, 0, "L2: Intake");
        pros::delay(50);
        Controller.print(1, 0, "R1: Indexer");
        pros::delay(50);
        Controller.print(2, 0, "R2: Flywheel");
        pros::delay(50);
    }
}

void NotesCheck() {
    Controller.clear();
    pros::delay(50);
    if (Page == 1) {
        Controller.print(0, 0, "- Check the indexer ");
        pros::delay(50);
        Controller.print(1, 0, "position             ");
        Controller.print(0, 0, "");
        pros::delay(50);
        Controller.print(1, 0, "");
        pros::delay(50);
        Controller.print(2, 0, "");
        pros::delay(50);
    } else if (Page == 2) {
        Controller.print(0, 0, "");
        pros::delay(50);
        Controller.print(1, 0, "");
        pros::delay(50);
        Controller.print(2, 0, "");
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
            case 1:
                // Left Quals
                autonSelect = 1;
                posX = 16;
                posY = 9;
                IMU.set_heading(-90);
                break;
            case 2:
                // Right Quals
                autonSelect = 2;
                posX = 135;
                posY = 138;
                IMU.set_heading(-180);
                break;
            case 3:
                // Left Elims
                autonSelect = 3;
                posX = 16;
                posY = 9;
                IMU.set_heading(-90);
                break;
            case 4:
                // Right Elims
                autonSelect = 4;
                posX = 135;
                posY = 138;
                IMU.set_heading(-180);
                break;
            case 5:
                // Full Autonomous Win Point
                autonSelect = 5;
                posX = 135;
                posY = 138;
                IMU.set_heading(-180);
                break;
            case 6:
                // No Auton
                autonSelect = 6;
                posX = 135;
                posY = 138;
                IMU.set_heading(-180);
                break;
            case 7:
                // Programming Skills
                autonSelect = 7;
                posX = 16;
                posY = 9;
                IMU.set_heading(-90);
                break;
        }
        orientation = degToRad(360 - IMU.get_heading());
        lastOrientation = orientation;
        avgTheta = orientation + (deltaTheta / 2);
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
	IntakeMotor.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
	while (true) {
		if(Controller.get_digital_new_press(DIGITAL_DOWN)) DownPressed();
		if(Controller.get_digital_new_press(DIGITAL_UP)) UpPressed();
		if(Controller.get_digital_new_press(DIGITAL_A)) APressed();
		if(Controller.get_digital_new_press(DIGITAL_B)) BPressed();

		pros::delay(20);
	}
}