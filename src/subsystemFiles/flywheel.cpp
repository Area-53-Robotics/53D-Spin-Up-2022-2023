#include "main.h"
#include "subsystemHeaders/flywheel.hpp"

/*
?   All functions related to flywheel control in both the autonomous
?   phase and driver controlled phase.
*/

//* Boolean variable to represent whether the flywheel is spinning
bool FlywheelSpinning = false;
//* Integer variable to store the target RPM of the flywheel motors
int FlywheelMotorSpeed = 340;

/*
    * This function runs in the background during the program's
    * runtime. It adjusts the speed of the flywheel to match the
    * target speed set in FlywheelMotorSpeed.
*/
void FlywheelController() {
    while (true) {
        if (FlywheelMotorSpeed == 0) {
            //* Stops the flywheel if the motor speed is set to 0.
            FlywheelMotor1.stop();
            FlywheelMotor2.stop();
        } else if (FlywheelSpinning) {
            /*
                * If the driver has turned on the flywheel,
                * the flywheel will adjust to the speed the driver
                * has toggled using a PID control loop.
            */
            FlywheelMotor1.set_velocity(FlywheelMotorSpeed);
            FlywheelMotor2.set_velocity(FlywheelMotorSpeed);
        } else if (!FlywheelSpinning) {
            //* Stops the flywheel if the driver toggles it off
            FlywheelMotor1.stop();
            FlywheelMotor2.stop();
        }
        pros::delay(10);
    }
}

void ToggleFlywheelSpeed() {
    /*
        * When the driver triggers this function, it toggles the
        * flywheel motor speed between 340 and 500.
    */
    if (FlywheelMotorSpeed == 500) FlywheelMotorSpeed = 340;
    else if (FlywheelMotorSpeed == 340) FlywheelMotorSpeed = 500;
    else FlywheelMotorSpeed = 340;
    MainControllerDisplay();
}

void ToggleFlywheelStatus() {
    /*
        * When the driver triggers this function, it toggles the
        * flywheel on and off.
    */
    if (!FlywheelSpinning) FlywheelSpinning = true;
    else FlywheelSpinning = false;
    MainControllerDisplay();
}

void AutonFlywheel(int velocity) {
    /*
        * Toggles the flywheel on with the input velocity if the
        * target is not 0. If the target is 0, it will stop the
        * motors.
    */
    if (velocity == 0) {
        FlywheelSpinning = false;
        FlywheelMotorSpeed = 0;
    } else {
        FlywheelSpinning = true;
        FlywheelMotorSpeed = velocity;
    }
}

double flywheelVelocity = 0;
const double FlywheelRadius = 2.5;
const double SpeedConversionFactor = 0.5; //! Needs testing

void AutoAim() {
    if (findDiscVelocity() < 30 /* Number needs testing */) {
        double distDX = highGoalX - posX;
        double distDY = highGoalY - posY;
        double desiredOrientation = orientation - atan2(distDY, distDX) - M_PI - degToRad(10);
        PIDTurn(desiredOrientation);
        FlywheelMotorSpeed = findDiscVelocity() * SpeedConversionFactor;
    } else {
        double distDX = lowGoalX - posX;
        double distDY = lowGoalY - posY;
        double desiredOrientation = orientation - atan2(distDY, distDX) - M_PI - degToRad(10);
        PIDTurn(desiredOrientation);
        // FlywheelMotorSpeed = findLowGoalDiscVelocity();
    }
}

void SkillsAutoAim() {
    if (highGoalDist < teamHighGoalDist) {
        double distDX = highGoalX - posX;
        double distDY = highGoalY - posY;
        double desiredOrientation = orientation - atan2(distDY, distDX) - M_PI - degToRad(10);
        PIDTurn(desiredOrientation);
        FlywheelMotorSpeed = findDiscVelocity() * SpeedConversionFactor;
    } else {
        double distDX = teamHighGoalX - posX;
        double distDY = teamHighGoalY - posY;
        double desiredOrientation = orientation - atan2(distDY, distDX) - M_PI - degToRad(10);
        PIDTurn(desiredOrientation);
        FlywheelMotorSpeed = findTeamDiscVelocity() * SpeedConversionFactor;
    }
}

void FlySpeedInc100() {
    FlywheelMotorSpeed += 100;
    MainControllerDisplay();
}

void FlySpeedDec100() {
    FlywheelMotorSpeed -= 100;
    MainControllerDisplay();
}

void FlySpeedInc10() {
    FlywheelMotorSpeed += 10;
    MainControllerDisplay();
}

void FlySpeedDec10() {
    FlywheelMotorSpeed -= 10;
    MainControllerDisplay();
}