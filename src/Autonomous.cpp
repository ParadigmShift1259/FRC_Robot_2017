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
//	if (m_driverstation->IsAutonomous())
		m_stage = kStart;
//	else
//		m_stage = kIdle;
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
	SmartDashboard::PutNumber("AU8_distancepos", distancepos);

	m_drivetrain->Drive(0, power, true);
	if ((-m_leftposition > distancepos) || (m_rightposition > distancepos))
	{
		m_drivetrain->Drive(0, 0);
		m_drivetrain->LeftTalon()->SetPosition(0);
		m_drivetrain->RightTalon()->SetPosition(0);
		return true;
	}
	return false;
}


bool Autonomous::TurnDegree(double degrees){
	//double Conversion = degrees *  SmartDashboard::GetNumber("DB/Slider 3", 0);
	double Conversion = degrees * 0.0444;
	if (degrees < 0) {
		m_drivetrain->Drive(-0.5, 0); //right turn
		if((m_leftposition < Conversion) || (-m_rightposition < Conversion))
			{
				m_drivetrain->Drive(0, 0);
				return true;
			}
	} else {
		m_drivetrain->Drive(0.5, 0); //left turn
		if((m_leftposition > Conversion) || (-m_rightposition > Conversion))
			{
				m_drivetrain->Drive(0, 0);
				return true;
			}
	}


	return false;
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
	SmartDashboard::PutNumber("AU9_auto", autoselected);

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
			m_stage = kStage1;
			break;

		case kStage1:
			DriverStation::ReportError("stage1");
			Wait(0.1);
			if (GoStraight(6.0, -1.0))
			{
				m_stage = kStage2;
			}
			break;

		case kStage2:
			DriverStation::ReportError("stage2");
			Wait(0.1);
			if (TurnDegree(-60))
			{
				m_stage = kStage3;
			}
			break;

		case kStage3:
			DriverStation::ReportError("stage3");
			Wait(0.1);
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
		switch (m_stage)
		{
		case kIdle:
			m_drivetrain->Drive(0, 0);
			break;

		case kStart:
			DriverStation::ReportError("start");
			m_drivetrain->LeftTalon()->SetPosition(0);
			m_drivetrain->RightTalon()->SetPosition(0);
			m_stage = kStage1;
			break;

		case kStage1:
			DriverStation::ReportError("stage1");
			Wait(0.1);
			if (GoStraight(6.0, 1.0))
			{
				m_stage = kStage2;
			}
			break;

		case kStage2:
			DriverStation::ReportError("stage2");
			Wait(0.1);
			if (TurnDegree(60))
			{
				m_stage = kStage3;
			}
			break;

		case kStage3:
			DriverStation::ReportError("stage3");
			Wait(0.1);
			if (GoStraight(6.0, -1.0))
				m_stage = kDeploy;
			break;

		case kDeploy:
			DriverStation::ReportError("deploy");
			m_stage = kIdle;
			break;
		}
		break;

	case kAutoRedShoot:
		switch (m_stage)
		{
		case kIdle:
			m_drivetrain->Drive(0, 0);
			break;

		case kStart:
			DriverStation::ReportError("start");
			m_drivetrain->LeftTalon()->SetPosition(0);
			m_drivetrain->RightTalon()->SetPosition(0);
			m_stage = kStage1;
			break;

		case kStage1:
			DriverStation::ReportError("stage1");
			Wait(0.1);
			if (GoStraight(7.15, -1.0))
			{
				m_stage = kStage2;
			}
			break;

		case kStage2:
			DriverStation::ReportError("stage2");
			Wait(0.1);
			if (TurnDegree(-90))
			{
				m_stage = kStage3;
			}
			break;

		case kStage3:
			DriverStation::ReportError("stage3");
			Wait(0.1);
			if (GoStraight(3.5, -1.0))
				m_stage = kDeploy;
			break;

		case kDeploy:
			DriverStation::ReportError("deploy");
			m_stage = kIdle;
			break;
		}
		break;


	case kAutoBlueShoot:
		switch (m_stage)
		{
		case kIdle:
			m_drivetrain->Drive(0, 0);
			break;

		case kStart:
			DriverStation::ReportError("start");
			m_drivetrain->LeftTalon()->SetPosition(0);
			m_drivetrain->RightTalon()->SetPosition(0);
			m_stage = kStage1;
			break;

		case kStage1:
			DriverStation::ReportError("stage1");
			Wait(0.1);
			if (GoStraight(7.15, -1.0))
			{
				m_stage = kStage2;
			}
			break;

		case kStage2:
			DriverStation::ReportError("stage2");
			Wait(0.1);
			if (TurnDegree(90))
			{
				m_stage = kStage3;
			}
			break;

		case kStage3:
			DriverStation::ReportError("stage3");
			Wait(0.1);
			if (GoStraight(3.5, -1.0))
				m_stage = kDeploy;
			break;

		case kDeploy:
			DriverStation::ReportError("deploy");
			m_stage = kIdle;
			break;
		}
		break;

	case kAutoStraight:
		switch (m_stage)
		{
		case kIdle:
			m_drivetrain->Drive(0, 0);
			break;

		case kStart:
			DriverStation::ReportError("start");
			m_drivetrain->LeftTalon()->SetPosition(0);
			m_drivetrain->RightTalon()->SetPosition(0);
			m_stage = kStage1;
			break;

		case kStage1:
			DriverStation::ReportError("stage1");
			Wait(0.1);
			if (GoStraight(6.625, -1.0))
			{
				m_stage = kDeploy;
			}
			break;
		case kDeploy:
			break;
		default:
			break;
		break;
		}
	}
}
