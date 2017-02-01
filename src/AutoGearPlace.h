/*
 * AutoGearPlace.h
 *
 *  Created on: Jan 25, 2017
 *      Author: Developer
 */

#ifndef SRC_AUTOGEARPLACE_H_
#define SRC_AUTOGEARPLACE_H_
#include "WPILib.h"
#include <networktables/NetworkTable.h>
#include <Commands/PIDSubsystem.h>
#include <nt_Value.h>

class AutoGearPlace: public PIDSubsystem {
public:

	NetworkTable * netTable;
	AutoGearPlace(NetworkTable *newTable);
	double ReturnPIDInput();
	void UsePIDOutput(double output);
	virtual ~AutoGearPlace();
	double output;

private:

	PIDController* pid;

protected:


};

#endif /* SRC_AUTOGEARPLACE_H_ */
