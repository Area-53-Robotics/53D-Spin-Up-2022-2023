#include "main.h"
#include "utilHeaders/controller.hpp"

/*
*   This function displays useful information to the driver during
*   the driver controlled phase of the match.
*/
void MainControllerDisplay() {
    Controller.clear();
    sylib::delay(50);
    /*
    *   Displays the direction the drivetrain is set to drive by
    *   the driver on the first line of the controller.
    */
    if (isReverse == false) Controller.print(0, 0, "Direction: Normal");
    else if (isReverse == true) Controller.print(0, 0, "Direction: Reverse");
    sylib::delay(50);
    /*
    *   Displays whether the flywheel is on or off on the second line
    *   of the controller.
    */
    if (FlywheelSpinning) Controller.print(1, 0, "Flywheel: On");
    else if (!FlywheelSpinning) Controller.print(1, 0, "Flywheel: Off");
    sylib::delay(50);
    /*
    *   Prints the current target flywheel motor speed on the third
    *   line of the controller.
    */
    Controller.print(2, 0, "FlySpeed = %d", FlywheelMotorSpeed);
}

unsigned short discCount = 0;

void SecondControllerDisplay() {
    Controller2.clear();
    sylib::delay(50);
    Controller2.print(0, 0, "Discs: %d", discCount);
    sylib::delay(50);
    Controller2.print(1, 0, "Fly Speed: %f", flywheelVelocity);
    sylib::delay(50);
    Controller2.print(2, 0, "Target Speed: %d", FlywheelMotorSpeed);
}

void IncDiscCount() {
    if (discCount < 3) {
        discCount++;
        SecondControllerDisplay();
    }
}

void DecDiscCount() {
    if (discCount > 0) {
        discCount--;
        SecondControllerDisplay();
    }
}

void MotorTempDisplay1() {
    Controller.clear();
    sylib::delay(50);
    Controller.print(0,0,"BLM: %f °C", BLM.get_temperature());
    sylib::delay(50);
    Controller.print(1,0,"FLM: %f °C", FLM.get_temperature());
    sylib::delay(50);
    Controller.print(2,0,"BRM: %f °C", BRM.get_temperature());
    sylib::delay(50);
}

void MotorTempDisplay2() {
    Controller.clear();
    sylib::delay(50);
    Controller.print(0,0,"FRM: %f °C", FRM.get_temperature());
    sylib::delay(50);
    Controller.print(1, 0, "Intake1: %f °C", IntakeMotor.get_temperature());
    sylib::delay(50);
    Controller.print(2, 0, "Intake2: %f °C", IndexerMotor.get_temperature());
    sylib::delay(50);
}

void MotorTempDisplay3() {
    Controller.clear();
    sylib::delay(50);
    Controller.print(0, 0, "FWM1: %f °C", FlywheelMotor1.get_temperature());
    sylib::delay(50);
    Controller.print(1, 0, "FWM2: %f °C", FlywheelMotor2.get_temperature());
    sylib::delay(50);
}