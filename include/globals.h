#include "main.h"

// Controller Setup
extern pros::Controller master;


// Motor Initialization
extern pros::Motor frontLeftMotor;
extern pros::Motor frontRightMotor;

extern pros::Motor backLeftMotor;
extern pros::Motor backRightMotor;

extern pros::Motor_Group leftDrive;
extern pros::Motor_Group rightDrive;

extern pros::Motor slapper;

// Sensor Initialization
extern pros::ADIAnalogIn lineTracker;
extern pros::ADIUltrasonic ultrasonic;

extern pros::IMU gyro;