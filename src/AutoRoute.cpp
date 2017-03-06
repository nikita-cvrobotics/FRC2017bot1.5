#include "WPILib.h"
#include "AutoRoute.h"
#include "RobotMecanum.h"
#include "Claw.h"
#include "RoboRealm.h"
#include "CounterBox.h"

//I'm gonna put object definitions here; I know it's a sketchy place, but it's easy to access.
// - Nikita

CounterBox *init_drive_limit;
CounterBox *init_turn_limit;
CounterBox *search_limit;

AutoRoute::AutoRoute(std::shared_ptr<RobotMecanum> _driver, std::shared_ptr<Claw> _clawer, std::shared_ptr<RoboRealm> _tracker) {
	_robot_drive = _driver;
	_claw = _clawer;
	_track = _tracker;
}
void AutoRoute::setRoute(int route, int escape_2, bool swerve_escape) {
	current_state = AutoRoute::INIT_STATE;
	current_route = route;
	current_escape = escape_2;
	current_swerve = swerve_escape;
	//Any init code for autonomous should be placed below.
	init_drive_limit = new CounterBox(100);
	init_turn_limit = new CounterBox(40);
	search_limit = new CounterBox(150);
	_claw->raiseArm();
}

int i = 5;

void AutoRoute::proceedAuto() {
	SmartDashboard::PutNumber("AutoRoute State: ", current_state);
	switch(current_state) {
	case AutoRoute::INIT_STATE:
		//The robot is blindly moving into position.
		if (init_drive_limit->maxed()) {
			if (init_turn_limit->maxed()) {
				//Task complete. Move on.
				current_state = AutoRoute::LOCATE_STATE;
			} else {
				//Turn.
				_robot_drive->DriveCartesian(0, 0, -.9);
				init_turn_limit->increment();
			}
		} else {
			//Drive forward.
			_robot_drive->DriveCartesian(0, 1, 0);
			init_drive_limit->increment();
		}
		break;
	case AutoRoute::LOCATE_STATE:
		//The robot is searching for a target.
		_track->searchForTarget();
		if (_track->targetFound) {
			current_state = AutoRoute::TARGET_STATE;
		} else {
			_robot_drive->DrivePolar(0, 0, -0.9);
		}
		break;
	case AutoRoute::TARGET_STATE:
		//The robot is driving towards the target.
		_track->searchForTarget();
		if (!search_limit->maxed()) {
			double cogtX;
			cogtX = _track->COG_X;
			SmartDashboard::PutNumber("COGX", cogtX);
			double move;
			move = (cogtX - 320) / 50;
			if (move > 1) {
				move = 1;
			}
			if (move < -1) {
				move = -1;
			}
			if (_track->targetFound) {
				_robot_drive->DriveCartesian(move, .4, 0);
			} else {
				current_state = AutoRoute::LOCATE_STATE;
			}
			search_limit->increment();
		} else {
			current_state = AutoRoute::DEPLOY_STATE;
		}
		break;
	case AutoRoute::DEPLOY_STATE:
		//The robot is releasing the gear, then backing away.
		_claw->openClaw();
		_claw->lowerArm();
		current_state = AutoRoute::ESCAPE_STATE;
		break;
	case AutoRoute::ESCAPE_STATE:
		//The robot is performing a swift maneuver past the BASELINE (If necessary to get points).

		break;
	}
}
