#include "WPILib.h"
#include "RobotMecanum.h"
#include "Claw.h"
#include "RoboRealm.h"

#ifndef SRC_AUTOROUTE_H_
#define SRC_AUTOROUTE_H_

class AutoRoute {
public:
	std::shared_ptr<RobotMecanum> _robot_drive;
	AutoRoute(RobotMecanum drive, Claw claw, RoboRealm track);
	const int INIT_STATE = 1;
	const int LOCATE_STATE = 2;
	const int TARGET_STATE = 3;
	const int DEPLOY_STATE = 4;
	const int ESCAPE_STATE = 5;
	const int ESCAPE_2_RIGHT = 0;
	const int ESCAPE_2_LEFT = 0;
	int current_state = 0;
	void setRoute(int route, int escape_2, bool swerve_escape);
	void proceedAuto();
};

#endif /* SRC_AUTOROUTE_H_ */
