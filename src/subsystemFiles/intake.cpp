#include "main.h"

void setIntakeMotor() {
    if (Controller.get_digital_new_press(DIGITAL_X)) intake = !intake;

    if (intake) {
        IntakeMotor.move(127);
    } else {
        IntakeMotor.brake();
    }
}