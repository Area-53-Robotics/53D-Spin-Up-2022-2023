#include "main.h"
#include "subsystemHeaders/pid.hpp"

std::ofstream file;

bool PIDActive = false;
double const driveFactor = 0.8;

void PIDMove(double desiredX, double desiredY, bool isReverse) {
  while (odomActive) pros::delay(1);
  unsigned long long int PIDLoopNum = 1;

  double kP = 0;
  double error = 0;
  double power = 0;
  double integral = 0;
  double kI = 0;
  double derivative = 0;
  double prevError = 0;
  double kD = 0;

  double distDX = desiredX - posX;
  double distDY = desiredY - posY;
  double desiredOrientation = orientation - atan2(distDY, distDX);

  if (!isReverse) PIDTurn(desiredOrientation);
  else if (isReverse) PIDTurn(desiredOrientation + M_PI);

  while (error > 1) {
    if ((orientation != desiredOrientation) && PIDLoopNum % 3 == 0) {
      if (!isReverse) PIDTurn(desiredOrientation);
      else if (isReverse) PIDTurn(desiredOrientation + M_PI);
    }
    error = distFormula(posX, posY, desiredX, desiredY);
    integral += error;
    if (error < 0) integral = 0;
    if (error > 100000000) integral = 0;
    derivative = error - prevError;
    prevError = error;
    power = error * kP + integral * kI + derivative * kD;
    if (power > 12000) power = 12000;

    if (!isReverse) {
      BLM.move_voltage(power);
      FLM.move_voltage(power);
      BRM.move_voltage(power * driveFactor);
      FRM.move_voltage(power * driveFactor);
    } else {
      BLM.move_voltage(power * -1);
      FLM.move_voltage(power * -1);
      BRM.move_voltage(power * driveFactor * -1);
      FRM.move_voltage(power * driveFactor * -1);
    }

    // Data Collection
      file.open("/usd/Trial.txt");

      file << center("Type",10) << " | "
            << center("Loop #",10) << " | "
            << center("Error",10) << " | "
            << center("Power",10) << " | "
            << center("kP",10) << " | "
            << center("integral",10) << " | "
            << center("kI",10) << " | "
            << center("derivative",10) << " | "
            << center("kD",10) << " | "
            << center("posX",10) << " | "
            << center("posY",10) << " | "
            << center("desiredX",10) << " | "
            << center("desiredY",10) << " | "
            << center("distDX",10) << " | "
            << center("distDY",10) << "\n";

            file << std::string(10*11 /*Sec # = # of variables (for both terms)*/ + 2*11, '-') << "\n";

            file << prd(1,1,10) << " | "
                << prd(PIDLoopNum,1,10) << " | "
                << prd(error,2,10) << " | "
                << prd(power,2,10) << " | "
                << prd(kP,2,10) << " | "
                << prd(integral,2,10) << " | "
                << prd(kI,2,10) << " | "
                << prd(derivative,2,10) << " | "
                << prd(kD,2,10) << " | "
                << prd(posX,2,10) << " | "
                << prd(posY,2,10) << " | "
                << prd(desiredX,2,10) << " | "
                << prd(desiredY,2,10) << " | "
                << prd(distDX,2,10) << " | "
                << prd(distDY,2,10) << "\n";
            
            file.close();

            std::cout << center("Type",10) << " | "
                << center("Loop #",10) << " | "
                << center("Error",10) << " | "
                << center("Power",10) << " | "
                << center("kP",10) << " | "
                << center("integral",10) << " | "
                << center("kI",10) << " | "
                << center("derivative",10) << " | "
                << center("kD",10) << " | "
                << center("posX",10) << " | "
                << center("posY",10) << " | "
                << center("desiredX",10) << " | "
                << center("desiredY",10) << " | "
                << center("distDX",10) << " | "
                << center("distDY",10) << "\n";

            std::cout << std::string(10*11 /*Sec # = # of variables (for both terms)*/ + 2*11, '-') << "\n";

            std::cout << prd(1,1,10) << " | "
                << prd(PIDLoopNum,1,10) << " | "
                << prd(error,2,10) << " | "
                << prd(power,2,10) << " | "
                << prd(kP,2,10) << " | "
                << prd(integral,2,10) << " | "
                << prd(kI,2,10) << " | "
                << prd(derivative,2,10) << " | "
                << prd(kD,2,10) << " | "
                << prd(posX,2,10) << " | "
                << prd(posY,2,10) << " | "
                << prd(desiredX,2,10) << " | "
                << prd(desiredY,2,10) << " | "
                << prd(distDX,2,10) << " | "
                << prd(distDY,2,10) << "\n";
    // Data Collection

    PIDLoopNum++;

    pros::delay(10);
  }
  BLM.move_voltage(0);
  FLM.move_voltage(0);
  BRM.move_voltage(0);
  FRM.move_voltage(0);
}

