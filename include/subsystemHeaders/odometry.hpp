#include "api.h"

extern pros::ADIEncoder LEncoder;
extern pros::ADIEncoder REncoder;
extern pros::ADIEncoder SEncoder;

extern const double lDist;
extern const double rDist;
extern const double sDist;

extern double currentL, currentR, currentS;
extern double deltaL, deltaR, deltaS;
extern double lastDeltaL, lastDeltaR, lastDeltaS;
extern double deltaLi, deltaRi, deltaSi;
extern double totalDeltaLi, totalDeltaRi, totalDeltaSi;
extern double deltaTheta;
extern double thetaRad, thetaDeg;
extern double posX, posY;

extern double initOrientation;
extern double orientation;
extern double lastOrientation;
extern double avgOrientation;

extern double polarLength;
extern double polarTheta;

extern double deltaX, deltaY;

// Constants
  extern const double goalX;
  extern const double goalY;
// Constants

extern bool odomRunning;

extern double sec2();

extern void runOdometry();

extern double distFormula();

void PIDMove();

void PIDTurn();

extern double h;
extern double a;
extern double x;
extern double y;

double goalDistance();