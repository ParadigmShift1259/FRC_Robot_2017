// DriveAnglePID.cpp


#include <DriveAnglePID.h>
#include <math.h>


DriveAnglePID::DriveAnglePID(Drivetrain *drive) : PIDSubsystem("DriveAngle", 0, 0, 0)
{
	m_drivetrain = drive;
	m_netTable = NetworkTable::GetTable("OpenCV");
	isActive = false;
	m_y = 0;
	isInitialized = false;
	ChangeActive(false);
	SetAbsoluteTolerance(0.3);
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
		isActive = true;
		Enable();
	}
	else
	if (!newState)
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
	if (isInitialized == false)
		SetSetpoint(ReturnCurrentPosition());

	newSetPoint -= GetPIDController()->GetError();
	SetSetpointRelative(newSetPoint);
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
	if (GetPIDController()->GetP() != SmartDashboard::GetValue("DB/Slider 0")->GetDouble() ||
		GetPIDController()->GetI() != SmartDashboard::GetValue("DB/Slider 1")->GetDouble() ||
		GetPIDController()->GetD() != SmartDashboard::GetValue("DB/Slider 2")->GetDouble())
		GetPIDController()->SetPID(SmartDashboard::GetValue("DB/Slider 0")->GetDouble(),
								   SmartDashboard::GetValue("DB/Slider 1")->GetDouble(),
								   SmartDashboard::GetValue("DB/Slider 2")->GetDouble());
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
