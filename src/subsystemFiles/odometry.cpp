#include "main.h"
#include "pros/rtos.hpp"
#include <cmath>

pros::ADIEncoder LEncoder(1, 2, false);
pros::ADIEncoder REncoder(3, 4, true);
pros::ADIEncoder SEncoder(5, 6, false);

const double lDist = 7;
const double rDist = 7;
const double sDist = 7;

double currentL = 0, currentR = 0, currentS = 0;
double deltaL = 0, deltaR = 0, deltaS = 0;
double lastDeltaL = 0, lastDeltaR = 0, lastDeltaS = 0;
double deltaLi = 0, deltaRi = 0, deltaSi = 0;
double totalDeltaLi = 0, totalDeltaRi = 0, totalDeltaSi = 0;
double deltaTheta = 0;
double thetaRad = 0, thetaDeg = 0;
double posX = 0, posY = 0;

double initOrientation = 0;
double orientation = 0;
double lastOrientation = 0;
double avgOrientation = 0;

double polarLength = 0;
double polarTheta = 0;

double deltaX = 0, deltaY = 0;

// Constants
  const double goalX = 0.5;
  const double goalY = 15.5;
// Constants

// double desiredX = 0, desiredY = 0, desiredOrientation = 0;

bool odomRunning = false;

double sec2(double theta) {
  return 1 / pow(cos(theta), 2);
}

void runOdometry() {
  odomRunning = true;

  while(odomRunning) {

    // remember to add bearings to the tracking wheels and use screw joints when attaching
    
    currentL = LEncoder.get_value();
    currentR = REncoder.get_value();
    currentS = SEncoder.get_value();

    deltaL = currentL - lastDeltaL;
    deltaR = currentR - lastDeltaR;
    deltaS = currentS - lastDeltaS;

    deltaLi = deltaL * 1.375;
    deltaRi = deltaR * 1.375;
    deltaSi = deltaS * 1.375;

    totalDeltaLi += deltaLi;
    totalDeltaRi += deltaRi;
    totalDeltaSi += deltaSi;

    orientation = initOrientation + (totalDeltaLi - totalDeltaRi)/(lDist + rDist);
    thetaRad = orientation - lastOrientation;
    thetaDeg = thetaRad * 180 / M_PI;

    orientation = initOrientation + thetaRad;
    deltaTheta = orientation - lastOrientation;

    deltaY = 2 * ((deltaRi / thetaRad) + rDist) * sin(thetaRad / 2);
    deltaX = 2 * ((deltaSi / thetaRad) + sDist) * sin(thetaRad / 2);

    avgOrientation = lastOrientation + (deltaTheta / 2);

    polarLength = sqrt(pow(posY, 2) + pow(posX, 2));
    polarTheta = atan2(posY, posX);

    polarTheta -= avgOrientation;
    
    deltaX = polarLength * cos(polarTheta);
    deltaY = polarLength * sin(polarTheta);

    posY += deltaY;
    posX += deltaX;

    lastDeltaL = LEncoder.get_value();
    lastDeltaR = REncoder.get_value();
    lastDeltaS = SEncoder.get_value();
    lastOrientation = orientation;

    pros::delay(10);
  }
}

double distFormula(double x1, double x2, double y1, double y2) {
  return sqrt(pow((x2 - x1), 2) + pow((y2-y1), 2));
}

void PIDMove(double desiredX, double desiredY) {
  double kP = 0;
  double error = 0;
  double power = 0;
  double integral;
  double kI;
  double derivative;
  double prevError;
  double kD;

  double distDX = desiredX - posX;
  double distDY = desiredY - posY;
  double desiredOrientation = atan2(distDY, distDX) + orientation;

  while (error > 10) {
    error = desiredOrientation - orientation;
    integral += error;
    if (error < 0) integral = 0;
    if (error > 100) integral = 0;
    derivative = error - prevError;
    prevError = error;
    power = error * kP + integral * kI + derivative * kD;
    
    BLM.move(power);
    FLM.move(power);
    BRM.move(power);
    FRM.move(power);
    pros::delay(15);
  }

  // double desiredDistance = 
  
  // double error = 
}

void PIDTurn(double d) {
  //
}

double h = 13;
double a = M_PI / 4;
double x = 4.264;
double y = 0.7408;

double goalDistance() {
  return sqrt((-1 * (4.9 * pow(x, 2) * sec2(a))) / (y - (0.0254 * h) - (x * tan(a))));
}