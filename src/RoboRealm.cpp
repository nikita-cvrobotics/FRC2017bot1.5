#include "WPILib.h"
#include "RoboRealm.h"

void RoboRealm::searchForTarget() {
	COG_X = SmartDashboard::GetNumber("COG_X", 0.0);
	COG_Y = SmartDashboard::GetNumber("COG_Y", 0.0);
	WIDTH = SmartDashboard::GetNumber("WIDTH", 0.0);
	HEIGHT = SmartDashboard::GetNumber("WIDTH", 0.0);
	targetFound = (COG_X != 0);
}
double RoboRealm::getXOffset() {
	return COG_X - center_x;
}
double RoboRealm::getYOffset() {
	return COG_Y - center_y;
}
double RoboRealm::getXMove() {
	return RoboRealm::getXOffset() / 100;
}
double RoboRealm::getYMove() {
	return 1.0 - abs(RoboRealm::getXOffset() / 100);
}
