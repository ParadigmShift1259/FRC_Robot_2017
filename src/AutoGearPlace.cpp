/*
 * AutoGearPlace.cpp
 *
 *  Created on: Jan 25, 2017
 *      Author: Developer
 */

#include <AutoGearPlace.h>
#include <math.h>



AutoGearPlace::AutoGearPlace(std::shared_ptr<NetworkTable> newTable, Drivetrain *drive, OperatorInputs * oi) : PIDSubsystem("AutoGearPlace", 0, 0, 0)
{
	isActive = false;
	m_drivetrain = drive;
	m_netTable = newTable;
	m_inputs = oi;
	isInitialized = false;
	ChangeActive(false);
	SetAbsoluteTolerance(3);

}

double AutoGearPlace::ReturnPIDInput()
{
	return ReturnCurrentPosition();
}

void AutoGearPlace::ChangeActive(bool newState)
{
	if(newState)
	{
		isActive = true;
		Enable();
	}
	else if (!newState)
	{
		Disable();
		isActive = false;
	}
}

bool AutoGearPlace::IsDone()
{
	bool retval = m_netTable->GetNumber("xSpread", 0) > 400;
	m_netTable->PutBoolean("AGP_isDone", retval);
	return retval;
}

void AutoGearPlace::SetNewRelativeSetpoint(double newSetPoint)
{
	if(isInitialized == false)
		SetSetpoint(ReturnCurrentPosition());

	newSetPoint -= GetPIDController()->GetError();
	SetSetpointRelative(newSetPoint);

}

void AutoGearPlace::UsePIDOutput(double output)
{

	m_netTable->PutNumber("output", output);
	if (isActive)
	{
		//output = std::abs(output) > 0.25 ? output : 0.25 * output / std::abs(output);
		m_drivetrain->Drive(output, m_inputs->xBoxLeftY(), true);
	}
}

void AutoGearPlace::CheckPIDValues()
{
	if(GetPIDController()->GetP() != SmartDashboard::GetValue("DB/Slider 0")->GetDouble() || GetPIDController()->GetI() != SmartDashboard::GetValue("DB/Slider 1")->GetDouble() ||GetPIDController()->GetD() != SmartDashboard::GetValue("DB/Slider 2")->GetDouble())
		GetPIDController()->SetPID(SmartDashboard::GetValue("DB/Slider 0")->GetDouble(), SmartDashboard::GetValue("DB/Slider 1")->GetDouble(), SmartDashboard::GetValue("DB/Slider 2")->GetDouble());
}

double AutoGearPlace::ReturnCurrentPosition()
{
	return ((360/(2*3.1415926535))*((m_drivetrain->LeftTalon()->GetPosition()+m_drivetrain->RightTalon()->GetPosition())*WHEEL_CIRCUMFERENCE*3.1415926535)/(WHEEL_BASE));
}

AutoGearPlace::~AutoGearPlace() {

}

