#include "main.h"
#include "subsystemHeaders/flywheel.hpp"

const double flyFactor = 0.5; //! Needs testing

void ToggleFlywheel(int velocity) {
    if (!FlywheelSpinning) {
        FlywheelSpinning = true;
        FlywheelMotor1.set_velocity(velocity);
        FlywheelMotor2.set_velocity(velocity);
        /*
        FlywheelMotor1.set_velocity_custom_controller(velocity);
        FlywheelMotor2.set_velocity_custom_controller(velocity);
        FlywheelMotor1.move_velocity(velocity);
        FlywheelMotor2.move_velocity(velocity);
        */
    } else if (FlywheelSpinning) {
        FlywheelMotor1.stop();
        FlywheelMotor2.stop();
        /*
        FlywheelMotor1.brake();
        FlywheelMotor2.brake();
        */
        FlywheelSpinning = false;
    }
    ControllerDisplay();
}

void ToggleFlywheelSpeed() {
    if (FlywheelMotorSpeed == 363) FlywheelMotorSpeed = 500;
    else if (FlywheelMotorSpeed == 500) FlywheelMotorSpeed = 600;
    else if (FlywheelMotorSpeed == 600) FlywheelMotorSpeed = 363;
    ControllerDisplay();
}

void AutoAim() {
    if (findDiscVelocity() < 30 /* Number needs testing */) {
        double distDX = highGoalX - posX;
        double distDY = highGoalY - posY;
        double desiredOrientation = orientation - atan2(distDY, distDX) - M_PI - degToRad(10);
        PIDTurn(desiredOrientation);
        ToggleFlywheel(findDiscVelocity() * flyFactor);
    } else {
        double distDX = lowGoalX - posX;
        double distDY = lowGoalY - posY;
        double desiredOrientation = orientation - atan2(distDY, distDX) - M_PI - degToRad(10);
        PIDTurn(desiredOrientation);
        // ToggleFlywheel(findLowGoalDiscVelocity());
    }
}

void SkillsAutoAim() {
    if (highGoalDist < teamHighGoalDist) {
        double distDX = highGoalX - posX;
        double distDY = highGoalY - posY;
        double desiredOrientation = orientation - atan2(distDY, distDX) - M_PI - degToRad(10);
        PIDTurn(desiredOrientation);
        ToggleFlywheel(findDiscVelocity() * flyFactor);
    } else {
        double distDX = teamHighGoalX - posX;
        double distDY = teamHighGoalY - posY;
        double desiredOrientation = orientation - atan2(distDY, distDX) - M_PI - degToRad(10);
        PIDTurn(desiredOrientation);
        ToggleFlywheel(findTeamDiscVelocity() * flyFactor);
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