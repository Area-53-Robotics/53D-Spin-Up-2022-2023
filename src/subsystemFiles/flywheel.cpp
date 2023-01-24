#include "main.h"
#include "subsystemHeaders/flywheel.hpp"

void ToggleFlywheel(int velocity) {
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

void ToggleFlywheelSpeed() {
    if (FlywheelMotorSpeed == 363) FlywheelMotorSpeed = 600;
    else if (FlywheelMotorSpeed == 600) FlywheelMotorSpeed = 363;
    ControllerDisplay();
}

void AutoAim() {
    if (findDiscVelocity() < 10) {
        double distDX = highGoalX - posX;
        double distDY = highGoalY - posY;
        double desiredOrientation = orientation - atan2(distDY, distDX) - degToRad(10);
        PIDTurn(desiredOrientation);
        ToggleFlywheel(findDiscVelocity());
    } else {
        double distDX = lowGoalX - posX;
        double distDY = lowGoalY - posY;
        double desiredOrientation = orientation - atan2(distDY, distDX) - degToRad(10);
    }
}

void FlySpeedInc100() {
    FlywheelMotorSpeed += 100;
    ControllerDisplay();
}

void FlySpeedDec100() {
    FlywheelMotorSpeed -= 100;
    ControllerDisplay();
}

void FlySpeedInc10() {
    FlywheelMotorSpeed += 10;
    ControllerDisplay();
}

void FlySpeedDec10() {
    FlywheelMotorSpeed -= 10;
    ControllerDisplay();
}