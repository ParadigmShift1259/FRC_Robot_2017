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
//	if (m_driverstation->IsAutonomous())
		m_stage = kStart;
//	else
//		m_stage = kIdle;
}


void Autonomous::Stop()
{
	m_stage = kIdle;
}


bool Autonomous::GoStraight(double feet, double power)
{
	double leftposition = m_drivetrain->LeftTalon()->GetPosition();
	double rightposition = m_drivetrain->RightTalon()->GetPosition();

	double kSFoot = SmartDashboard::GetNumber("DB/Slider 0", 0);
	if (kSFoot == 0) {kSFoot = 0.95;}
	SmartDashboard::PutNumber("AU6_kSFoot", kSFoot);

	if (feet > 0)
	{
		double distancepos = feet * kSFoot;
		SmartDashboard::PutNumber("AU8_distancepos", distancepos);

		m_drivetrain->Drive(0, power, true);
		if ((leftposition > distancepos) || (-rightposition > distancepos))
		{
			m_drivetrain->Drive(0, 0);
			m_drivetrain->LeftTalon()->SetPosition(0);
			m_drivetrain->RightTalon()->SetPosition(0);
			Wait(0.1);
			return true;
		}
	}
	else
	{
		double distancepos = -feet * kSFoot;
		SmartDashboard::PutNumber("AU8_distancepos", distancepos);

		m_drivetrain->Drive(0, power, true);
		if ((-leftposition > distancepos) || (rightposition > distancepos))
		{
			m_drivetrain->Drive(0, 0);
			m_drivetrain->LeftTalon()->SetPosition(0);
			m_drivetrain->RightTalon()->SetPosition(0);
			Wait(0.1);
			return true;
		}
	}
	return false;
}


bool Autonomous::TurnDegree(double degrees)
{
	double leftposition = m_drivetrain->LeftTalon()->GetPosition();
	double rightposition = m_drivetrain->RightTalon()->GetPosition();

	double kSDegree = SmartDashboard::GetNumber("DB/Slider 1", 0);
	if (kSDegree == 0) {kSDegree = 0.0188;}
	SmartDashboard::PutNumber("AU7_kSDegree", kSDegree);

	if (degrees < 0)
	{
		double Conversion = degrees * -kSDegree;
		SmartDashboard::PutNumber("AU8_Conversion", Conversion);
		//SmartDashboard::PutNumber("AUA_leftpos", leftposition);
		//SmartDashboard::PutNumber("AUB_rightpos", rightposition);
		//DriverStation::ReportError("here 1");
		m_drivetrain->Drive(0.375, 0); //left turn
		if ((leftposition > Conversion) || (rightposition > Conversion))
		{
			//DriverStation::ReportError("here 2");
			m_drivetrain->Drive(0, 0);
			m_drivetrain->LeftTalon()->SetPosition(0);
			m_drivetrain->RightTalon()->SetPosition(0);
			Wait(0.1);
			return true;
		}
	}
	else
	{
		double Conversion = degrees * kSDegree;
		SmartDashboard::PutNumber("AU8_Conversion", Conversion);
		//SmartDashboard::PutNumber("AUA_leftpos", leftposition);
		//SmartDashboard::PutNumber("AUB_rightpos", rightposition);
		//DriverStation::ReportError("here 3");
		m_drivetrain->Drive(-0.375, 0); //right turn
		if ((-leftposition > Conversion) || (-rightposition > Conversion))
		{
			//DriverStation::ReportError("here 4");
			m_drivetrain->Drive(0, 0);
			m_drivetrain->LeftTalon()->SetPosition(0);
			m_drivetrain->RightTalon()->SetPosition(0);
			Wait(0.1);
			return true;
		}
	}
	return false;
}


void Autonomous::Loop(Auto autoselected)
{
	double leftvolts = m_drivetrain->LeftTalon()->GetOutputVoltage();
	double rightvolts = m_drivetrain->RightTalon()->GetOutputVoltage();

	SmartDashboard::PutNumber("AU1_leftvolts", leftvolts);
	SmartDashboard::PutNumber("AU2_rightvolts", rightvolts);
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
			Wait(0.1);
			m_stage = kStage1;
			break;

		case kStage1:
			DriverStation::ReportError("stage1");
			if (GoStraight(6.0, -0.625))
				m_stage = kStage2;
			break;

		case kStage2:
			DriverStation::ReportError("stage2");
			Wait(0.1);
			if (TurnDegree(-60))
				m_stage = kStage3;
			break;

		case kStage3:
			DriverStation::ReportError("stage3");
			if (GoStraight(6.0, -0.625))
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
			Wait(0.1);
			m_stage = kStage1;
			break;

		case kStage1:
			DriverStation::ReportError("stage1");
			if (GoStraight(6.0, -1.0))
				m_stage = kStage2;
			break;

		case kStage2:
			DriverStation::ReportError("stage2");
			if (TurnDegree(60))
				m_stage = kStage3;
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
			Wait(0.1);
			m_stage = kStage1;
			break;

		case kStage1:
			DriverStation::ReportError("stage1");
			if (GoStraight(7.15, -1.0))
				m_stage = kStage2;
			break;

		case kStage2:
			DriverStation::ReportError("stage2");
			if (TurnDegree(-90))
				m_stage = kStage3;
			break;

		case kStage3:
			DriverStation::ReportError("stage3");
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
			Wait(0.1);
			m_stage = kStage1;
			break;

		case kStage1:
			DriverStation::ReportError("stage1");
			if (GoStraight(7.15, -1.0))
				m_stage = kStage2;
			break;

		case kStage2:
			DriverStation::ReportError("stage2");
			if (TurnDegree(90))
				m_stage = kStage3;
			break;

		case kStage3:
			DriverStation::ReportError("stage3");
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
			Wait(0.1);
			m_stage = kStage1;
			break;

		case kStage1:
			DriverStation::ReportError("stage1");
			if (GoStraight(6.625, -1.0))
				m_stage = kDeploy;
			break;

		case kDeploy:
			break;

		default:
			break;
		break;
		}
	}
}
