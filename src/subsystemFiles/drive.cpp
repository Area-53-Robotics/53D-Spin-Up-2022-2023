#include "main.h"

float getMotorOutput(int i) {
    return i*exp((double)((abs(i)-100)*60)/1000);
}

void DirectionToggle() {
    if (Direction == 'N') Direction = 'R';
    else if (Direction == 'R') Direction = 'N';
    ControllerDisplay();
}

void setDriveMotors() {
	LYAxis = Controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
	RYAxis = Controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

    if (abs(LYAxis) < 10) LYAxis = 0;
    if (abs(RYAxis) < 10) RYAxis = 0;

    if (Direction == 'N') {
        /*
        BLM.move(getMotorOutput(LYAxis));
        FLM.move(getMotorOutput(LYAxis));
        BRM.move(getMotorOutput(RYAxis));
        FRM.move(getMotorOutput(RYAxis));
        */
        BLM.move(LYAxis);
        FLM.move(LYAxis);
        BRM.move(RYAxis);
        FRM.move(RYAxis);
    } else if (Direction == 'R') {
        /*
        BLM.move(getMotorOutput(RYAxis) * -1);
        FLM.move(getMotorOutput(RYAxis) * -1);
        BRM.move(getMotorOutput(LYAxis) * -1);
        FRM.move(getMotorOutput(LYAxis) * -1);
        */
        BLM.move(RYAxis * -1);
        FLM.move(RYAxis * -1);
        BRM.move(LYAxis * -1);
        FRM.move(LYAxis * -1);   
    }
}