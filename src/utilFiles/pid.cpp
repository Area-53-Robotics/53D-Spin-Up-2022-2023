#include "main.h"
#include "utilHeaders/pid.hpp"

std::ofstream file;

bool PIDActive = false;
double const driveFactor = 0.8;

void PIDMove(double desiredX, double desiredY, bool isReverse) {
  while (odomActive) sylib::delay(1);
  PIDActive = true;
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

  if (!isReverse) desiredOrientation -= M_PI;

  PIDTurn(desiredOrientation);

  while (error > 0.1 || error < -0.1) {
    PIDActive = true;

    if ((orientation != desiredOrientation) && PIDLoopNum % 3 == 0) PIDTurn(desiredOrientation);

    error = distFormula(posX, posY, desiredX, desiredY);
    integral += error;
    if (error < 0) integral = 0;
    if (error > 100000000) integral = 0;
    derivative = error - prevError;
    prevError = error;
    power = error * kP + integral * kI + derivative * kD;
    if (power > 12000) power = 12000;

    if (!isReverse) {
      /*
      BLM.set_voltage(power);
      FLM.set_voltage(power);
      BRM.set_voltage(power * driveFactor);
      FRM.set_voltage(power * driveFactor);
      */
      BLM.move_voltage(power);
      FLM.move_voltage(power);
      BRM.move_voltage(power * driveFactor);
      FRM.move_voltage(power * driveFactor);
    } else {
      /*
      BLM.set_voltage(power * -1);
      FLM.set_voltage(power * -1);
      BRM.set_voltage(power * driveFactor * -1);
      FRM.set_voltage(power * driveFactor * -1);
      */
      BLM.move_voltage(power * -1);
      FLM.move_voltage(power * -1);
      BRM.move_voltage(power * driveFactor * -1);
      FRM.move_voltage(power * driveFactor * -1);
    }

    // Data Collection
      /*
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


        std::cout << std::string(10*15 + 2*15, '-') << "\n";

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
      */
      
      printf("PID Moving\n");
      printf("%s | %s | %s | %s | %s | %s | %s | %s | %s | %s | %s | %s | %s | %s | \n",
        center("Loop #",10).c_str(), center("Error",10).c_str(), center("Power",10).c_str(), center("kP",10).c_str(),
        center("integral",10).c_str(), center("kI",10).c_str(), center("derivative",10).c_str(),
        center("kD",10).c_str(), center("posX",10).c_str(), center("posY",10).c_str(),
        center("desiredX",10).c_str(), center("desiredY",10).c_str(), center("distDX",10).c_str(),
        center("distDY",10).c_str());

      printf("%s \n", std::string(10*14 + 2*14, '-').c_str());

      printf("%s | %s | %s | %s | %s | %s | %s | %s | %s | %s | %s | %s | %s | %s | \n",
        prd(PIDLoopNum,1,10).c_str(), prd(error,2,10).c_str(), prd(power,2,10).c_str(),
        prd(kP,2,10).c_str(), prd(integral,2,10).c_str(), prd(kI,2,10).c_str(),
        prd(derivative,2,10).c_str(), prd(kD,2,10).c_str(), prd(posX,2,10).c_str(),
        prd(posY,2,10).c_str(), prd(desiredX,2,10).c_str(), prd(desiredY,2,10).c_str(),
        prd(distDX,2,10).c_str(), prd(distDY,2,10).c_str());

    // Data Collection

    PIDLoopNum++;

    sylib::delay(10);
  }
  /*
  BLM.set_voltage(0);
  FLM.set_voltage(0);
  BRM.set_voltage(0);
  FRM.set_voltage(0);
  */
  BLM.move_voltage(0);
  FLM.move_voltage(0);
  BRM.move_voltage(0);
  FRM.move_voltage(0);

  printf("%s \n", std::string(10*10 + 2*10, '-').c_str());
  printf("%s \n\n", std::string(10*10 + 2*10, '-').c_str());

  PIDActive = false;
}

void PIDTurn(double desiredOrientation) {
  while (odomActive) sylib::delay(1);
  PIDActive = true;
  unsigned long long int PIDLoopNum = 1;

  double kP = 0;
  double error = 0;
  double power = 0;
  double integral = 0;
  double kI = 0;
  double derivative = 0;
  double prevError = 0;
  double kD = 0;

  while (error > 0.1 || error < -0.1) {
    PIDActive = true;

    error = desiredOrientation - orientation;
    integral += error;
    if (error < 0) integral = 0;
    if (error > 100000000) integral = 0;
    derivative = error - prevError;
    prevError = error;
    power = error * kP + integral * kI + derivative * kD;
    if (power > 12000) power = 12000;

    if (desiredOrientation - orientation > 0) {
      /*
      BLM.set_voltage(power * -1);
      FLM.set_voltage(power * -1);
      BRM.set_voltage(power * driveFactor);
      FRM.set_voltage(power * driveFactor);
      */
      BLM.move_voltage(power * -1);
      FLM.move_voltage(power * -1);
      BRM.move_voltage(power * driveFactor);
      FRM.move_voltage(power * driveFactor);
    } else {
      /*
      BLM.set_voltage(power);
      FLM.set_voltage(power);
      BRM.set_voltage(power * driveFactor * -1);
      FRM.set_voltage(power * driveFactor * -1);
      */
      BLM.move_voltage(power);
      FLM.move_voltage(power);
      BRM.move_voltage(power * driveFactor * -1);
      FRM.move_voltage(power * driveFactor * -1);  
    }

    // Data Collection
      printf("PID Turning\n");
      printf("%s | %s | %s | %s | %s | %s | %s | %s | %s | %s |\n",
        center("Loop #",14).c_str(), center("Error",14).c_str(), center("Power",14).c_str(),
        center("kP",14).c_str(), center("integral",14).c_str(), center("kI",14).c_str(),
        center("derivative",14).c_str(), center("kD",14).c_str(), center("orientation",14).c_str(),
        center("desOrientation",14).c_str());
        
      printf("%s \n", std::string(10*10 + 2*10, '-').c_str());

      printf("%s | %s | %s | %s | %s | %s | %s | %s | %s | %s |\n",
        prd(PIDLoopNum,1,10).c_str(), prd(error,2,10).c_str(), prd(power,2,10).c_str(),
        prd(kP,2,10).c_str(), prd(integral,2,10).c_str(), prd(kI,2,10).c_str(),
        prd(derivative,2,10).c_str(), prd(kD,2,10).c_str(), prd(orientation,2,10).c_str(),
        prd(desiredOrientation,2,10).c_str());
    // Data Collection

    PIDLoopNum++;

    sylib::delay(10);
  }
  /*
  BLM.set_voltage(0);
  FLM.set_voltage(0);
  BRM.set_voltage(0);
  FRM.set_voltage(0);
  */
  BLM.move_voltage(0);
  FLM.move_voltage(0);
  BRM.move_voltage(0);
  FRM.move_voltage(0);

  printf("%s \n", std::string(10*10 + 2*10, '-').c_str());
  printf("%s \n\n", std::string(10*10 + 2*10, '-').c_str());

  PIDActive = false;
}

void PIDTurnTo(double x, double y, bool isReverse) {
  double distDX = x - posX;
  double distDY = y - posY;
  double desiredOrientation = orientation - atan2(distDY, distDX);
  if (isReverse) desiredOrientation -= M_PI;
  PIDTurn(desiredOrientation);
}