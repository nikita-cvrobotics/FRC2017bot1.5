#include "WPILib.h"
#ifndef SRC_ROBOREALM_H_
#define SRC_ROBOREALM_H_

class RoboRealm {
public:
	bool targetFound = false;
	double COG_X = 0;
	double COG_Y = 0;
	double WIDTH = 0;
	double HEIGHT = 0;
	double center_x = 450;
	double center_y = 200;
	void searchForTarget();
	double getXOffset();
	double getYOffset();
};

#endif /* SRC_ROBOREALM_H_ */
