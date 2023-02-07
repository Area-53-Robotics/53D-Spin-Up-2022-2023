#include "main.h"
#include "subsystemHeaders/drive.hpp"

float getMotorOutput(int input) {
    return (std::exp(-20/12.7)+std::exp((std::abs(input)-127)/12.7)*(1-std::exp(-20/12.7))) * input;
    // return input*exp((int)(((abs(i)-100)*60)/1000));
}

void DirectionToggle() {
    isReverse = !isReverse;
    ControllerDisplay();
}

void setDriveMotors() {
	LYAxis = Controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
	RYAxis = Controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y)/* * 0.7 */;

    if (abs(LYAxis) < 10) LYAxis = 0;
    if (abs(RYAxis) < 10) RYAxis = 0;

    if (isReverse == false) {
        /*
        BLM.set_voltage(VConversion(LYAxis));
        FLM.set_voltage(VConversion(LYAxis));
        BRM.set_voltage(VConversion(RYAxis));
        FRM.set_voltage(VConversion(RYAxis));
        BLM.set_voltage(getMotorOutput(VConversion(LYAxis)));
        FLM.set_voltage(getMotorOutput(VConversion(LYAxis)));
        BRM.set_voltage(getMotorOutput(VConversion(RYAxis)));
        FRM.set_voltage(getMotorOutput(VConversion(RYAxis)));
        BLM.move(LYAxis);
        FLM.move(LYAxis);
        BRM.move(RYAxis);
        FRM.move(RYAxis);
        */
        BLM.move(getMotorOutput(LYAxis));
        FLM.move(getMotorOutput(LYAxis));
        BRM.move(getMotorOutput(RYAxis));
        FRM.move(getMotorOutput(RYAxis));
    } else if (isReverse == true) {
        /*
        BLM.set_voltage(VConversion(RYAxis * -1));
        FLM.set_voltage(VConversion(RYAxis * -1));
        BRM.set_voltage(VConversion(LYAxis * -1));
        FRM.set_voltage(VConversion(LYAxis * -1));   
        BLM.set_voltage(VConversion(getMotorOutput(RYAxis) * -1));
        FLM.set_voltage(VConversion(getMotorOutput(RYAxis) * -1));
        BRM.set_voltage(VConversion(getMotorOutput(LYAxis) * -1));
        FRM.set_voltage(VConversion(getMotorOutput(LYAxis) * -1));
        BLM.move(RYAxis * -1);
        FLM.move(RYAxis * -1);
        BRM.move(LYAxis * -1);
        FRM.move(LYAxis * -1);
        */
        BLM.move(getMotorOutput(RYAxis) * -1);
        FLM.move(getMotorOutput(RYAxis) * -1);
        BRM.move(getMotorOutput(LYAxis) * -1);
        FRM.move(getMotorOutput(LYAxis) * -1);
    }
}