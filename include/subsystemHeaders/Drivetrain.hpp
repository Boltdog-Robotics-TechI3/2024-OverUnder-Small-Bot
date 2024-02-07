#include "main.h"


void drivetrainInitialize();

void drivetrainPeriodic(bool override);

void drive();

void moveDistance(int distance, int speed);

void moveDistancePID(int distance);

void rotateToHeading(int angle, int speed);
 
void rotateToHeadingGyro(double angle);

void rotateToHeadingPID(double angle);
 