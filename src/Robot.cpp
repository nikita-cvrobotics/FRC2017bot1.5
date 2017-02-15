#include <iostream>
#include <memory>
#include <string>

#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include "WPILib.h"
#include "RobotMecanum.h"

class Robot: public frc::IterativeRobot {

	RobotMecanum *_robot_drive;
	XboxController *_joystick;
	bool lastResetGyro = false;

public:
	void RobotInit() {
		chooser.AddDefault(autoNameDefault, autoNameDefault);
		chooser.AddObject(autoNameCustom, autoNameCustom);
		frc::SmartDashboard::PutData("Auto Modes", &chooser);
		_robot_drive = new RobotMecanum();
		_robot_drive->Initialize();
		_joystick = new XboxController(0);
	}

	void AutonomousInit() override {
		autoSelected = chooser.GetSelected();
		// std::string autoSelected = SmartDashboard::GetString("Auto Selector", autoNameDefault);
		std::cout << "Auto selected: " << autoSelected << std::endl;

		if (autoSelected == autoNameCustom) {
			// Custom Auto goes here
		} else {
			// Default Auto goes here
		}
	}

	void AutonomousPeriodic() {
		if (autoSelected == autoNameCustom) {
			// Custom Auto goes here
		} else {
			// Default Auto goes here
		}
	}

	void TeleopInit() {

	}

	void TeleopPeriodic() {
		bool currResetGyro = _joystick->GetRawButton(7);
		if (currResetGyro && !lastResetGyro) {
			_robot_drive->setDriveAngle();
		}
		lastResetGyro = currResetGyro;
		double drX = _joystick->GetRawAxis(0);
		double drY = -_joystick->GetRawAxis(1);
		double drR = _joystick->GetRawAxis(4);
		_robot_drive->DriveCartesian(drX, drY, drR);
	}

	void TestPeriodic() {
		lw->Run();
	}

private:
	frc::LiveWindow* lw = LiveWindow::GetInstance();
	frc::SendableChooser<std::string> chooser;
	const std::string autoNameDefault = "Default";
	const std::string autoNameCustom = "My Auto";
	std::string autoSelected;
};

START_ROBOT_CLASS(Robot)
