/**
 *  Autonomous.cpp
 *  Date: 2/18/17
 *  Last Edited By: Eric
 *  Note:
 */


#include <Autonomous.h>


Autonomous::Autonomous(DriverStation *driverstation, Drivetrain *drivetrain, DriveAngle *driveangle, Picker *picker, OperatorInputs *operatorinputs)
{
	m_driverstation = driverstation;
	m_drivetrain = drivetrain;
	m_driveangle = driveangle;
	m_inputs = operatorinputs;
	m_stage = kIdle;
	m_turning = false;
	m_leftposition = 0;
	m_rightposition = 0;
	start = false;
	Test = 0;
	m_picker = picker;
}


Autonomous::~Autonomous()
{

}


void Autonomous::Init()
{
	start = false;
	Test = 0;
	//m_stage = kIdle;
	m_turning = false;
	m_leftposition = 0;
	m_rightposition = 0;
	//if (m_driverstation->IsAutonomous())
	m_stage = kStart;
}


void Autonomous::Stop()
{
	m_stage = kIdle;
}

/*
bool Autonomous::GoStraight(double feet, double power)
{
	double leftposition = m_drivetrain->LeftTalon()->GetPosition();
	double rightposition = m_drivetrain->RightTalon()->GetPosition();

	double kSFoot = SmartDashboard::GetNumber("DB/Slider 0", 0);
	if (kSFoot == 0) {kSFoot = 0.87;}									// Old: 0.955
	SmartDashboard::PutNumber("AU6_kSFoot", kSFoot);

	if (feet > 0)
	{
		double distancepos = feet * kSFoot;
		SmartDashboard::PutNumber("AU8_distancepos", distancepos);

		m_driveangle->Drive(power, true);
		if ((leftposition > distancepos) || (-rightposition > distancepos))
		{
			m_driveangle->Stop();
			m_driveangle->Drive(0);
			m_drivetrain->Drive(0, 0);
			m_drivetrain->LeftTalon()->SetPosition(0);
			m_drivetrain->RightTalon()->SetPosition(0);
			Wait(0.25); //change this
			m_driveangle->Init();
			return true;
		}
	}
	else
	{
		double distancepos = -feet * kSFoot;
		SmartDashboard::PutNumber("AU8_distancepos", distancepos);

		m_driveangle->Drive(power, true);
		if ((-leftposition > distancepos) || (rightposition > distancepos))
		{
			m_driveangle->Stop();
			m_driveangle->Drive(0);
			m_drivetrain->Drive(0, 0);
			m_drivetrain->LeftTalon()->SetPosition(0);
			m_drivetrain->RightTalon()->SetPosition(0);
			Wait(0.25);
			m_driveangle->Init();
			return true;
		}
	}
	return false;
}
*/

bool Autonomous::GoStraight(double feet, double power, double rampdist)
{
	double leftposition = m_drivetrain->LeftTalon()->GetPosition();
	double rightposition = m_drivetrain->RightTalon()->GetPosition();

	double kSFoot = SmartDashboard::GetNumber("DB/Slider 0", 0);
	if (kSFoot == 0) {kSFoot = 0.87;}									// Old: 0.955
	SmartDashboard::PutNumber("AU6_kSFoot", kSFoot);

	int direction = feet > 0 ? 1 : -1;

	double distancepos = feet * kSFoot;
	SmartDashboard::PutNumber("AU8_distancepos", distancepos);

	double distancetotarget = distancepos - ((leftposition - rightposition) / 2);
	//m_driveangle->Drive(power, true);

	if (((leftposition * direction) > (distancepos * direction)) || ((-rightposition * direction) > (distancepos * direction)))
	{
		m_driveangle->Stop();
		m_driveangle->Drive(0);
		m_drivetrain->Drive(0, 0);
		m_drivetrain->LeftTalon()->SetPosition(0);
		m_drivetrain->RightTalon()->SetPosition(0);
		Wait(0.25);
		m_driveangle->Init();
		return true;
	}
	return false;
}


