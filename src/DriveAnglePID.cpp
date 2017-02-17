// DriveAnglePID.cpp


#include <DriveAnglePID.h>
#include <math.h>


DriveAnglePID::DriveAnglePID(Drivetrain *drive) : PIDSubsystem("DriveAngle", 0, 0, 0)
{
	m_drivetrain = drive;
	m_netTable = NetworkTable::GetTable("OpenCV");
	isInitialized = false;
	isActive = false;
	m_y = 0;
	m_ramp = false;
	SetAbsoluteTolerance(1.0);
}


DriveAnglePID::~DriveAnglePID()
{
}


double DriveAnglePID::ReturnPIDInput()
{
	return ReturnCurrentPosition();
}


void DriveAnglePID::ChangeActive(bool newState)
{
	if (newState)
	{
		Enable();
		isActive = true;
	}
	else
	{
		Disable();
		isActive = false;
		isInitialized = false;
	}
}


bool DriveAnglePID::IsDone()
{
	bool retval = m_netTable->GetNumber("xSpread", 0) > 400;
	m_netTable->PutBoolean("AGP_isDone", retval);
	return retval;
}


void DriveAnglePID::SetNewRelativeSetpoint(double newSetPoint)
{
	if (!isInitialized)
	{
		GetPIDController()->Reset();
		//SetSetpoint(ReturnCurrentPosition());
		SetSetpointRelative(0);
		isInitialized = true;
	}
	else
	{
		newSetPoint -= GetPIDController()->GetError();
		SetSetpointRelative(newSetPoint);
	}
}


void DriveAnglePID::UsePIDOutput(double output)
{
	m_netTable->PutNumber("output", output);
	if (isActive)
	{
		//output = std::abs(output) > 0.25 ? output : 0.25 * output / std::abs(output);
		m_drivetrain->Drive(output, m_y, true);
	}
}


void DriveAnglePID::CheckPIDValues()
{
	GetPIDController()->SetPID(0.1, 0.001, 0);
/*
	if (GetPIDController()->GetP() != SmartDashboard::GetValue("DB/Slider 0")->GetDouble() ||
		GetPIDController()->GetI() != SmartDashboard::GetValue("DB/Slider 1")->GetDouble() ||
		GetPIDController()->GetD() != SmartDashboard::GetValue("DB/Slider 2")->GetDouble())
		GetPIDController()->SetPID(SmartDashboard::GetValue("DB/Slider 0")->GetDouble(),
								   SmartDashboard::GetValue("DB/Slider 1")->GetDouble(),
								   SmartDashboard::GetValue("DB/Slider 2")->GetDouble());
*/
}


double DriveAnglePID::ReturnCurrentPosition()
{
	return ((360/(2*3.1415926535))*((m_drivetrain->LeftTalon()->GetPosition()+m_drivetrain->RightTalon()->GetPosition())*WHEEL_CIRCUMFERENCE*3.1415926535)/(WHEEL_BASE));
}


void DriveAnglePID::SetY(double y)
{
	m_y = (y >= -1.0) ? ((y <= 1.0) ? y : 1.0) : -1.0;
}


double DriveAnglePID::GetY()
{
	return m_y;
}


void DriveAnglePID::SetRamp(bool ramp)
{
	m_ramp = ramp;
}


bool DriveAnglePID::GetRamp()
{
	return m_ramp;
}
