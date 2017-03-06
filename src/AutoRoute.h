#include "WPILib.h"
#include "RobotMecanum.h"
#include "Claw.h"
#include "RoboRealm.h"

#ifndef SRC_AUTOROUTE_H_
#define SRC_AUTOROUTE_H_

class AutoRoute {
public:
	std::shared_ptr<RobotMecanum> _robot_drive;
	std::shared_ptr<Claw> _claw;
	std::shared_ptr<RoboRealm> _track;
	AutoRoute(std::shared_ptr<RobotMecanum> _driver, std::shared_ptr<Claw> _clawer, std::shared_ptr<RoboRealm> _tracker);
	static const int INIT_STATE = 1;
	static const int LOCATE_STATE = 2;
	static const int TARGET_STATE = 3;
	static const int DEPLOY_STATE = 4;
	static const int ESCAPE_STATE = 5;
	static const int ESCAPE_2_RIGHT = 0;
	static const int ESCAPE_2_LEFT = 1;
	const int ROUTE_1 = 1;
	const int ROUTE_2 = 2;
	const int ROUTE_3 = 3;
	int current_state = 0;
	int current_route = 0;
	int current_escape = 0;
	bool current_swerve = false;
	void setRoute(int route, int escape_2 = 0, bool swerve_escape = false);
	void proceedAuto();
};

#endif /* SRC_AUTOROUTE_H_ */
