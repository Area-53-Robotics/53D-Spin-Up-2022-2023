#include "main.h"
#include "utilHeaders/odometry.hpp"

/*
? This file contains all functions related to the robot's absolute position tracking
? system (odometry). We use a field-centric coordinate system in inches.
*/

//* Radius of the tracking wheels in inches
const double WHEEL_RADIUS = 1.379;

//* Distances of tracking wheels from the tracking center in inches
const double lDist = 3.791;
const double rDist = 4.292;
const double sDist = 2;

//* Starting angle relative to the field in radians
double initOrientation;

/*
* Angles of each tracking wheel in degrees. They are converted to
* radians for the odometry system.
*/
double currentL = 0;
double currentR = 0;
double currentS = 0;

/*
* The angles of the tracking wheel in the last loop
*/
double lastL = 0;
double lastR = 0;
double lastS = 0;

//* Distances traveled by the tracking wheels each loop in inches
double deltaL = 0;
double deltaR = 0;
double deltaS = 0;

/*
  * Distance summations of each tracking wheel since the start of
  * the program
*/
double totalDeltaL = 0;
double totalDeltaR = 0;
double totalDeltaS = 0;

//* The change in theta each loop in radians
double deltaTheta = 0;

//* The current angle of the bot in radians
double orientation;
//* The previous angle of the bot in radians
double lastOrientation;
/*
  * The average angle theta in radians throughout the arc made by
  * the robot in each loop
*/
double avgTheta;

/*
* The local changes in the X and Y positions of the robot in inches
* in every loop
*/
double deltaXLocal = 0;
double deltaYLocal = 0;

//* The X and Y offsets converted from their local forms in inches
double deltaXGlobal = 0;
double deltaYGlobal = 0;

//* The global position of the robot in inches
double posX;
double posY;

//
  double idealDiscDist;
  double highGoalDist;
  double lowGoalDist;

  double teamHighGoalDist;
  double teamDiscDist;
//

// Location Constants
  //* Coordinates of our high goal
  const double highGoalX = 17.880563; // Measured in Onshape
  const double highGoalY = 122.935637; // Measured in Onshape
  //* Coordinates of our low goal
  const double lowGoalX = 120;
  const double lowGoalY = 24;
  //
    const double teamHighGoalX = 122.935637; // Measured in Onshape
    const double teamHighGoalY = 17.880563; // Measured in Onshape
  //
// Location Constants

//* Boolean variable representing if the odometry system is active
bool odomRunning = false;
//* Boolean variable representing if the odometry loop is on delay
bool odomLoopActive = false; // Whether odom is on delay or not

/*
* This function calculates the X position, Y position, and
* and orientation of the robot in the background during the progams
* run
*/
void runOdometry() {
  odomRunning = true;

  while(odomRunning) {  
    odomLoopActive = true;

    //* Gets the angle of the tracking wheels in degrees
    currentL = LEncoder.get_value();
    currentR = REncoder.get_value();
    currentS = SEncoder.get_value();

    /*
    * Calculates the distance travelled by each tracking wheel
    * in inches since the last loop
    */
    deltaL = degToRad(currentL - lastL) * WHEEL_RADIUS;
    deltaR = degToRad(currentR - lastR) * WHEEL_RADIUS;
    deltaS = degToRad(currentS - lastS) * WHEEL_RADIUS;

    /*
    * Updates the previous positions of the encoders in degrees
    * to be used in the next loop
    */
    lastL = currentL;
    lastR = currentR;
    lastS = currentS;

    /*
    * Updates the total change of each tracking wheel in inches
    * since the start of the program
    */
    totalDeltaL += deltaL;
    totalDeltaR += deltaR;
    totalDeltaS += deltaS;

    //* Calculates the absolute orientation of the robot in radians
    orientation = initOrientation - (totalDeltaL - totalDeltaR)/(lDist + rDist);
    //* Calculate the change in the angle of the robot in radians
    deltaTheta = orientation - lastOrientation;
    //* Updatse the previous theta value in radians
    lastOrientation = orientation;

    if(deltaTheta == 0) {
      /*
      * If the robot did not turn, then the local change in position
      * can be found using the delta encoder values
      */
      deltaXLocal = deltaS;
      deltaYLocal = deltaL;
    } else {
      /*
      * Otherwise, the local change in position can be found using
      * an adaptation of the Law of Sines
      */
      deltaXLocal = 2 * ((deltaS / deltaTheta) + sDist) * sin(deltaTheta / 2.0);
      deltaYLocal = 2 * ((deltaR / deltaTheta) - rDist) * sin(deltaTheta / 2.0);
    }

    //* The average angle of the robot during it's arc in radians
    avgTheta = orientation - (deltaTheta / 2);

    /*
    * Converts the local change in position to a global change in
    * position
    */
    deltaXGlobal = (deltaYLocal * cos(avgTheta)) - (deltaXLocal * sin(avgTheta));
    deltaYGlobal = (deltaYLocal * sin(avgTheta)) + (deltaXLocal * cos(avgTheta));

    /*
    * Wraps the orientation angle back around if it ever goes under 0
    * or over 2 pi
    */
    orientation = simplifyRadAngle(orientation);

    //* Updates the global position
    posX += deltaXGlobal;
    posY += deltaYGlobal;

    //
      highGoalDist = distFormula(posX, posY, highGoalX, highGoalY);
      idealDiscDist = (highGoalDist - flyDist) * 0.0254; //Inches -> Meters
      lowGoalDist = distFormula(posX, posY, lowGoalX, lowGoalY);

      teamHighGoalDist = distFormula(posX, posY, teamHighGoalX, teamHighGoalY);
      teamDiscDist = (teamHighGoalDist - flyDist) * 0.0254; //Inches -> Meters
    //

    odomLoopActive = false;

    sylib::delay(10);
  }
}

