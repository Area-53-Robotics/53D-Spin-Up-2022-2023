#include "main.h"
#include "utilHeaders/misc.hpp"

/*
? Miscellaneous functions used throughout the program.
*/

/*
* This function prints a rounded decimal value with a specified
* number of spaces around it. This function is used to tabulate
* information.
*/
std::string prd(const double x, const int decDigits, const int width) {
    std::stringstream ss;
    ss << std::fixed << std::right;
    ss.fill(' ');        // fill space around displayed #
    ss.width(width);     // set  width around displayed #
    ss.precision(decDigits); // set # places after decimal
    ss << x;
    return ss.str();
}

/*
* This function prints a string with a specified number of spaces
* around it. This function is also used to tabulate information.
*/
std::string center(const std::string s, const int w) {
    std::stringstream ss, spaces;
    int padding = w - s.size();                 // count excess room to pad
    for(int i=0; i<padding/2; ++i)
        spaces << " ";
    ss << spaces.str() << s << spaces.str();    // format with padding
    if(padding>0 && padding%2!=0)               // if odd #, add 1 space
        ss << " ";
    return ss.str();
}

/*
* This function delays the program until the specified motor has
* rotated to the specified position.
*/
void waitUntilMoveAbsolute(pros::Motor Motor, double position, int velocity) {
    int count = 1;
    Motor.move_absolute(position, velocity);
    while (!((Motor.get_position() < (position + 5)) && (Motor.get_position() > (position - 5))) && count < 1000) {
        count++;
        sylib::delay(2);
    }
}

//* This function converts degrees to radians.
double degToRad(double degrees) {
  return degrees * M_PI / 180;
}

//* This function converts radians to degrees.
double radToDeg(double radians) {
  return radians * 180 / M_PI;
}

/*
* This function calculates the distance between a point with
* coordinates (x1, x2) and a point with coordinates (x2, y2).
*/
double distFormula(double x1, double y1, double x2, double y2) {
  return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}

/*
* This function calculates the secant of an angle in radians and
* squares it.
*/
double sec2(double theta) {
  return 1 / pow(cos(theta), 2);
}

/*
* This function simplifies an angle in radians until it is within
* the interval [0, 2 * PI)
*/
double simplifyRadAngle(double theta) {
  /*
  * While the angle is greater than or equal to 2 * PI, the angle
  * is subtracted by 2 * PI.
  */
  while(theta >= 2 * M_PI) {
    theta -= 2 * M_PI;
  }
  
  /*
  * While the angle is less than 2 * PI, the angle is subtracted
  * by 2 * PI.
  */
  while(theta < 0) {
    theta += 2 * M_PI;
  }
  return theta;
}

/*
  1800 ticks/rev with 36:1 gearing (torque)
  900 ticks/rev with 18:1 gearing (normal)
  300 ticks/rev with 6:1 gearing (speed)
*/
int normalMotorDegToTicks(double degrees) {
  return degrees * 900/360;
}

int normalMotorRevToTicks(double revolutions) {
  return revolutions * 900;
}

int VConversion(double voltage) {
  return voltage * 12000 / 127;
}

void printTestValue() {
  /*
  std::cout << "Target Velo: " << targetFWMSpeed << std::endl;
  // std::cout << "kP: " << k
  std::cout << center("FWM1 Velo",10)       << " | "
            << center("FWM1 Volt",10)       << " | "
            << center("FWM2 Velo",10)       << " | "
            << center("FWM2 Volt",10)       << "\n";
  
  std::cout << std::string(10*4 + 4*2, '-') << "\n";

  while (true) {
    std::cout << prd(FlywheelMotor1.get_velocity(),3,10)     << " | "
              << prd(FlywheelMotor1.get_applied_voltage(),3,10)     << " | "
              << prd(FlywheelMotor2.get_velocity(),3,10)     << " | "
              << prd(FlywheelMotor2.get_applied_voltage(),3,10)     << "\n";
    
    pros::delay(50);
  }
  */
  std::cout << center("Velo", 10) << " | "
            << center("Error", 10) << " | "
            << center("Volt", 10) << " | "
            << center("V Term", 10) << " | "
            << center("P Term", 10) << "\n";
            
  std::cout << std::string(10*4 + 4*2, '-') << "\n";

  while(true) {
    /*
  std::cout << prd(FlywheelMotor1.get_velocity(), 3, 10) << " | "
            << prd(FlywheelMotor1.get_velocity_error(), 3, 10) << " | "
            << prd(FlywheelMotor1.get_applied_voltage(), 3, 10) << " | "
            << prd(FlywheelMotor1.get_estimator_voltage(), 3, 10) << " | "
            << prd(FlywheelMotor1.get_p_voltage(), 3, 10) << "\n";
    std::cout << LEncoder.get_value() << std::endl;
    std::cout << REncoder.get_value() << std::endl;
    std::cout << "-------------------" << std::endl;
    */
  
  std::cout << FlywheelMotorSpeed << std::endl;
  std::cout << FlywheelSpinning << std::endl;
  std::cout << "---------------------" << std::endl;
  pros::delay(100);
  }
}