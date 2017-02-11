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
#include <Const.h>
#include <nt_Value.h>
#include "Drivetrain.h"
#include "OperatorInputs.h"

class AutoGearPlace: public PIDSubsystem {
public:

	std::shared_ptr<NetworkTable> m_netTable;
	AutoGearPlace(std::shared_ptr<NetworkTable> newTable, Drivetrain *drive, OperatorInputs *oi);
	double ReturnPIDInput();
	void ChangeActive(bool newState);
	bool IsDone();
	void SetNewRelativeSetpoint(double newSetpoint);
	void UsePIDOutput(double output);
	virtual ~AutoGearPlace();
	double ReturnCurrentPosition();
	void CheckPIDValues();
	bool isInitialized;

protected:
	Drivetrain* m_drivetrain;
	OperatorInputs *m_inputs;
	bool isActive;



};

#endif /* SRC_AUTOGEARPLACE_H_ */
