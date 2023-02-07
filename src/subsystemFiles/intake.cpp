#include "main.h"
#include "subsystemHeaders/intake.hpp"


void ToggleIntake() {
    /*
    if (!intakeOn) {
        IntakeMotor.set_voltage(VConversion(127));
    }
    else if (intakeOn) {
        IntakeMotor.stop();
    }
    intakeOn = !intakeOn;
    */
    if (!intakeOn) {
        IntakeMotor.move(127);
    }
    else if (intakeOn) {
        IntakeMotor.brake();
    }
    intakeOn = !intakeOn;
}

void BackwardsIntake() {
    /*
    if (!intakeOn) {
        IntakeMotor.set_velocity(-200);
    }
    else if (intakeOn) {
        IntakeMotor.stop();
    }
    intakeOn = !intakeOn;
    */
    if (!intakeOn) {
        IntakeMotor.move_velocity(-200);
    }
    else if (intakeOn) {
        IntakeMotor.brake();
    }
    intakeOn = !intakeOn;
}

void SpinRoller() {
    ToggleIntake();
    sylib::delay(333);
    ToggleIntake();
}

void SpinSkillsRoller() {
    BackwardsIntake();
    sylib::delay(500);
    BackwardsIntake();
}