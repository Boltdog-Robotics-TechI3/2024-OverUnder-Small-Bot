#include "main.h"

// Controller Setup
pros::Controller master(pros::E_CONTROLLER_MASTER);


// Motor Initialization

// Drivetrain
pros::Motor frontLeftMotor(15, MOTOR_GEAR_BLUE, true, MOTOR_ENCODER_COUNTS);
pros::Motor frontRightMotor(17, MOTOR_GEAR_BLUE, false, MOTOR_ENCODER_COUNTS);
pros::Motor backLeftMotor(14, MOTOR_GEAR_BLUE, true, MOTOR_ENCODER_COUNTS);
pros::Motor backRightMotor(16, MOTOR_GEAR_BLUE, false, MOTOR_ENCODER_COUNTS);

pros::Motor_Group leftDrive({frontLeftMotor, backLeftMotor});
pros::Motor_Group rightDrive({frontRightMotor, backRightMotor});

// Catapult
// pros::Motor catapult(18, MOTOR_GEAR_GREEN, false, MOTOR_ENCODER_COUNTS);

// Wings
pros::Motor slapper(18, MOTOR_GEAR_GREEN, true, MOTOR_ENCODER_COUNTS);

// Sensor Initialization
pros::IMU gyro(8);