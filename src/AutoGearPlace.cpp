/*
 * AutoGearPlace.cpp
 *
 *  Created on: Jan 25, 2017
 *      Author: Developer
 */

#include <AutoGearPlace.h>
#include <math.h>

#define P_VALUE 0.005
#define I_VALUE 0.0
#define D_VALUE 0.0

AutoGearPlace::AutoGearPlace(std::shared_ptr<NetworkTable> newTable, Drivetrain *drive) : PIDSubsystem("AutoGearPlace",P_VALUE,I_VALUE,D_VALUE)
{
	isActive = false;
	m_drivetrain = drive;
	m_netTable = newTable;
	SetSetpoint(0);
}

double AutoGearPlace::ReturnPIDInput()
{
	return m_netTable->GetNumber("xPos",0);
}

void AutoGearPlace::changeActive(bool newState)
{
	if(newState)
	{
		isActive = true;
		Enable();
	}
	else if (!newState)
	{
		isActive = false;
		Disable();
	}
}

bool AutoGearPlace::isDone()
{
	bool retval = m_netTable->GetNumber("xSpread", 0) > 400;
	m_netTable->PutBoolean("AGP_isDone", retval);
	return retval;
}

void AutoGearPlace::UsePIDOutput(double output)
{
	m_netTable->PutNumber("output", output);
	if (isActive)
	{
		output = std::abs(output) > 0.25 ? output : 0.25 * output / std::abs(output);
		m_drivetrain->Drive(-output, 0, false);
	}
}

AutoGearPlace::~AutoGearPlace() {

}

