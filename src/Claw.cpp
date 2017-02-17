#include "Claw.h"

Claw::Claw() {
	_claw_piston = std::make_shared<DoubleSolenoid>(0,1);
	_arm_piston = std::make_shared<DoubleSolenoid>(2,3);
	_reed_switch = std::make_shared<DigitalInput>(1);
}
void Claw::closeClaw() {
	if (!claw_close_locked) {
		_claw_piston->Set(DoubleSolenoid::kForward);
		claw_close_lock_locked = false;
	}
}
void Claw::openClaw() {
	_claw_piston->Set(DoubleSolenoid::kReverse);
	claw_close_lock_locked = true;
}
void Claw::raiseArm() {
	_arm_piston->Set(DoubleSolenoid::kReverse);
}
void Claw::lowerArm() {
	_arm_piston->Set(DoubleSolenoid::kForward);
}
void Claw::checkLimits() {
	if (_reed_switch->Get() && !claw_close_lock_locked) {
		_claw_piston->Set(DoubleSolenoid::kOff);
		claw_close_locked = true;
	}
}
