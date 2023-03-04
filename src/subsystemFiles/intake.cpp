#include "main.h"
#include "subsystemHeaders/intake.hpp"

/*
?   All functions relating to usage of the intake and roller during
?   the autonomous and driver controlled phases.
*/

/*
    * Integer variable to store the status of the intake.
    * Possible values:
        0: Intake Off
        1: Normal Direction (used to intake discs)
        2: Reverse Direction (used to remove discs from the intake)
*/
unsigned short int intakeStatus = 0;

void ForwardIntake() {
    if ((intakeStatus == 0) || (intakeStatus == 2)) {
        /*
            * If the intake is currently not rotating or is rotating
            * in the reverse direction, the intake will start
            * rotating in the normal direction.
        */
        intakeStatus = 1;
        IntakeMotor.move(127);
    }
    else if (intakeStatus == 1) {
        /*
            * If the intake is currently rotating in the normal
            * direction, the intake will be toggled off.
        */
        intakeStatus = 0;
        IntakeMotor.brake();
    }
}

void ReverseIntake() {
    if ((intakeStatus == 0) || (intakeStatus == 1)) {
        /*
            * If the intake is currently not rotating or is rotating
            * in the normal direction, the intake will start
            * rotating in the reverse direction.
        */
        intakeStatus = 2;
        IntakeMotor.move(-127);
    }
    else if (intakeStatus == 2) {
        /*
            * If the intake is currently rotating in the reverse
            * direction, the intake will be toggled off.
        */
        intakeStatus = 0;
        IntakeMotor.brake();
    }
}

/*
    * Macro to spin the color rollers 1/3 of its circumference.
    * By using this macro once or twice, our driver can turn the
    * roller to our color regardless of the rollers color status.
*/
void SpinRoller() {
    ForwardIntake();
    sylib::delay(333);
    ForwardIntake();
}

/*
    * Macro to spin the color rollers 1/2 of its circumference.
    * This macro can turn the color rollers from blue to red to
    * score them.
*/
void SpinSkillsRoller() {
    ForwardIntake();
    sylib::delay(500);
    ForwardIntake();
}