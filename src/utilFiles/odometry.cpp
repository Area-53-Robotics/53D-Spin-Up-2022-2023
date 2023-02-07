#include "main.h"
#include "utilHeaders/odometry.hpp"

//* Radius of the tracking wheels in inches
const double WHEEL_RADIUS = 1.379;

//* Distances of tracking wheels from the tracking center in inches
const double lDist = 6.8335;
// const double rDist = 6.8335;
const double sDist = 5.85;

//* Starting angle relative to the field in radians
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
double avgTheta;

double deltaXLocal = 0;
double deltaYLocal = 0;

double deltaXGlobal = 0;
double deltaYGlobal = 0;

double posX;
double posY;

double idealDiscDist;
double highGoalDist;
double lowGoalDist;

double teamHighGoalDist;
double teamDiscDist;

// std::ofstream file2;

// Location Constants
  const double highGoalX = 17.880563; // Measured in Onshape
  const double highGoalY = 122.935637; // Measured in Onshape
  const double lowGoalX = 120;
  const double lowGoalY = 24;
  const double teamHighGoalX = 122.935637; // Measured in Onshape
  const double teamHighGoalY = 17.880563; // Measured in Onshape
// Location Constants

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

    simplifyAngle(orientation);

    posX += deltaXGlobal;
    posY += deltaYGlobal;

    highGoalDist = distFormula(posX, posY, highGoalX, highGoalY);
    idealDiscDist = (highGoalDist - flyDist) * 0.0254; //Inches -> Meters
    lowGoalDist = distFormula(posX, posY, lowGoalX, lowGoalY);

    teamHighGoalDist = distFormula(posX, posY, teamHighGoalX, teamHighGoalY);
    teamDiscDist = (teamHighGoalDist - flyDist) * 0.0254; //Inches -> Meters

    odomActive = false;

    sylib::delay(10);
  }
}

void odomKillSwitch() {
  odomRunning = !odomRunning;
}

const double flyDist = 5;
const double flyHeight = 12; //measured with ruler
const double flyAngle = M_PI / 4;
const double idealDiscHeight = 0.715;

double findDiscVelocity() {
  return sqrt((4.9 * pow(idealDiscDist, 2) * sec2(flyAngle)) / ((0.0254 * flyHeight) + (idealDiscDist * tan(flyAngle)) - idealDiscHeight));
}

double findTeamDiscVelocity() {
  return sqrt((4.9 * pow(teamDiscDist, 2) * sec2(flyAngle)) / ((0.0254 * flyHeight) + (teamDiscDist * tan(flyAngle)) - idealDiscHeight));
}