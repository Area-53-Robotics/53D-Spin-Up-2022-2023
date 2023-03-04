#include "api.h"
#include "sylib/sylib.hpp"

extern sylib::SpeedControllerInfo flywheel_motor_speed_controller;

extern pros::Controller Controller;
extern pros::Controller Controller2;
extern pros::Motor BLM;
extern pros::Motor FLM;
extern pros::Motor BRM;
extern pros::Motor FRM;
extern pros::Motor IntakeMotor;
extern pros::Motor IndexerMotor;
extern sylib::Motor FlywheelMotor1;
extern sylib::Motor FlywheelMotor2;
extern pros::Motor_Group LMotors;
extern pros::Motor_Group RMotors;
extern pros::Imu IMU;
extern pros::ADIEncoder LEncoder;
extern pros::ADIEncoder REncoder;
extern pros::ADIEncoder SEncoder;

extern pros::ADIDigitalOut PressurePiston;
extern pros::ADIDigitalOut ExpansionPistons;

extern unsigned short int GamePhase;