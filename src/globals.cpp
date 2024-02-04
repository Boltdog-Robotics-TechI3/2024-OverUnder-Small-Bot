#include "main.h"

// Controller Setup
pros::Controller master(pros::E_CONTROLLER_MASTER);


// Motor Initialization
pros::Motor catapult(18);

pros::Motor frontLeftMotor(19, MOTOR_GEAR_BLUE, true, MOTOR_ENCODER_COUNTS);
pros::Motor frontRightMotor(12, MOTOR_GEAR_BLUE, false, MOTOR_ENCODER_COUNTS);
pros::Motor backLeftMotor(20, MOTOR_GEAR_BLUE, true, MOTOR_ENCODER_COUNTS);
pros::Motor backRightMotor(11, MOTOR_GEAR_BLUE, false, MOTOR_ENCODER_COUNTS);

pros::Motor_Group leftSideMotors({frontLeftMotor, backLeftMotor});
pros::Motor_Group rightSideMotors({frontRightMotor, backRightMotor});

pros::Motor leftLiftMotor(5, true);
pros::Motor rightLiftMotor(6);
pros::Motor_Group lift({leftLiftMotor, rightLiftMotor});

pros::Motor intake(1, true);

// Sensor Initialization
pros::ADIAnalogIn lineTracker('H');
pros::ADIUltrasonic ultrasonic('E', 'F');

pros::IMU gyro(8);