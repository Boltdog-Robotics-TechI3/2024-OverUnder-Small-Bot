#include "main.h"

// Controller Setup
pros::Controller master(pros::E_CONTROLLER_MASTER);


// Motor Initialization

// Drivetrain
pros::Motor frontLeftMotor(19, MOTOR_GEAR_BLUE, true, MOTOR_ENCODER_COUNTS);
pros::Motor frontRightMotor(12, MOTOR_GEAR_BLUE, false, MOTOR_ENCODER_COUNTS);
pros::Motor backLeftMotor(20, MOTOR_GEAR_BLUE, true, MOTOR_ENCODER_COUNTS);
pros::Motor backRightMotor(11, MOTOR_GEAR_BLUE, false, MOTOR_ENCODER_COUNTS);

pros::Motor_Group leftDrive({frontLeftMotor, backLeftMotor});
pros::Motor_Group rightDrive({frontRightMotor, backRightMotor});

// Catapult
pros::Motor catapult(18, MOTOR_GEAR_GREEN, false, MOTOR_ENCODER_COUNTS);

// Wings
pros::Motor wings(10, MOTOR_GEAR_GREEN, true, MOTOR_ENCODER_COUNTS);

// Sensor Initialization
pros::IMU gyro(8);