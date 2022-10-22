#include "main.h"

void setDriveMotors() {
	short int LYAxis = Controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
	short int RYAxis = Controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

    if (abs(LYAxis) < 10) LYAxis = 0;
    if (abs(RYAxis) < 10) RYAxis = 0;

    BLM.move(LYAxis);
    FLM.move(LYAxis);
    BRM.move(RYAxis);
    FRM.move(RYAxis);
}