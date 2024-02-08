#include "main.h"
#include <iostream>
using namespace std;
#include "lemlib/api.hpp"

// lemlib's drivetrain object, will only use if we get tracking wheels :(
// lemlib::Drivetrain_t drivetrain {
//     leftSideMotors, // left drivetrain motors
//     rightSideMotors, // right drivetrain motors
//     13, // track width
//     2.75, // wheel diameter
//     360 // wheel rpm
// };

lemlib::FAPID drivePID{0, 0, .2, 0, 0, "billy"};
lemlib::FAPID turnPID{
    0,//ff
    .05,//aceleration
    2.25,//p
    0,//i
    0.2,//d
    "johnny"//name
};

// lemlib::time timer{};
void drivetrainInitialize(){
    turnPID.setExit(360, .5, 5000, 500, 10000);
}

// User Drive Function
void drive() {
	int power = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
	int turn = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

	leftSideMotors = pow((power + turn), 3) / pow(127, 2);
    rightSideMotors = pow((power - turn), 3) / pow(127, 2);

    pros::lcd::set_text(6, "Heading:" + to_string(gyro.get_heading()));

    int error = 90 - gyro.get_heading();


    master.set_text(0, 0, to_string(turnPID.settled()));
    
		// int motorVal = error * .2;
        // pros::lcd::set_text(5, "Motor Val: " + to_string(motorVal));
    // pros::lcd::set_text(5, "Error: " + to_string(error));
}

// AUTO METHODS //

// Move x distance using PROS built-in movement methods
void moveDistance(int distance, int speed) {
    double targetDistanceLeft = frontLeftMotor.get_position() + distance;
    double targetDistanceRight = frontRightMotor.get_position() + distance;

    // leftDrive.move_absolute(targetDistanceLeft, speed);
    // rightDrive.move_absolute(targetDistanceRight, speed);

    leftSideMotors.move_relative(distance, speed);
    rightSideMotors.move_relative(distance, speed);

    while (abs(abs(targetDistanceLeft) - abs(frontLeftMotor.get_position())) > 20) {
    }
	
    leftSideMotors.move_relative(0, speed);
    rightSideMotors.move_relative(0, speed);
    pros::delay(200);
}

// drive a certain distance using lemlib's pid controller
void moveDistancePID(int distance) {
    // float initialPos = frontLeftMotor.get_position();
    float targetPos = frontLeftMotor.get_position() + distance;

    //This sets the exit conditions
    drivePID.setExit(2000, 10, 5000, 0, 5000000);
    int motorVal = 0;

    while (true)
        motorVal = drivePID.update(targetPos, frontLeftMotor.get_position(), false);
        leftSideMotors.move(motorVal);
        rightSideMotors.move(motorVal);

    leftSideMotors.move(0);
    rightSideMotors.move(0);
}

// Target angle is relative to the robot's current heading, so a 90 will mean the robot will turn 90 degrees
void rotateToHeading(int angle, int speed) {
    // the distance the motor needs to travel in order to reach the desired rotation
    double distance = 2335 * ((angle - 5) / 360.0);

    // the actual target encoder value for the leftDrive
    double targetDistanceLeft = frontLeftMotor.get_position() + distance;
    double targetDistanceRight = frontRightMotor.get_position() - distance;

    // set the motors to move to the target positions. (This will move and stop the motors on its own [apparently])
    leftSideMotors.move_absolute(targetDistanceLeft, speed);
    rightSideMotors.move_absolute(targetDistanceRight, speed);

    while (abs(abs(targetDistanceLeft) - abs(frontLeftMotor.get_position())) > 50) {
    }
    
    pros::delay(200);
}

// rotate to face a certain angle using a p controller and the gyro
void rotateToHeadingGyro(double angle) {
    double kP = 1.75;

    double error = angle - gyro.get_heading();

    while (abs(error) > .5) {
		int motorVal = error * kP;
		leftSideMotors.move(motorVal);
		rightSideMotors.move(-motorVal);
	    error = angle - gyro.get_heading();
	}

    leftSideMotors.move(0);
	rightSideMotors.move(0);
}



void rotateToHeadingPID(double angle){
    int motorVal = 0;
    double error = angle - gyro.get_heading();
    while () {
        motorVal = turnPID.update(angle, gyro.get_heading(), false);
        leftSideMotors.move(motorVal);
        rightSideMotors.move(-motorVal);
        // master.set_text(1, 0, to_string(gyro.get_heading()));
        master.set_text(0, 0, to_string(turnPID.settled()));
        error = angle - gyro.get_heading();
        if (abs(error) < 2) {

        }
    }
    turnPID.reset();
    leftSideMotors.move(0);
    rightSideMotors.move(0);
}
    