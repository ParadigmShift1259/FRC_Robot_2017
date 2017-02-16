/*
 * GearTarget.h
 *
 *  Created on: Feb 15, 2017
 *      Author: Developer
 */

#ifndef GEARTARGET_H_
#define GEARTARGET_H_

#include "DriveAngle.h"
#include "Drivetrain.h"
#include <ntCore.h>

class GearTarget {
public:
	GearTarget(std::shared_ptr<NetworkTable> newTable, DriveAngle *newAngle);
	void Init();
	void Loop();
	void Target();
	void Stop();
	virtual ~GearTarget();
private:
	bool isDone;
	int prevCounter;
	int counter;
	double xDegree;
	DriveAngle* container;
	enum Stage {stopped, read, targeting};
	std::shared_ptr<NetworkTable> netTable;
	Stage stage;
};

#endif /* GEARTARGET_H_ */
