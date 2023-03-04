#include "api.h"

// Radius of the tracking wheels in inches
extern const double WHEEL_RADIUS;

// Distances of tracking wheels from the tracking center in inches
extern const double lDist;
extern const double rDist;
extern const double sDist;

// Starting angle relative to the field in radians
extern double initOrientation;

extern double currentL;
extern double currentR;
extern double currentS;

extern double lastL;
extern double lastR;
extern double lastS;

extern double deltaL;
extern double deltaR;
extern double deltaS;

extern double totalDeltaL;
extern double totalDeltaR;
extern double totalDeltaS;

extern double deltaTheta;

extern double orientation;
extern double lastOrientation;
extern double avgTheta;

extern double deltaXLocal;
extern double deltaYLocal;

extern double deltaXGlobal;
extern double deltaYGlobal;

extern double posX;
extern double posY;

extern double idealDiscDist;
extern double highGoalDist;
extern double lowGoalDist;

extern double teamHighGoalDist;
extern double teamDiscDist;

// Constants
  extern const double highGoalX;
  extern const double highGoalY;
  extern const double lowGoalX;
  extern const double lowGoalY;
  extern const double teamHighGoalX;
  extern const double teamHighGoalY;
// Constants

extern bool odomRunning;
extern bool odomLoopActive;

extern void runOdometry();
extern void setStartingOdomValues();
extern void resetOdomPositions(int rollerNum);
extern void odomKillSwitch();

extern const double flyDist;
extern const double flyHeight;
extern const double flyAngle;
extern const double idealDiscHeight;

extern double findDiscVelocity();
extern double findTeamDiscVelocity();

extern void odomDataCollection();