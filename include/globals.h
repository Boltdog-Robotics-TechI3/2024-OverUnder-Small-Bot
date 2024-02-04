#include "main.h"

// Controller Setup
extern pros::Controller master;


// Motor Initialization
extern pros::Motor catapult;

extern pros::Motor frontLeftMotor;

extern pros::Motor frontRightMotor;
extern pros::Motor backLeftMotor;
extern pros::Motor backRightMotor;

extern pros::Motor_Group leftSideMotors;
extern pros::Motor_Group rightSideMotors;

extern pros::Motor leftLiftMotor;
extern pros::Motor rightLiftMotor;
extern pros::Motor_Group lift;

extern pros::Motor intake;

// Sensor Initialization
extern pros::ADIAnalogIn lineTracker;
extern pros::ADIUltrasonic ultrasonic;

extern pros::IMU gyro;