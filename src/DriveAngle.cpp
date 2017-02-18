/**
 *  DriveAngle.cpp
 *  Date:
 *  Last Edited By:
 */


#include <DriveAngle.h>


DriveAngle::DriveAngle(Drivetrain *drivetrain, OperatorInputs *inputs)
{
	m_drivetrain = drivetrain;
	m_inputs = inputs;
	m_driveAnglePID = new DriveAnglePID(drivetrain);
	m_angle = 0;
}


DriveAngle::~DriveAngle()
{
}


void DriveAngle::EnableAnglePID()
{
	m_driveAnglePID->CheckPIDValues();
	m_driveAnglePID->SetNewRelativeSetpoint(0);
	m_driveAnglePID->ChangeActive(true);
}


void DriveAngle::DisableAnglePID()
{
	m_driveAnglePID->ChangeActive(false);
}


void DriveAngle::SetRelativeAngle(double angleTarget)
{
	m_driveAnglePID->CheckPIDValues();
	m_driveAnglePID->SetNewRelativeSetpoint(angleTarget);
}


double DriveAngle::GetAngle()
{
	return m_driveAnglePID->ReturnCurrentPosition();
}


bool DriveAngle::IsOnTarget()
{
	return m_driveAnglePID->OnTarget();
}


void DriveAngle::Init()
{
	SmartDashboard::PutNumber("DB/Slider 3", m_angle);
	EnableAnglePID();
}


void DriveAngle::Loop()
{
	static unsigned int loopcnt = 0;
	static unsigned int shiftcnt = 0;
	double y;

	double newangle = SmartDashboard::GetNumber("DB/Slider 3", 0);
	if (m_angle != newangle)
	{
		SetRelativeAngle(newangle);
		m_angle = newangle;
	}
	SmartDashboard::PutNumber("DTAngle", GetAngle());

	m_driveAnglePID->CheckPIDValues();

	if (m_inputs->xBoxLeftTrigger())
	{
		m_drivetrain->m_shift = true;
		m_drivetrain->m_lowspeedmode = false;
	}

	m_drivetrain->LowSpeedDriving();

	y = m_inputs->xBoxLeftY();

	if (m_drivetrain->m_isdownshifting)
		y = 0;

	if (m_drivetrain->m_lowspeedmode)
	{
		//x = x * LOWSPEED_MODIFIER_X;
		y = y * LOWSPEED_MODIFIER_Y;
	}

	Drive(y, true);

	if (m_drivetrain->m_shift)
	{
		shiftcnt += 4;
		if (m_drivetrain->m_ishighgear)
		{
			m_drivetrain->m_isdownshifting = true;
			shiftcnt += 2;
		}
		else
		{
			m_drivetrain->Shift();
			m_drivetrain->m_isdownshifting = false;
			shiftcnt += 1;
		}
	}

	if (m_drivetrain->m_isdownshifting && (abs(m_drivetrain->m_previousx * X_SCALING) < ENCODER_TOP_SPEED) && (abs(m_drivetrain->m_previousy * Y_SCALING) < ENCODER_TOP_SPEED))
	{
		loopcnt++;
		m_drivetrain->Shift();
		m_drivetrain->m_isdownshifting = false;
	}

	SmartDashboard::PutNumber("DT02_y", y);
	SmartDashboard::PutNumber("DT03_top", ENCODER_TOP_SPEED);
	SmartDashboard::PutNumber("DT04_loop_count", loopcnt);
	SmartDashboard::PutNumber("DT05_shift", m_drivetrain->m_shift);
	SmartDashboard::PutNumber("DT06_shift_count", shiftcnt);
	SmartDashboard::PutNumber("DT07_shift_down", m_drivetrain->m_isdownshifting);
	SmartDashboard::PutNumber("DT08_abs_x", (abs(m_drivetrain->m_previousx * X_SCALING) < ENCODER_TOP_SPEED));
	SmartDashboard::PutNumber("DT09_abs_y", (abs(m_drivetrain->m_previousy * Y_SCALING) < ENCODER_TOP_SPEED));
}


void DriveAngle::Stop()
{
	DisableAnglePID();
	m_driveAnglePID->SetSetpoint(0);
	m_angle = 0;
}


void DriveAngle::Drive(double y, bool ramp)
{
	m_driveAnglePID->SetY(y);
	m_driveAnglePID->SetRamp(ramp);
}
