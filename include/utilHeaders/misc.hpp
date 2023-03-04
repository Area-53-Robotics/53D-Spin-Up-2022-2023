#include "api.h"

extern std::string prd(const double x, const int decDigits, const int width);
extern std::string center(const std::string s, const int w);
extern void waitUntilMoveAbsolute(pros::Motor Motor, double position, int velocity);
extern double degToRad(double degrees);
extern double radToDeg(double radians);
extern double distFormula(double x1, double y1, double x2, double y2);
extern double sec2(double theta);
extern double simplifyRadAngle(double theta);
extern int normalMotorDegToTicks(double degrees);
int normalMotorRevToTicks(double revolutions);
int VConversion(double voltage);
void printTestValue();