/*
* This function sets the starting X coordinate, Y coordinate, and
* orientation of the robot in the program depending on which
* autonomous is being used.
*/
void setStartingOdomValues() {
  switch (autonSelect) {
      case 0:
        // Odom Tests
        posX = 0;
        posY = 0;
        initOrientation = simplifyRadAngle(M_PI / 2);
        break;
      case 1:
        // Left Quals
        posX = 38.218;
        posY = 13;
        initOrientation = simplifyRadAngle(3 * M_PI / 2);
        break;
      case 2:
        // Right Quals
        posX = 135;
        posY = 138;
        initOrientation = simplifyRadAngle(0);
        break;
      case 3:
        // Left Elims
        posX = 16;
        posY = 9;
        initOrientation = simplifyRadAngle(3 * M_PI / 2);
        break;
      case 4:
        // Right Elims
        posX = 135;
        posY = 138;
        initOrientation = simplifyRadAngle(0);
        break;
      case 5:
        // Full Autonomous Win Point
        posX = 38.218;
        posY = 13;
        initOrientation = simplifyRadAngle(3 * M_PI / 2);
        break;
      case 6:
        // No Auton
        posX = 135;
        posY = 138;
        initOrientation = simplifyRadAngle(3 * M_PI / 2);
        break;
      case 7:
        // Programming Skills
        posX = 16;
        posY = 9;
        initOrientation = simplifyRadAngle(3 * M_PI / 2);
        break;
  }
  orientation = initOrientation;
  lastOrientation = orientation;
  avgTheta = orientation + (deltaTheta / 2);
}

//* Allows the driver to kill the odometry background task if needed
void odomKillSwitch() {
  odomRunning = !odomRunning;
}

void resetOdomPositions(int rollerNum) {
  //! Needs to be completed
  switch (rollerNum) {
    case 1:
      posX = 1;
      posY = 1;
      initOrientation = 3 * M_PI / 2;
      orientation = initOrientation;
      totalDeltaL = 0;
      totalDeltaR = 0;
      deltaTheta = 0;
      break;
    case 2:
      posX = 1;
      posY = 1;
      initOrientation = M_PI;
      orientation = initOrientation;
      totalDeltaL = 0;
      totalDeltaR = 0;
      deltaTheta = 0;
      break;
    case 3:
      posX = 1;
      posY = 1;
      initOrientation = M_PI / 2;
      orientation = initOrientation;
      totalDeltaL = 0;
      totalDeltaR = 0;
      deltaTheta = 0;
      break;
    case 4:
      posX = 1;
      posY = 1;
      initOrientation = 0;
      orientation = initOrientation;
      totalDeltaL = 0;
      totalDeltaR = 0;
      deltaTheta = 0;
      break;
  }
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

void odomDataCollection() {
  printf("%s | %s | %s | %s | %s | %s | %s | %s \n",
    center("totalDeltaL", 14).c_str(), center("totalDeltaR", 14).c_str(), center("totalDeltaS",14).c_str(),
    center("orientation",14).c_str(), center("deltaTheta",14).c_str(), center("avgTheta",14).c_str(),
    center("posX",14).c_str(), center("posY",14).c_str());
  
  printf("%s \n", std::string(15*8 + 2*8, '-').c_str());

  while(odomRunning) {
    printf("%s | %s | %s | %s | %s | %s | %s | %s \n",
      prd(totalDeltaL,2,14).c_str(), prd(totalDeltaR,2,14).c_str(), prd(totalDeltaS,2,14).c_str(),
      prd(radToDeg(orientation),2,14).c_str(),
      prd(deltaTheta,2,14).c_str(), prd(avgTheta,2,14).c_str(), prd(posX,2,14).c_str(),
      prd(posY,2,14).c_str());

    sylib::delay(500);
  }
}