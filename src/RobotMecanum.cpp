#include "WPILib.h"
#include "RobotMecanum.h"
#include <Math.h>

#define PI 3.14159265

RobotMecanum::RobotMecanum() {
	_motor_FL = std::make_shared<Spark>(0);
	_motor_FR = std::make_shared<Spark>(1);
	_motor_BL = std::make_shared<TalonSRX>(3);
	_motor_BR = std::make_shared<TalonSRX>(2);
	_robot_gyro = std::make_shared<ADXRS450_Gyro>();
	RobotMecanum::setDriveAngle();
}
void RobotMecanum::setDriveAngle() {
	init_angle = _robot_gyro->GetAngle();
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
void RobotMecanum::driveBasic(double x, double y, double rotation) {
	current_angle = _robot_gyro->GetAngle();
	if (rotation < 0.2 && rotation > -0.2) {
		//IF ROBOT IS SPINNING OUT OF CONTROL, CHECK THE STATEMENT BELOW.
		rotation = rotation - lock_sensitivity * (current_angle - lock_angle) / 20;
	} else {
		lock_angle = current_angle;
	}

	_motor_FL->Set((y + x + rotation) * sensitivity * inv_FL);
	_motor_FR->Set((y*1.32 - x*1.32 - rotation) * sensitivity * inv_FR);
	_motor_BL->Set((y*1.2 - x*1.2 + rotation) * sensitivity * inv_BL);
	_motor_BR->Set((y + x - rotation) * sensitivity * inv_BR);
}
