#include "main.h"
#include "utilHeaders/pid.hpp"

/*
? All PID movement functions used in the drivetrain
*/

//* Boolean variable representing whether a PID movement is active
bool PIDActive = false;
/*
* Factor to reduce the speed of the right drive to balance out
* robot drift.
*/
const double rightDriveFactor = 0.84;

/*
* The robot turns toward and drives to the given X and Y coordinates.
* If isReverse is set to true, the robot will do this while treating
* the back of the robot (flywheel side) as the front.
*/
void PIDMove(double desiredX, double desiredY, bool isReverse) {
  /*
  * The robot waits until the current odometry loop is finished
  * to start the PID so that the orientation data is accurate.
  */
  while (odomLoopActive) sylib::delay(1);
  PIDActive = true;
  //* How many loops the PID has gone through since the PID started
  unsigned long long int PIDLoopNum = 1;
  //* How many loops the error of the PID loop has remained constant
  unsigned long long int sameErrorCount = 0;

  /*
  * Constant to multiply the distance between the desired
  * position and the current position by. If the difference
  * is large, this value will be large and will request a large
  * amount of voltage from the drivetrain motors.
  */
  double const kP = 460;
  /*
  * Calculates the initial distance between the desired position
  * and the robots current position using the distance formula
  */
  double error = distFormula(posX, posY, desiredX, desiredY);
  /*
  * Power in millivolts supplied to the drive motors calculated in
  * each PID loop
  */
  double power = 0;
  //* Rate of change of the PID movement
  double derivative = 0;
  //* The error in the previous loop
  double prevError = error;
  /*
  * Constant to multiply the rate of change of the movement by. If the
  * movement is happening too fast, this will slow down the movement
  * slightly.
  */
  double const kD = 0;

  /*
  * Calculates the difference in X position between the desired position
  * and the robots current position
  */
  double distDX = desiredX - posX;
  /*
  * Calculates the difference in Y position between the desired position
  * and the robots current position
  */
  double distDY = desiredY - posY;
  /*
  * Calculates the orientation the robot needs to face to drive
  * forward to the desired position
  */
  double desiredOrientation = orientation - atan2(distDX, distDY);

  /*
  * If the robot is set to do this reversed, the orientation is
  * subtracted by pi to make the flywheel face the desired position
  */
  if (isReverse) desiredOrientation -= M_PI;

  //* The robot turns toward the desired position
  PIDTurn(desiredOrientation);

  //* The coordinates of the robot when the PID loop is started
  double const OGposX = posX;
  double const OGposY = posY;
  /*
    * The distance between the starting position of the robot and the
    * desired position
  */
  double const targetPointDist = distFormula(OGposX, OGposY, desiredX, desiredY);
  /*
  * The distance from the original position of the robot to the current
  * position of the robot.
  */
  double traveledDist = 0;

  //
    printf("PID Moving\n");
    printf("kP: %f\n", kP);
    printf("kD: %f\n", kD);
    printf("%s | %s | %s | %s | %s | %s | %s | %s | %s | %s | %s | %s \n",
      center("Loop #",10).c_str(), center("Error",10).c_str(), center("Power",10).c_str(),
      center("P Term",10).c_str(), center("derivative",10).c_str(), center("D Term",10).c_str(),
      center("posX",10).c_str(), center("posY",10).c_str(), center("distDX",10).c_str(), center("distDY",10).c_str(),
      center("desOri", 10).c_str(), center("ori", 10).c_str());

    printf("%s \n", std::string(11*12 + 2*12, '-').c_str());
  //

  while (fabs(error) > 0.1) {
    PIDActive = true;

    /*
    * Updates the distance from the original position of the robot at
    * the start of the PID function to the current position of the robot.
    */
    traveledDist = distFormula(OGposX, OGposY, posX, posY);

    /*
    * Updates the difference between the desired position and the
    * robot's position
    */
    error = targetPointDist - traveledDist;
    /*
    * If the error was the same as the last loop, the counter
    * increases. Otherwise, it is set to 0.
    */
    if (error == prevError) sameErrorCount++;
    else sameErrorCount = 0;
    //* Calculates the rate of change (derivative) of the turn
    derivative = error - prevError;
    //* Updates the previous error for the next loop
    prevError = error;
    /*
    * Calculates the power supplied to the drive motors based on
    * the proportional term and derivative term
    */
    power = (error * kP) + (derivative * kD);
    //* If the requested power exceeds 12000 mV, it is set to 12000 mV
    if (power > 12000) power = 12000;
    else if (power < -12000) power = -12000;

    if (!isReverse) {
      /*
      * If the PID is not set to reverse, the robot applies the
      * requested voltage to drive towards the desired position. The
      * right motors voltage is multiplied by a factor to counteract the
      * drift of the robot.
      */
      LMotors.move_voltage(power);
      RMotors.move_voltage(power * rightDriveFactor);
    } else {
      /*
      * If the PID is set to reverse, the robot moves backward to get to
      * its desired position.
      */
      LMotors.move_voltage(power * -1);
      RMotors.move_voltage(power * -1 * rightDriveFactor);
    }

    /*
    * If the error of the PID has remained constant for 20 loops,
    * the PID has reached equilibrium and will stop moving. The PID
    * is then exited to prevent it from blocking the rest of the
    * program.
    */
    if (sameErrorCount > 20) break;

    //
      if (PIDLoopNum % 3 == 0) {
      printf("%s | %s | %s | %s | %s | %s | %s | %s | %s | %s | %s | %s \n",
        prd(PIDLoopNum,1,10).c_str(), prd(error,2,10).c_str(), prd(power,2,10).c_str(),
        prd(kP * error,2,10).c_str(), prd(derivative,2,10).c_str(), prd(kD * derivative,2,10).c_str(),
        prd(posX,2,10).c_str(), prd(posY,2,10).c_str(), prd(distDX,2,10).c_str(),
        prd(distDY,2,10).c_str(), prd(desiredOrientation, 3, 10).c_str(), prd(orientation, 3, 10).c_str());
      }

      pros::lcd::print(1, "PIDLoopNum: %d", PIDLoopNum);
      pros::lcd::print(2, "Error: %f", error);
      pros::lcd::print(3, "Power: %f", power);
      pros::lcd::print(4, "kP: %f", kP);
      pros::lcd::print(5, "Derivative: %f", derivative);
      pros::lcd::print(6, "kD: %f", kD);
      pros::lcd::print(7, "posX: %f", posX);
      pros::lcd::print(8, "posY: %f", posY);
      pros::lcd::print(9, "distDX: %f", distDX);
      pros::lcd::print(10, "distDY: %f", distDY);
    //

    PIDLoopNum++;

    sylib::delay(10);
  }
  //* After the PID loop is finished, the voltage of the motors is 0
  LMotors.move_voltage(0);
  RMotors.move_voltage(0);

  //
    printf("%s \n", std::string(10*10 + 2*10, '-').c_str());
    printf("%s \n\n", std::string(10*10 + 2*10, '-').c_str());
  //

  PIDActive = false;
}

