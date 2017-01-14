/*
 * Shooter.cpp
 *
 *  Created on: Jan 11, 2017
 *      Author: Developer
 */

#include <Shooter.h>
#include "smartdashboard/smartdashboard.h"

Shooter::Shooter(OperatorInputs *opIn)
{

	input = opIn;
	m_shooterMotor = new Spark(2);
	dashNum = 0;
}

Shooter::~Shooter() {
	// TODO Auto-generated destructor stub
}


void Shooter::Loop()
{
	AdjustSpeed();
}

void Shooter::AdjustSpeed()
{

	dashNum =   SmartDashboard::GetNumber("DB/Slider 0", 0.0);
	//dashNum = dashNum - 1;

	if (dashNum > 1)
	{
		dashNum = 1;
	}

	if (dashNum < (-1))
	{
		dashNum = (-1);
	}

	SmartDashboard::PutNumber("VT1_leftpos", dashNum);
	m_shooterMotor->Set(dashNum);
}
