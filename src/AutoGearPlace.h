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
#include "Drivetrain.h"

class AutoGearPlace: public PIDSubsystem {
public:

	std::shared_ptr<NetworkTable> m_netTable;
	AutoGearPlace(std::shared_ptr<NetworkTable> newTable, Drivetrain *drive);
	double ReturnPIDInput();
	void changeActive(bool newState);
	bool isDone();
	void UsePIDOutput(double output);
	virtual ~AutoGearPlace();


protected:
	Drivetrain* m_drivetrain;
	bool isActive;


};

#endif /* SRC_AUTOGEARPLACE_H_ */
