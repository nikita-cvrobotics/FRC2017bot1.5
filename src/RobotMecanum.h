#include "WPILib.h"

#ifndef SRC_ROBOTMECANUM_H_
#define SRC_ROBOTMECANUM_H_

class RobotMecanum {

public:
	RobotMecanum();
	const int BASIC_DRIVE = 0;
	const int ADVANCED_DRIVE = 1;
	double sensitivity = 0.25;
	void DrivePolar(double angle, double magnitude, double rotation);
	void DriveCartesian(double x, double y, double rotation);
	void setDriveAngle();
	void setDriveSystem(int new_drive);
	void resetTurnLock();
	void boostSpeed(bool isBoost);
	double current_angle;
	double init_angle;
	double lock_angle;
	//void Initialize();
protected:
	//For alignment when robot moves straight and stands still. Between 0 and 1. Be reasonable.
	double lock_sensitivity = 1;
	double inv_FL = 1;
	double inv_FR = -1;
	double inv_BL = 1;
	double inv_BR = -1;
private:
	int current_drive = ADVANCED_DRIVE;
	//int current_drive = BASIC_DRIVE;
	//double current_angle;
	//double init_angle;
	//double lock_angle;
	std::shared_ptr<ADXRS450_Gyro> _robot_gyro;
	std::shared_ptr<SpeedController> _motor_FL;
	std::shared_ptr<SpeedController> _motor_FR;
	std::shared_ptr<SpeedController> _motor_BL;
	std::shared_ptr<SpeedController> _motor_BR;
	void driveBasic(double x, double y, double rotation);
};

#endif /* SRC_ROBOTMECANUM_H_ */
