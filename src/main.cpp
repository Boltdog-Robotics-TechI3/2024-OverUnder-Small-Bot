#include "main.h"
#include <iostream>
#include "cmath"
using namespace std;
#include "lemlib/api.hpp"

// Globals
static bool skills = false;
static bool elim = false;
static bool qual = true;
static bool red = false;
static bool blue = true;

static bool isMatchLoading = false;




// Checks to see if a triball is loaded
bool triballLoaded() {
    return ultrasonic.get_value() < 100;
}

// Makes sure the catapult is in the proper position to fire
void primeCatapult() {
	int lineTrackerVal;
	lineTrackerVal = lineTracker.get_value();
	if (lineTrackerVal > 300) {
		catapult.move(127);
		while(lineTrackerVal > 300) {
			drive();
			lineTrackerVal = lineTracker.get_value();
			if (lineTrackerVal < 300) {
				catapult.move(0);
				catapult.set_brake_mode(MOTOR_BRAKE_HOLD);
			}
		}
	}
	else {
		catapult.move(0);
		catapult.set_brake_mode(MOTOR_BRAKE_HOLD);
	}
}

// Fires the triball
void launchTriball() {
	catapult.move(100);
	pros::delay(300);
	primeCatapult();
}

void launchTriballNoPrime() {
	catapult.move(100);
	pros::delay(200);
	}

void matchLoad() {
	while(master.get_digital(DIGITAL_X)) {
		lift.move(-90);
		pros::delay(650);
		lift.move(0);
		pros::delay(500);
		intake.move(0);
		launchTriball();
		lift.move(90);
		pros::delay(650);
		lift.move(0);
		intake.move(127);
		pros::delay(700);
		}
}

/**
 * A callback function for LLEMU's center button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "Skills Run" and "Match Auton" If the robot is selected for match auton, qualififaction rounds is defaultly selected
 */
void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;

	if (pressed) {

		pros::lcd::set_text(3, "Skills Run");
		skills = true;
		elim = false;
		qual = false;

	} else {

		pros::lcd::set_text(2, "Match Auton");
		skills = false;
		pros::lcd::set_text(3, "Elimination rounds auton selected");
		qual = true;

	}
}

/**
 * A callback function for LLEMU's right button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "Elimination rounds auton selected" and "Qualification rounds auton selected"
 */

void on_right_button() {
	static bool pressed = false;
	pressed = !pressed;

	if (pressed) {

		pros::lcd::set_text(3, "Elimination rounds auton selected");
		elim = true;
		qual = false;

	} else {

		pros::lcd::set_text(3, "Qualification rounds auton selected");
		qual = true;
		elim = false;

	}
}

/**
 * A callback function for LLEMU's right button.
 *
 * When this callback is fired, it will toggle line 2 of the LCD text between
 * "Elimination rounds auton selected" and "Qualification rounds auton selected"
 */

void on_left_button() {
	static bool pressed = false;
	pressed = !pressed;

	if (pressed) {

		pros::lcd::set_text(4, "Red side is selected");
		blue = true;
		red = false;

	} else {

		pros::lcd::set_text(4, "Blue side is selected");
		red = true;
		blue = false;

	}
}

// First half of auton
void score2TriBalls(){
  	//move lift to deploy
	lift.move(127);
	pros::delay(300);
	lift.move(0);
	//rotate to shoot
	rotateToHeading(-55, 100);
	//shoot
	launchTriballNoPrime();
	catapult.move_relative(6687, 200);
	//rotate to drive
	rotateToHeading(225, 200);
	//set lift and intake to get ball under bar
	intake.move(40);
	lift.move(-127);
	pros::delay(50);
	lift.move(0);
	//drive under bar
	moveDistance(-4200, 300);
	//hold the ball while turning
	lift.move(-127);
	pros::delay(50);
	lift.move(0);
	//go to goal
	rotateToHeading(-45, 100);
	intake.move(0);

	moveDistance(-1300, 300);
	rotateToHeading(-25, 100);


	// score first triball
	intake.move(-100);
	lift.move(90);
	pros::delay(600);
	lift.move(0);
	moveDistance(500, 300);
	pros::delay(500);
	lift.move(-90);
	pros::delay(600);
	lift.move(0);
	moveDistance(-900, 300);
	moveDistance(850, 300);
	intake.move(0);
	lift.move(90);
	pros::delay(550);
	lift.move(0);

	// move towards alliance balls
	rotateToHeading(130, 300);
	intake.move(127);
	moveDistance(-500, 200);
	lift.move(-90);
	pros::delay(350);
	lift.move(0);
	pros::delay(200);
	moveDistance(400, 200);
	moveDistance(300, 200);

	// move towards and score in goal again
	rotateToHeading(-110, 200);
	moveDistance(-200, 200);
	intake.move(-127);
	lift.move(90);
	pros::delay(450);
	lift.move(0);
	intake.move(-40);
	moveDistance(1200, 250);
	lift.move(-90);
	pros::delay(400);
	lift.move(0);
	moveDistance(-1300, 300);
}

