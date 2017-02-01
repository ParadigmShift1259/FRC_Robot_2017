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

AutoGearPlace::AutoGearPlace(NetworkTable *newTable) : PIDSubsystem("AutoGearPlace",P_VALUE,0,0)
{
	netTable = newTable;

}

double AutoGearPlace::ReturnPIDInput()
{
	return netTable->GetNumber("xPos",0);
}


void AutoGearPlace::UsePIDOutput(double output)
{

}

AutoGearPlace::~AutoGearPlace() {
	// TODO Auto-generated destructor stub
}

