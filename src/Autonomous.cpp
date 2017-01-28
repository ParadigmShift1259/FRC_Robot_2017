// Autonomous.cpp


#include <Autonomous.h>


Autonomous::Autonomous(DriverStation *driverstation, Drivetrain *drivetrain, OperatorInputs *operatorinputs)
{
	m_driverstation = driverstation;
	m_drivetrain = drivetrain;
	m_inputs = operatorinputs;
	m_stage = kIdle;
	m_leftposition = 0;
	m_rightposition = 0;
}


Autonomous::~Autonomous()
{

}


void Autonomous::Init()
{
	m_timer.Stop();
	m_timer.Reset();
	m_leftposition = 0;
	m_rightposition = 0;
	if (m_driverstation->IsAutonomous())
		m_stage = kStart;
	else
		m_stage = kIdle;
}


void Autonomous::Stop()
{
	m_timer.Stop();
	m_timer.Reset();
	m_stage = kIdle;
}


bool Autonomous::GoStraight(double feet, double power)
{
	double kSFoot = SmartDashboard::GetNumber("DB/Slider 0", 0);
	if (kSFoot == 0) {kSFoot = 2.24;}
	SmartDashboard::PutNumber("AU6_kSFoot", kSFoot);

	double distancepos = feet * kSFoot;
	m_drivetrain->Drive(0, power, true);
	if ((m_leftposition > distancepos) || (-m_rightposition > distancepos))
	{
		m_drivetrain->Drive(0, 0);
		m_drivetrain->LeftTalon()->SetPosition(0);
		m_drivetrain->RightTalon()->SetPosition(0);
		return true;
	}
	return false;
}


bool Autonomous::TurnDegree(double degrees)
{
	double kSDegree = SmartDashboard::GetNumber("DB/Slider 1", 0);
	if (kSDegree == 0) {kSDegree = 0.027;}
	SmartDashboard::PutNumber("AU7_kSDegree", kSDegree);

	double distancepos = degrees * kSDegree;
	if (degrees > 0.0)
	{
		m_drivetrain->Drive(-0.5, 0);
		if ((m_leftposition > distancepos) || (-m_rightposition > distancepos))
		{
			m_drivetrain->Drive(0, 0);
			m_drivetrain->LeftTalon()->SetPosition(0);
			m_drivetrain->RightTalon()->SetPosition(0);
			return true;
		}
		return false;
	}
	else
	{
		m_drivetrain->Drive(0.5, 0);
		if ((-m_leftposition > distancepos) || (m_rightposition > distancepos))
		{
			m_drivetrain->Drive(0, 0);
			m_drivetrain->LeftTalon()->SetPosition(0);
			m_drivetrain->RightTalon()->SetPosition(0);
			return true;
		}
		return false;
	}
}


void Autonomous::Loop(Auto autoselected)
{
	double leftvolts = m_drivetrain->LeftTalon()->GetOutputVoltage();
	double rightvolts = m_drivetrain->RightTalon()->GetOutputVoltage();
	m_leftposition = m_drivetrain->LeftTalon()->GetPosition();
	m_rightposition = m_drivetrain->RightTalon()->GetPosition();

	SmartDashboard::PutNumber("AU1_leftvolts", leftvolts);
	SmartDashboard::PutNumber("AU2_rightvolts", rightvolts);
	SmartDashboard::PutNumber("AU3_leftpos", m_leftposition);
	SmartDashboard::PutNumber("AU4_rightpos", m_rightposition);

	switch (autoselected)
	{
	case kAutoLeftGear:

		switch (m_stage)
		{
		case kIdle:
			m_drivetrain->Drive(0, 0);
			break;

		case kStart:
			DriverStation::ReportError("start");
			m_drivetrain->LeftTalon()->SetPosition(0);
			m_drivetrain->RightTalon()->SetPosition(0);
			Wait(0.1);
			m_stage = kStage1;
			break;

		case kStage1:
			DriverStation::ReportError("stage1");
			if (GoStraight(6.0, -1.0))
			{
				m_stage = kStage2;
				Wait(0.1);
			}
			break;

		case kStage2:
			DriverStation::ReportError("stage2");
			if (TurnDegree(60))
			{
				m_stage = kStage3;
				Wait(0.1);
			}
			break;

		case kStage3:
			DriverStation::ReportError("stage3");
			if (GoStraight(6.0, -1.0))
				m_stage = kDeploy;
			break;

		case kDeploy:
			DriverStation::ReportError("deploy");
			m_stage = kIdle;
			break;
		}
		break;

	case kAutoRightGear:
		break;

	case kAutoRedShoot:
		break;

	case kAutoBlueShoot:
		break;

	case kAutoStraight:
		break;
	}
}