// Second half of auton for 6 ball auton
void finalPartQuals(){
	// drive back to trench
	moveDistance(1300, 300);
	lift.move(90);
	pros::delay(300);
	lift.move(0);
	intake.move(0);
	rotateToHeading(62.5, 300);

	//drive through trench
	moveDistance(6000, 400);

	// align with alliance triball
	moveDistance(-400, 300);
	lift.move(90);
	pros::delay(400);
	lift.move(0);
	rotateToHeading(-175, 300);

	// intake alliance triball
	moveDistance(-500, 300);
	intake.move(127);
	lift.move(-90);
	pros::delay(350);
	lift.move(0);
	pros::delay(200);
	moveDistance(400, 200);

	// drive to goal
	rotateToHeading(120, 300);
	moveDistance(-300, 300);
	intake.move(-90);
	lift.move(90);
	pros::delay(450);
	lift.move(0);
	moveDistance(500, 300);
	lift.move(-90);
	pros::delay(400);
	lift.move(0);

	// score triball
	moveDistance(-800, 300);
	moveDistance(1200, 300);
	intake.move(0);
	lift.move(90);
	pros::delay(400);
	lift.move(0);

	// drive to horizontal bar and touch it
	launchTriballNoPrime();
	rotateToHeading(-50, 300);
	moveDistance(3200, 300);
}

void skillsAutoLift() {
	// launch preload
	lift.move(90);
	pros::delay(600);
	lift.move(0);
	intake.move(127);
	moveDistance(-100, 200);
	launchTriball();

	// match load triballs
	for (int i = 0; i <= 30; i++) {
		lift.move(-90);
		pros::delay(650);
		lift.move(0);
		pros::delay(500);
		lift.move(90);
		pros::delay(650);
		lift.move(0);
		intake.move(127);
		launchTriball();
		pros::delay(700);
	}

	// climb on horizontal bar
	moveDistance(700, 200);
	rotateToHeading(-90, 255);
	lift.move(90);
	pros::delay(300);
	lift.move(0); 
	moveDistance(500, 255);
	rotateToHeading(45, 255);
	moveDistance(2500, 255);
	lift.move(-90);
	pros::delay(1000);
	lift.move(0);
}




/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();
	pros::lcd::set_text(1, "TECHI3 Ruff and Ready");

	// activating v5 buttons
	pros::lcd::register_btn1_cb(on_center_button);
	pros::lcd::register_btn0_cb(on_right_button);
	pros::lcd::register_btn2_cb(on_left_button);

	// setting motor brake modes
	frontLeftMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
	frontRightMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
	backLeftMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);
	backRightMotor.set_brake_mode(MOTOR_BRAKE_BRAKE);

	lift.set_brake_modes(MOTOR_BRAKE_HOLD);

	// calibrating encoders and gyro
	leftLiftMotor.set_encoder_units(MOTOR_ENCODER_ROTATIONS);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
	// calibrate gyro
	gyro.reset();
	gyro.set_heading(0);
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
	pros::lcd::set_text(1, "TECHI3 Ruff and Ready");
	gyro.reset();
	gyro.set_heading(0);
	pros::lcd::register_btn1_cb(on_center_button);
	pros::lcd::register_btn0_cb(on_right_button);
	pros::lcd::register_btn2_cb(on_left_button);
	}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	// if (elim == true) {

	// 	score2TriBalls();
	// 	finalPartElims();

	// } else if (qual == true) {
	// rotateToHeadingGyro(90);
	moveDistancePID(500);
		// score2TriBalls();
		// finalPartQuals();

	// } else if (skills == true) {

	// 	skillsAutoLift();

	// }
}


/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

void opcontrol() {
	float liftPos;
	primeCatapult();
	leftLiftMotor.tare_position();

	while (true) {
		if (master.get_digital(DIGITAL_LEFT) && master.get_digital(DIGITAL_RIGHT)) {
			// autonomous();
			rotateToHeadingGyro(90);
		}

		pros::lcd::set_text(6, "Catapult Encoder: " + to_string(catapult.get_position()));

		matchLoad();
		
		pros::lcd::set_text(0, "Drivetrain Left Encoder: " + to_string(frontLeftMotor.get_position()));

		liftPos = leftLiftMotor.get_position();
		pros::lcd::print(2, "%f", liftPos);

		//Split Arcade control code
		drive();

		// This block launches the triball when the correct buttons is pressed
		if (master.get_digital(DIGITAL_R2) && triballLoaded()) {
			launchTriball();
		}

		// This block lifts the lift and intake up and down
		if (master.get_digital(DIGITAL_L1)) {
			if (liftPos < 2 || master.get_digital(DIGITAL_B)) {
				lift.move(127);
			}
			else {
				lift.move(0);
			}
		}
		else if (master.get_digital(DIGITAL_L2)) {
			if (liftPos > 0) {
				lift.move(-127);
				intake.move(127);
			}
			else {
				lift.move(0);
			}
		}
		else {
			lift.move(0);
			intake.move(0);
		}

		// This block operates the intake motors
		if (master.get_digital(DIGITAL_UP)) {
			intake.move(127);
		}
		else if (master.get_digital(DIGITAL_DOWN)) {
			intake.move(-127);
		}

		if (master.get_digital_new_press(DIGITAL_A)){
			primeCatapult();
		}

		if (master.get_digital(DIGITAL_Y)) {
			catapult.move(100);
		}
		else {
			catapult.move(0);
		}

		pros::delay(20);
	}
}	


