#include "main.h"
#include <iostream>
using namespace std;
#include "lemlib/api.hpp"
// #include <okapi/impl/util/timer.hpp>
#include "../../include/utilHeaders/Timer.hpp"


// lemlib's drivetrain object
lemlib::Drivetrain_t drivetrain {
    &leftDrive, // left drivetrain motors
    &rightDrive, // right drivetrain motors
    13, // track width
    2.75, // wheel diameter
    360 // wheel rpm
};

lemlib::OdomSensors_t odometry {
    nullptr,
    nullptr,
    nullptr, 
    nullptr, 
    &gyro // inertial sensor
};

// forward/backward PID
lemlib::ChassisController_t lateralController {
    8, // kP
    30, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    5 // slew rate
};
 
// turning PID
lemlib::ChassisController_t angularController {
    4, // kP
    40, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    0 // slew rate
};

// create the chassis
lemlib::Chassis chassis(drivetrain, lateralController, angularController, odometry);


// PID controllers for if we dont use LemLib drivetrain stuff
lemlib::FAPID drivePID{
    0, 
    0, 
    .2, 
    0, 
    0, 
    "billy"

};
lemlib::FAPID turnPID{
    0,//ff
    .05,//aceleration
    2.25,//p
    0,//i
    0.2,//d
    "johnny"//name
};

Timer timer;


// lemlib::time timer{};

// Code to be run upon initialization
void drivetrainInitialize(){
	gyro.reset();
	gyro.set_heading(0);
    chassis.calibrate();
    chassis.setPose(0, 0, 0); // X: 0, Y: 0, Heading: 0

}

// Code to be run repeatedly in OpControl
void drivetrainPeriodic() {
    drive();
}

// User Drive Function
void drive() {
	int power = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
	int turn = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

	leftDrive = pow((power + turn), 3) / pow(127, 2);
    rightDrive = pow((power - turn), 3) / pow(127, 2);

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

    leftDrive.move_relative(distance, speed);
    rightDrive.move_relative(distance, speed);

    while (abs(abs(targetDistanceLeft) - abs(frontLeftMotor.get_position())) > 20) {
    }
	
    leftDrive.move_relative(0, speed);
    rightDrive.move_relative(0, speed);
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
        leftDrive.move(motorVal);
        rightDrive.move(motorVal);

    leftDrive.move(0);
    rightDrive.move(0);
}

// rotate to face a certain angle using a p controller and the gyro
void rotateToHeadingGyro(double angle) {
    double kP = 1.75;

    double error = angle - gyro.get_heading();

    while (abs(error) > .5) {
		int motorVal = error * kP;
		leftDrive.move(motorVal);
		rightDrive.move(-motorVal);
	    error = angle - gyro.get_heading();
	}

    leftDrive.move(0);
	rightDrive.move(0);
}



void rotateToHeadingPID(double angle){
    int motorVal = 0;
    double error = angle - gyro.get_heading();
    while (timer.getElapsedTime() > 1) {
        motorVal = turnPID.update(angle, gyro.get_heading(), false);
        leftDrive.move(motorVal);
        rightDrive.move(-motorVal);
        // master.set_text(1, 0, to_string(gyro.get_heading()));
        master.set_text(0, 0, to_string(turnPID.settled()));
        error = angle - gyro.get_heading();
        if (abs(error) < 2) {
            timer.start();
        }
        else {
            timer.stop();
            timer.clear();    
        }
    }
    timer.stop();
    timer.clear();   
    turnPID.reset();
    leftDrive.move(0);
    rightDrive.move(0);
}

// Move to pose from lemlib but made relative.
void moveTo(double xDist, double yDist, int timeout) {
    chassis.setPose(0, 0, 0);
    double y = chassis.getPose().y + yDist;
    double x = chassis.getPose().x + xDist;
    chassis.moveTo(x, y, timeout);
}
