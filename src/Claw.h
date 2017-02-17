#include "WPILib.h"

#ifndef SRC_CLAW_H_
#define SRC_CLAW_H_

class Claw {
public:
	std::shared_ptr<DoubleSolenoid> _claw_piston;
	std::shared_ptr<DoubleSolenoid> _arm_piston;
	std::shared_ptr<DigitalInput> _reed_switch;
	bool claw_close_locked = false;
	bool claw_close_lock_locked = false;
	Claw();
	void openClaw();
	void closeClaw();
	void raiseArm();
	void lowerArm();
	void checkLimits();
};

#endif /* SRC_CLAW_H_ */
