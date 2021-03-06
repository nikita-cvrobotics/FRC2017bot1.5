#include "WPILib.h"
#include "RobotMecanum.h"
#include <Math.h>

#define PI 3.14159265

RobotMecanum::RobotMecanum() {
	_motor_FL = std::make_shared<Spark>(3);
	_motor_FR = std::make_shared<Spark>(2);
	_motor_BL = std::make_shared<TalonSRX>(0);
	_motor_BR = std::make_shared<TalonSRX>(1);
	_robot_gyro = std::make_shared<ADXRS450_Gyro>();
	RobotMecanum::setDriveAngle();
}

void RobotMecanum::setDriveAngle() {
	_robot_gyro->Reset();
	init_angle = _robot_gyro->GetAngle();
	lock_angle = init_angle;
}
void RobotMecanum::setDriveSystem(int new_drive) {
	current_drive = new_drive;
}
void RobotMecanum::DrivePolar(double angle, double magnitude, double rotation) {
	if (current_drive == ADVANCED_DRIVE) {
		angle = angle + (current_angle - init_angle);
	}
	RobotMecanum::driveBasic(cos(angle * PI / 180) * magnitude, sin(angle * PI / 180) * magnitude, rotation);
}
void RobotMecanum::DriveCartesian(double x, double y, double rotation) {
	if (current_drive == ADVANCED_DRIVE) {
		RobotMecanum::DrivePolar(atan2(y, x) * 180 / PI, sqrt(x*x + y*y), rotation);
	} else {
		RobotMecanum::driveBasic(x, y, rotation);
	}
}
void RobotMecanum::resetTurnLock() {
	lock_angle = _robot_gyro->GetAngle();
}
void RobotMecanum::boostSpeed(bool isBoost) {
	if (isBoost) {
		sensitivity = 0.65;
	} else {
		sensitivity = 0.25;
	}
}
void RobotMecanum::driveBasic(double x, double y, double rotation) {
	current_angle = _robot_gyro->GetAngle() - 0.015;
	if (rotation < 0.2 && rotation > -0.2) {
		//IF ROBOT IS SPINNING OUT OF CONTROL, CHECK THE STATEMENT BELOW.
		rotation = rotation - lock_sensitivity * (current_angle - lock_angle) / 20;
	} else {
		lock_angle = current_angle;
	}
	_motor_FL->Set((y + x * 1.3 + rotation) * sensitivity * inv_FL * 1.2);
	_motor_FR->Set((y*1.32 - x*1.32 * 1.3 - rotation) * sensitivity * inv_FR);
	_motor_BL->Set((y*1.2 - x*1.2 * 1.3 + rotation) * sensitivity * inv_BL);
	_motor_BR->Set((y + x * 1.3 - rotation) * sensitivity * inv_BR);
}