void PIDTurn(double desiredOrientation) {
  while (odomActive) pros::delay(1);
  unsigned long long int PIDLoopNum = 0;

  double kP = 0;
  double error = 0;
  double power = 0;
  double integral = 0;
  double kI = 0;
  double derivative = 0;
  double prevError = 0;
  double kD = 0;

  while (error > 0) {
    error = desiredOrientation - orientation;
    integral += error;
    if (error < 0) integral = 0;
    if (error > 100000000) integral = 0;
    derivative = error - prevError;
    prevError = error;
    power = error * kP + integral * kI + derivative * kD;
    if (power > 12000) power = 12000;

    if (desiredOrientation - orientation > 0) {
      BLM.move_voltage(power * -1);
      FLM.move_voltage(power * -1);
      BRM.move_voltage(power * driveFactor);
      FRM.move_voltage(power * driveFactor);
    } else {
      BLM.move_voltage(power);
      FLM.move_voltage(power);
      BRM.move_voltage(power * driveFactor * -1);
      FRM.move_voltage(power * driveFactor * -1);
    }

    // Data Collection
      file.open("/usd/Trial.txt");

      file << center("Type",10) << " | "
            << center("Loop #",10) << " | "
            << center("Error",10) << " | "
            << center("Power",10) << " | "
            << center("kP",10) << " | "
            << center("integral",10) << " | "
            << center("kI",10) << " | "
            << center("derivative",10) << " | "
            << center("kD",10) << " | "
            << center("posX",10) << " | "
            << center("posY",10) << " | "
            << center("desiredX",10) << " | "
            << center("desiredY",10) << " | "
            << center("distDX",10) << " | "
            << center("distDY",10) << "\n";

            file << std::string(10*11 /*Sec # = # of variables (for both terms)*/ + 2*11, '-') << "\n";

            file << prd(1,1,10) << " | "
                << prd(PIDLoopNum,1,10) << " | "
                << prd(error,2,10) << " | "
                << prd(power,2,10) << " | "
                << prd(kP,2,10) << " | "
                << prd(integral,2,10) << " | "
                << prd(kI,2,10) << " | "
                << prd(derivative,2,10) << " | "
                << prd(kD,2,10) << " | "
                << prd(posX,2,10) << " | "
                << prd(posY,2,10) << " | " << "\n";
                // << prd(desiredX,2,10) << " | "
                // << prd(desiredY,2,10) << " | "
                // << prd(distDX,2,10) << " | "
                // << prd(distDY,2,10) << "\n";
            
            file.close();

            std::cout << center("Type",10) << " | "
                << center("Loop #",10) << " | "
                << center("Error",10) << " | "
                << center("Power",10) << " | "
                << center("kP",10) << " | "
                << center("integral",10) << " | "
                << center("kI",10) << " | "
                << center("derivative",10) << " | "
                << center("kD",10) << " | "
                << center("posX",10) << " | "
                << center("posY",10) << " | "
                << center("desiredX",10) << " | "
                << center("desiredY",10) << " | "
                << center("distDX",10) << " | "
                << center("distDY",10) << "\n";

            std::cout << std::string(10*11 /*Sec # = # of variables (for both terms)*/ + 2*11, '-') << "\n";

            std::cout << prd(1,1,10) << " | "
                << prd(PIDLoopNum,1,10) << " | "
                << prd(error,2,10) << " | "
                << prd(power,2,10) << " | "
                << prd(kP,2,10) << " | "
                << prd(integral,2,10) << " | "
                << prd(kI,2,10) << " | "
                << prd(derivative,2,10) << " | "
                << prd(kD,2,10) << " | "
                << prd(posX,2,10) << " | "
                << prd(posY,2,10) << " | " << "\n";
                // << prd(desiredX,2,10) << " | "
                // << prd(desiredY,2,10) << " | "
                // << prd(distDX,2,10) << " | "
                // << prd(distDY,2,10) << "\n";
    // Data Collection

    PIDLoopNum++;

    pros::delay(10);
  }
  BLM.move_voltage(0);
  FLM.move_voltage(0);
  BRM.move_voltage(0);
  FRM.move_voltage(0);
}