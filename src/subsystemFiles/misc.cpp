#include "main.h"
#include "subsystemHeaders/misc.hpp"

std::string prd(const double x, const int decDigits, const int width) {
    // using namespace std;
    std::stringstream ss;
    ss << std::fixed << std::right;
    ss.fill(' ');        // fill space around displayed #
    ss.width(width);     // set  width around displayed #
    ss.precision(decDigits); // set # places after decimal
    ss << x;
    return ss.str();
}

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

double degToRad(double degrees) {
  return degrees * M_PI / 180;
}

double radToDeg(double radians) {
  return radians * 180 / M_PI;
}

double distFormula(double x1, double y1, double x2, double y2) {
  return sqrt(pow((x2 - x1), 2) + pow((y2-y1), 2));
}

double sec2(double theta) {
  return 1 / pow(cos(theta), 2);
}

double simplifyAngle(double theta) {
  while(theta >= 2 * M_PI) {
    theta -= 2 * M_PI;
  }
  
  while(theta < 0) {
    theta += 2 * M_PI;
  }
  return theta;
}

void odomDataCollection() {
  /*
  std::cout << center("totalDeltaL",14) << " | "
            // << center("totalDeltaR",14) << " | "
            << center("totalDeltaS",14) << " | "
            << center("IMU Heading", 14) << " | "
            << center("orientation",14) << " | "
            << center("deltaTheta",14) << " | "
            << center("avgTheta",14) << " | "
            << center("posX",14) << " | "
            << center("posY",14) << " | " << "\n";
    
  std::cout << std::string(15*8 + 2*8, '-') << "\n";
  */

  printf("%s | %s | %s | %s | %s | %s | %s | %s | \n",
    center("totalDeltaL", 14).c_str(), center("totalDeltaS",14).c_str(), center("IMU Heading", 14).c_str(),
    center("orientation",14).c_str(), center("deltaTheta",14).c_str(), center("avgTheta",14).c_str(),
    center("posX",14).c_str(), center("posY",14).c_str());
  
  printf("%s \n", std::string(15*8 + 2*8, '-').c_str());

  while(odomRunning) {
    /*
    std::cout << prd(totalDeltaL,1,14) << " | "
              // << prd(totalDeltaR,1,14) << " | "
              << prd(totalDeltaS,2,14) << " | "
              << prd(IMU.get_heading(),0,14) << " | "
              << prd(radToDeg(orientation),2,14) << " | "
              << prd(deltaTheta,2,14) << " | "
              << prd(avgTheta,2,14) << " | "
              << prd(posX,2,14) << " | "
              << prd(posY,2,14) << " | " << "\n";

    file2.open("/usd/OdomData.txt");
    */

    /*
    std::cout << "totalDeltaL = " << totalDeltaL << std::endl;
    // std::cout << "totalDeltaR = " << totalDeltaR << std::endl;
    std::cout << "totalDeltaS = " << totalDeltaS << std::endl;
    std::cout << "orientation = " << orientation << std::endl;
    std::cout << "deltaTheta = " << deltaTheta << std::endl;
    std::cout << "avgTheta = " << avgTheta << std::endl;
    std::cout << "posX = " << posX << std::endl;
    std::cout << "posY = " << posY << std::endl;
    */

    printf("%s | %s | %s | %s | %s | %s | %s | %s | \n",
      prd(totalDeltaL,1,14).c_str(), prd(totalDeltaS,2,14).c_str(),
      prd(IMU.get_heading(),0,14).c_str(), prd(radToDeg(orientation),2,14).c_str(),
      prd(deltaTheta,2,14).c_str(), prd(avgTheta,2,14).c_str(), prd(posX,2,14).c_str(),
      prd(posY,2,14).c_str());

    pros::delay(50);
  }
}