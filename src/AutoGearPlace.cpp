/*
 * AutoGearPlace.cpp
 *
 *  Created on: Jan 25, 2017
 *      Author: Developer
 */

#include <AutoGearPlace.h>

#define P_VALUE 0.01
#define I_VALUE 0.001
#define D_VALUE 0.0001

AutoGearPlace::AutoGearPlace(NetworkTable *newTable, Drivetrain *drive) : PIDSubsystem("AutoGearPlace",P_VALUE,I_VALUE,D_VALUE)
{
	m_drivetrain = drive;
	m_netTable = newTable;
}

double AutoGearPlace::ReturnPIDInput()
{
	return m_netTable->GetNumber("xPos",0);
}

void AutoGearPlace::changeActive(bool newState)
{
	if(newState)
	{
		Enable();
	}
	else
	{
		Disable();
	}
}

bool AutoGearPlace::isDone()
{
	return (m_netTable->GetNumber("xSpread", 0) > 100);
}

void AutoGearPlace::UsePIDOutput(double output)
{
	m_drivetrain->Drive(output, .5, false);
}

AutoGearPlace::~AutoGearPlace() {

}

