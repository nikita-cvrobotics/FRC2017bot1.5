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
#include "RoboRealm.h"
#include "AutoRoute.h"

class Robot: public frc::IterativeRobot {

	std::shared_ptr<RobotMecanum> _robot_drive;
	std::shared_ptr<Claw> _claw;
	std::shared_ptr<RoboRealm> _track;
	std::shared_ptr<AutoRoute> _auto_route;
	XboxController *_joystick;
	Compressor *_compressor;
	bool lastResetGyro = false;
	Relay *_relay;
	TalonSRX *_winch;
	Talon *_hopper;
	DigitalInput *_bottom_limit;
	DigitalInput *_top_limit;
	//DoubleSolenoid *_claw;
	//DoubleSolenoid *_lift;
	double cog_x;
	double cog_y;
	//Ultrasonic *_left_sensor;
	//Ultrasonic *_right_sensor;
	double _time;
	//double _avg_angle_acc;
	bool _align;
public:
	void RobotInit() {
		CameraServer::GetInstance()->StartAutomaticCapture();
		chooser.AddDefault(autoNameDefault, autoNameDefault);
		chooser.AddObject(autoNameCustom, autoNameCustom);
		frc::SmartDashboard::PutData("Auto Modes", &chooser);
		_robot_drive = std::make_shared<RobotMecanum>();
		_claw = std::make_shared<Claw>();
		_track = std::make_shared<RoboRealm>();
		_joystick = new XboxController(0);
		_relay = new Relay(0, Relay::kForwardOnly);
		_winch = new TalonSRX(4);
		_hopper = new Talon(5);
		_bottom_limit = new DigitalInput(0);
		_top_limit = new DigitalInput(2);
		_compressor = new Compressor();
		//_claw = new DoubleSolenoid(0,1);
		//_lift = new DoubleSolenoid(2,3);
		_auto_route = std::make_shared<AutoRoute>(_robot_drive, _claw, _track);
		//_left_sensor = new Ultrasound(0, 1);
		//_right_sensor = new Ultrasound(2, 3);
	}

	void AutonomousInit() override {
		_compressor->SetClosedLoopControl(false);
		autoSelected = chooser.GetSelected();
		// std::string autoSelected = SmartDashboard::GetString("Auto Selector", autoNameDefault);
		std::cout << "Auto selected: " << autoSelected << std::endl;

		if (autoSelected == autoNameCustom) {
			// Custom Auto goes here
		} else {
			// Default Auto goes here
		}
		_relay->Set(Relay::kOn);

		//_auto_route->setRoute(_auto_route->ROUTE_2, _auto_route->ESCAPE_2_RIGHT, false);

		_robot_drive->resetTurnLock();
		_claw->claw_close_lock_locked = false;
		_claw->claw_close_locked = false;
		_time = 0;
	}

	void AutonomousPeriodic() {
		if (autoSelected == autoNameCustom) {
			// Custom Auto goes here
		} else {
			// Default Auto goes here
		}
		// CODE TO ALIGN CAMERA WITH BAYONET

		cog_x = SmartDashboard::GetNumber("COG_X", 0.0);
		cog_y = SmartDashboard::GetNumber("COG_Y", 0.0);
		SmartDashboard::PutNumber("xval", cog_x);
		SmartDashboard::PutNumber("yval", cog_y);

		//Due to mechanical issues, the camera is currently upside-down. Keep in mind when using new frame.
		/*double offset = (650 - cog_x) / 100 * 0.75;

		if (cog_x != 0) {
			_robot_drive->DriveCartesian(offset, 0, 0);
		}*/

		if (_time >= 650){
			_robot_drive->DriveCartesian(0,-0.7,0);
		} else {
			_robot_drive->DriveCartesian(0,0.7,0);
		}
		/*if (_time>=0 && _time<500){
			_robot_drive->DriveCartesian(0,0.7,0);
		} else if (_time>=500 && _time<600) {
			_robot_drive->DriveCartesian(0,-0.7,0);
		} else {
			while (cog_x==0){
				_robot_drive->DriveCartesian(0,0,0.8);
			}
		}*/

		SmartDashboard::PutNumber("time",_time);
		_compressor->SetClosedLoopControl(true);
		_time++;

		//_auto_route->proceedAuto();
	}

	void TeleopInit() {
		_compressor->SetClosedLoopControl(true);
		_relay->Set(Relay::kOn);
		_robot_drive->resetTurnLock();
		_claw->claw_close_lock_locked = false;
		_claw->claw_close_locked = false;
		//_time = 0;
	}

	void TeleopPeriodic() {
		double offset;
		SmartDashboard::PutNumber("init_angle",_robot_drive->init_angle);
		SmartDashboard::PutNumber("current_angle",_robot_drive->current_angle);
		SmartDashboard::PutNumber("lock_angle",_robot_drive->lock_angle);
		//_avg_angle_acc = _robot_drive->current_angle;
		bool currResetGyro = _joystick->GetRawButton(7);
		if (currResetGyro && !lastResetGyro) {
			_robot_drive->setDriveAngle();
		}
		lastResetGyro = currResetGyro;
		SmartDashboard::PutNumber("lastResetGyro", lastResetGyro);
		_robot_drive->boostSpeed(_joystick->GetRawAxis(3) > 0.5);
		double drX = _joystick->GetRawAxis(0);
		double drY = -_joystick->GetRawAxis(1);
		double drR = _joystick->GetRawAxis(4);
		_robot_drive->DriveCartesian(drX, drY, drR);
		//bool pull_up = _joystick->GetRawButton(5);
		//bool pull_up = _joystick->GetRawButton(5);
		//_winch->Set(pull_up - _joystick->GetRawButton(6));
		bool pull_up = _joystick->GetRawButton(6);
		bool rope_lock = _joystick->GetRawButton(5);
		if (pull_up){
			_winch->Set(1);
		} else if (rope_lock) {
			_winch->Set(0.25);
		} else {
			_winch->Set(0);
		}

		if (pull_up) {
			_robot_drive->resetTurnLock();
		}
		SmartDashboard::PutNumber("drX",drX);

		if (_joystick->GetRawButton(1)) {
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
		bool hopperUp = false;
		bool hopperDown = false;
		SmartDashboard::PutNumber("POV Joystick", _joystick->GetPOV());
		int povAngle = _joystick->GetPOV();
		hopperUp = ( (povAngle > 270) || (povAngle >= 0 && povAngle < 90) ) && !_top_limit->Get();
		hopperDown = ( (povAngle > 90 && povAngle < 270) ) && !_bottom_limit->Get();
		//SmartDashboard::PutBoolean("hopper_up", _top_limit->Get());
		//SmartDashboard::PutBoolean("hopper_down", _bottom_limit->Get());
		_hopper->Set(hopperUp - hopperDown);
		//hopperUp = povAngle == 1
		//_claw->checkLimits();
		cog_x = SmartDashboard::GetNumber("COG_X", 0.0);
		_align = _joystick->GetRawButton(8);
		if (_align && cog_x!=0){
			//offset = (615 - cog_x) / 100 * 0.75;
			offset = (cog_x - 615*0.5) / 100 * 0.40;
			SmartDashboard::PutNumber("offset", offset);
			_robot_drive->DriveCartesian(offset, 0, 0);
		}
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