/*
  ? The robot turns to the given absolute orientation in radians.
*/
void PIDTurn(double desiredOrientation) {
  /*
  * The robot waits until the current odometry loop is finished
  * to start the PID so that the orientation data is accurate.
  */
  while (odomLoopActive) sylib::delay(1);
  PIDActive = true;
  //* How many loops the PID has gone through since the PID started
  unsigned long long int PIDLoopNum = 1;
  //* How many loops the error of the PID loop has remained constant
  unsigned long long int sameErrorCount = 0;

  /*
  * Constant to multiply the difference between the desired
  * orientation and the current orientation by. If the difference
  * is large, this value will be large and will request a large
  * amount of voltage from the drivetrain motors.
  */
  double const kP = 25000;
  /*
  * Calculates the initial difference between the desired orientation
  * and the robots current orientation
  */
  double error = desiredOrientation - orientation;
  /*
  * Power in millivolts supplied to the drive motors calculated in
  * each PID loop
  */
  double power = 0;
  //* Rate of change of the PID turn
  double derivative = 0;
  //* The error in the previous loop
  double prevError = error;
  /*
  * Constant to multiply the rate of change of the turn by. If the
  * turn is happening too fast, this will slow down the turn slightly.
  */
  double const kD = 152000;

  // Simplifies the desired orientation  between 0 and 2 pi
  desiredOrientation = simplifyRadAngle(desiredOrientation);

  // /*
      printf("PID Turning\n");
      printf("kP: %f\n", kP);
      printf("kD: %f\n", kD);
      printf("%s | %s | %s | %s | %s | %s | %s | %s |\n",
        center("Loop #",11).c_str(), center("Error",11).c_str(), center("Power",11).c_str(),
        center("P Term",11).c_str(), center("derivati",11).c_str(), center("D Term",11).c_str(),
        center("orientat",11).c_str(), center("desOrient",11).c_str());
        
      printf("%s \n", std::string(11*8 + 2*8, '-').c_str());
  // */
      
  while (fabs(error) > 0.01) {
    PIDActive = true;

    /*
    * Updates the difference between the desired orientation and
    * the robot's orientation
    */
    error = desiredOrientation - orientation;

    /*
    * Adjusts the error so that the robot turns the smallest amount
    * of degrees needed to reach its desired orientation
    */
    if (error > 0 && error <= M_PI) error = error;
    else if (error > 0 && error > M_PI) error = ((2 * M_PI) - error) * -1;
    else if (error < 0 && fabs(error) <= M_PI) error = error;
    else if (error < 0 && fabs(error) > M_PI) error = simplifyRadAngle((2 * M_PI) - error);

    /*
    * If the error was the same as the last loop, the counter
    * increases. Otherwise, it is set to 0.
    */
    if (error == prevError) sameErrorCount++;
    else sameErrorCount = 0;

    //* Calculates the rate of change (derivative) of the turn
    derivative = error - prevError;
    //* Updates the previous error for the next loop
    prevError = error;
    /*
    * Calculates the power supplied to the drive motors based on
    * the proportional term and derivative term
    */
    power = (error * kP) + (derivative * kD);
    //* If the requested power exceeds 12000 mV, it is set to 12000 mV
    if (power > 12000) power = 12000;
    else if (power < -12000) power = -12000;

    //* The requested voltage is then sent to the motors
    LMotors.move_voltage(power * -1);
    RMotors.move_voltage(power);

    /*
    * If the error of the PID has remained constant for 20 loops,
    * the PID has reached equilibrium and will stop moving. The PID
    * is then exited to prevent it from blocking the rest of the
    * program.
    */
    if (sameErrorCount > 20) break;

    //
      // /*
      if (PIDLoopNum % 1 == 0) {
      printf("%s | %s | %s | %s | %s | %s | %s | %s |\n",
        prd(PIDLoopNum,1,11).c_str(), prd(error,2,11).c_str(), prd(power,2,11).c_str(),
        prd(kP * error,2,11).c_str(), prd(derivative,2,11).c_str(), prd(kD * derivative,2,11).c_str(),
        prd(radToDeg(orientation),2,11).c_str(), prd(radToDeg(desiredOrientation),2,11).c_str());
      }
      // */
      pros::lcd::print(1, "orientation: %f", degToRad(orientation));
    //

    PIDLoopNum++;

    sylib::delay(10);
  }
  //* After the PID loop is finished, the voltage of the motors is 0
  LMotors.move_voltage(0);
  RMotors.move_voltage(0);

  //
    printf("%s \n", std::string(10*10 + 2*10, '-').c_str());
    printf("%s \n\n", std::string(10*10 + 2*10, '-').c_str());
  //

  PIDActive = false;
}

/*
* The robot turns to face the point at the given X and Y coordinates.
* If isReverse is set to true, the robot will do this while treating the back of the robot (flywheel side) as the front.
*/
void PIDTurnTo(double x, double y, bool isReverse) {
  /*
  * Calculates the difference in X values between the robots position
  * and the lookahead point.
  */
  double distDX = x - posX;
  /*
  * Calculates the difference in Y values between the robots position
  * and the lookahead point.
  */
  double distDY = y - posY;
  /*
  * Calculates the orientation in radians needed for the robot to face
  * the lookahead point.
  */
  double desiredOrientation = orientation - atan2(distDY, distDX);
  /*
  * If the robot is set to do this reversed, the orientation is
  * subtracted by pi to make the flywheel face the lookahead point
  */
  if (isReverse) desiredOrientation -= M_PI;
  /*
  * Calls the PID turn function to turn the robot to the desired
  * orientation
  */
  PIDTurn(desiredOrientation);
}