bool Autonomous::TurnDegree(double degrees)
{
	if (!m_turning)
	{
		m_turning = true;
		m_driveangle->SetRelativeAngle(degrees);
	}
	else
	if (m_driveangle->IsOnTarget())
	{
		m_turning = false;
		m_driveangle->Stop();
		m_drivetrain->Drive(0, 0);
		m_drivetrain->LeftTalon()->SetPosition(0);
		m_drivetrain->RightTalon()->SetPosition(0);
		Wait(0.25); //replace this
		m_driveangle->Init();
		return true;
	}
	return false;
}


/*
void Autonomous::Loop(Auto autoselected)
{
	if (start == false){
		Test = SmartDashboard::GetNumber("DB/Slider 1", 0);
		start = true;
	}

	switch (Test) {
		case 0:
			m_driveangle->Drive(0);
			break;
		case 1:
			if (GoStraight(6.3, -0.625)){
				Test = 0;
			}
			break;
		case 2:
			if (TurnDegree(60)){
				Test = 0;
			}
			break;
		case 3:
			if (GoStraight(5.3, -0.625)){
				Test = 0;
			}
			break;
	}

}
*/
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
			m_driveangle->Drive(0);
			break;

		case kStart:
			DriverStation::ReportError("start");
			m_driveangle->Stop();
			m_drivetrain->LeftTalon()->SetPosition(0);
			m_drivetrain->RightTalon()->SetPosition(0);
			Wait(0.1);
			m_driveangle->Init();
			m_stage = kStage1;
			break;

		case kStage1:
			DriverStation::ReportError("stage1");
			if (GoStraight(6.3, -0.625))
				m_stage = kStage2;
			break;

		case kStage2:
			DriverStation::ReportError("stage2");
			if (TurnDegree(-60))
				m_stage = kStage3;
			break;

		case kStage3:
			DriverStation::ReportError("stage3");
			if (GoStraight(5.3, -0.625))
				m_stage = kDeploy;
			break;

		case kDeploy:
			DriverStation::ReportError("deploy");
			m_picker->Deploy();
			m_stage = kIdle;
			break;
		}
		break;

	case kAutoRightGear:
		switch (m_stage)
		{
		case kIdle:
			m_driveangle->Drive(0);
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
			if (GoStraight(6.3, -0.625))
				m_stage = kStage2;
			break;

		case kStage2:
			DriverStation::ReportError("stage2");
			if (TurnDegree(60))
				m_stage = kStage3;
			break;

		case kStage3:
			DriverStation::ReportError("stage3");
			if (GoStraight(5.3, -0.625))
				m_stage = kDeploy;
			break;

		case kDeploy:
			DriverStation::ReportError("deploy");
			m_picker->Deploy();
			m_stage = kIdle;
			break;
		}
		break;

	case kAutoRedShoot:
		switch (m_stage)
		{
		case kIdle:
			m_driveangle->Drive(0);
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
			if (GoStraight(7.04, -0.625))
				m_stage = kStage2;
			break;

		case kStage2:
			DriverStation::ReportError("stage2");
			if (TurnDegree(90))
				m_stage = kStage3;
			break;

		case kStage3:
			DriverStation::ReportError("stage3");
			if (GoStraight(-3.375, 0.625))
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
			m_driveangle->Drive(0);
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
			if (GoStraight(7.04, -0.625))
				m_stage = kStage2;
			break;

		case kStage2:
			DriverStation::ReportError("stage2");
			if (TurnDegree(-90))
				m_stage = kStage3;
			break;

		case kStage3:
			DriverStation::ReportError("stage3");
			if (GoStraight(-3.375, 0.625))
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
			m_driveangle->Drive(0);
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
			if (GoStraight(6.625, -0.625))
				m_stage = kDeploy;
			break;

		case kDeploy:
			m_picker->Deploy();
			m_stage = kIdle;
			break;

		default:
			break;
		break;
		}
	}
}

