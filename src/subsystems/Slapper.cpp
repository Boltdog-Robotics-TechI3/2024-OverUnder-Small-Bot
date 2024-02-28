#include "main.h"

void slapperInitialize() {
    slapper.set_brake_mode(MOTOR_BRAKE_BRAKE);
}

void slapperPeriodic(bool override) {
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_A)) {
        setSlapperSpeed(127);
    }
    else {
        setSlapperSpeed(0);
    }
}

//
void setSlapperSpeed(double speed) {
    slapper.move(speed);
}