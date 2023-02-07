#include "api.h"

extern bool PIDActive;
extern double const driveFactor;

extern void PIDMove(double desiredX, double desiredY, bool isReverse);
extern void PIDTurn(double desiredOrientation);
extern void PIDTurnTo(double x, double y, bool isReverse);