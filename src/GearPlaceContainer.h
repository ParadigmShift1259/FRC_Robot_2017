/*
 * GearPlaceContainer.h
 *
 *  Created on: Feb 11, 2017
 *      Author: Developer
 */

#ifndef GEARPLACECONTAINER_H_
#define GEARPLACECONTAINER_H_

#include "Drivetrain.h"
#include "AutoGearPlace.h"
#include "OperatorInputs.h"
#include <ntCore.h>

class GearPlaceContainer {
public:
	GearPlaceContainer(Drivetrain *drivetrain, std::shared_ptr<NetworkTable> nTable, OperatorInputs *oi);
	virtual ~GearPlaceContainer();
	void StartGearPlace();
	void MaintainGearPlace();
private:
	OperatorInputs *m_inputs;
	AutoGearPlace* m_autoGearPlace;
	Drivetrain *m_drivetrain;
	std::shared_ptr<NetworkTable> m_netTable;
	double angleTarget;
	int netLoopCount;

};

#endif /* GEARPLACECONTAINER_H_ */
