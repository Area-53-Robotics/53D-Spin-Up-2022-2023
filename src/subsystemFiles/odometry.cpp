#include "main.h"
#include "subsystemHeaders/odometry.hpp"

// Radius of the tracking wheels in inches
const double WHEEL_RADIUS = 1.379;

// Distances of tracking wheels from the tracking center in inches
const double lDist = 6.8335;
// const double rDist = 6.8335;
const double sDist = 5.85;

// Starting angle relative to the field in radians
const double initOrientation = M_PI;

double currentL = 0;
// double currentR = 0;
double currentS = 0;

double deltaL = 0;
// double deltaR = 0;
double deltaS = 0;

double lastL = 0;
// double lastR = 0;
double lastS = 0;

double totalDeltaL = 0;
// double totalDeltaR = 0;
double totalDeltaS = 0;

double deltaTheta = 0;

double orientation;
double lastOrientation;
double avgTheta = orientation + (deltaTheta / 2);

double deltaXLocal = 0;
double deltaYLocal = 0;

double deltaXGlobal = 0;
double deltaYGlobal = 0;

double posX = 56.5;
double posY = 8.5;

double x;
double goalDist;

// std::ofstream file2;

// Constants
  const double goalX = 15.12;
  const double goalY = 127.92;
// Constants

// double desiredX = 0, desiredY = 0, desiredOrientation = 0;

bool odomRunning = false; // Overall odom running
bool odomActive = false; // Whether odom is on delay or not

void runOdometry() {
  odomRunning = true;

  while(odomRunning) {  
    odomActive = true;

    currentL = LEncoder.get_value();
    // currentR = REncoder.get_value();
    currentS = SEncoder.get_value();

    deltaL = degToRad(currentL - lastL) * WHEEL_RADIUS;
    // deltaR = degToRad(currentR - lastR) * WHEEL_RADIUS;
    deltaS = degToRad(currentS - lastS) * WHEEL_RADIUS;

    lastL = currentL;
    // lastR = currentR;
    lastS = currentS;

    totalDeltaL += deltaL;
    // totalDeltaR += deltaR;
    totalDeltaS += deltaS;

    // orientation = initOrientation - (totalDeltaL - totalDeltaR)/(lDist + rDist);
    orientation = degToRad(360 - IMU.get_heading());
    deltaTheta = orientation - lastOrientation;
    lastOrientation = orientation;

    if(deltaTheta == 0) {
      deltaXLocal = deltaS;
      deltaYLocal = deltaL;
    } else {
      deltaXLocal = 2 * ((deltaS / deltaTheta) + sDist) * sin(deltaTheta / 2);
      deltaYLocal = 2 * ((deltaL / deltaTheta) - lDist) * sin(deltaTheta / 2);
    }

    avgTheta = orientation - (deltaTheta / 2);

    deltaXGlobal = (deltaYLocal * cos(avgTheta)) - (deltaXLocal * sin(avgTheta));
    deltaYGlobal = (deltaYLocal * sin(avgTheta)) + (deltaXLocal * cos(avgTheta));

    while(orientation >= 2 * M_PI) {
      orientation -= 2 * M_PI;
    }
    
    while(orientation < 0) {
      orientation += 2 * M_PI;
    }

    posX += deltaXGlobal;
    posY += deltaYGlobal;

    goalDist = distFormula(posX, posY, goalX, goalY);
    x = ((goalDist * 12) - fDist) * 0.0254; // Feet -> Inches -> Meters

    odomActive = false;

    pros::delay(10);
  }
}

void odomKillSwitch() {
  odomRunning = !odomRunning;
}

const double fDist = 5;
const double h = 12; //measured with ruler
const double a = M_PI / 4;
const double y = 0.715;

double goalDistance() {
  return sqrt((4.9 * pow(x, 2) * sec2(a)) / ((0.0254 * h) + (x * tan(a)) - y));
}