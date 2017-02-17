#include <iostream>
#include <memory>
#include <string>

#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include "WPILib.h"
#include "RobotMecanum.h"
#include "Claw.h"


class Robot: public frc::IterativeRobot {

	RobotMecanum *_robot_drive;
	Claw *_claw;
	XboxController *_joystick;
	Compressor *_compressor;
	bool lastResetGyro = false;
	Relay *_relay;
	//DoubleSolenoid *_claw;
	//DoubleSolenoid *_lift;
	double cog_x;
	double cog_y;

public:
	void RobotInit() {
		chooser.AddDefault(autoNameDefault, autoNameDefault);
		chooser.AddObject(autoNameCustom, autoNameCustom);
		frc::SmartDashboard::PutData("Auto Modes", &chooser);
		_robot_drive = new RobotMecanum();
		//_claw = new Claw();
		_joystick = new XboxController(0);
		_relay = new Relay(0, Relay::kForwardOnly);
		//_compressor = new Compressor();
		//_claw = new DoubleSolenoid(0,1);
		//_lift = new DoubleSolenoid(2,3);
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
		_relay->Set(Relay::kOn);
	}

	void AutonomousPeriodic() {
		if (autoSelected == autoNameCustom) {
			// Custom Auto goes here
		} else {
			// Default Auto goes here
		}
		/* CODE TO ALIGN CAMERA WITH BAYONET
		cog_x = SmartDashboard::GetNumber("COG_X", 0.0);
		cog_y = SmartDashboard::GetNumber("COG_Y", 0.0);
		SmartDashboard::PutNumber("xval", cog_x);
		SmartDashboard::PutNumber("yval", cog_y);

		//Due to mechanical issues, the camera is currently upside-down. Keep in mind when using new frame.
		double offset = (450 - cog_x) / 100 * 0.75;

		if (cog_x != 0) {
			_robot_drive->DriveCartesian(offset, 0, 0);
		}
		*/

	}

	void TeleopInit() {
		//_compressor->SetClosedLoopControl(false);
		_relay->Set(Relay::kOn);
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
		SmartDashboard::PutNumber("drX",drX);

		/*if (_joystick->GetRawButton(1)) {
			//A button is pressed
			_claw->lowerArm();
		}
		if (_joystick->GetRawButton(2)) {
			//B button is pressed
			_claw->openClaw();
		}
		if (_joystick->GetRawButton(3)) {
			//X button is pressed
			_claw->closeClaw();
		}
		if (_joystick->GetRawButton(4)) {
			//Y button is pressed
			_claw->raiseArm();
		}
		_claw->checkLimits();*/

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
