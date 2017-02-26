/**
 *  Autonomous.cpp
 *  Date: 2/18/17
 *  Last Edited By: Eric
 *  Note:
 */


#include <Autonomous.h>


Autonomous::Autonomous(DriverStation *driverstation, Drivetrain *drivetrain, DriveAngle *driveangle, VisionTarget *visiontarget, Picker *picker, OperatorInputs *operatorinputs)
{
	m_visiontarget = visiontarget;
	m_driverstation = driverstation;
	m_drivetrain = drivetrain;
	m_driveangle = driveangle;
	m_inputs = operatorinputs;
	m_stage = kIdle;
	m_turning = false;
	m_leftposition = 0;
	m_rightposition = 0;
	m_picker = picker;
}


Autonomous::~Autonomous()
{

}


void Autonomous::Init()
{
	m_turning = false;
	m_leftposition = 0;
	m_rightposition = 0;
	m_stage = kStart;
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
	if (kSFoot == 0) {kSFoot = 0.87;}									// Old: 0.955
	SmartDashboard::PutNumber("AU6_kSFoot", kSFoot);

	double distancepos = feet * kSFoot;
	SmartDashboard::PutNumber("AU8_distancepos", distancepos);

	double distancetotarget = abs(distancepos) - (abs((leftposition - rightposition) / 2));
	//double k = 1.0;
	if (distancetotarget <= (0.5 * abs(distancepos)))
	{
		power = 0.15 * (power/abs(power));
	}

	if (distancetotarget <= 0)
	{
		m_driveangle->Stop();
		m_driveangle->Drive(0);
		m_drivetrain->Drive(0, 0);
		m_drivetrain->LeftTalon()->SetPosition(0);
		m_drivetrain->RightTalon()->SetPosition(0);
		Wait(0.25);
		m_driveangle->EnableAnglePID();
		return true;
	}
	m_driveangle->Drive(power, true);
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
		m_driveangle->EnableAnglePID();
		return true;
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

	switch (m_stage)
	{
	case kIdle:
		m_driveangle->Drive(0);
		break;

	case kStart:
		//m_driveangle->SetD(0.2);
		DriverStation::ReportError("start");
		m_drivetrain->LeftTalon()->SetPosition(0);
		m_drivetrain->RightTalon()->SetPosition(0);
		Wait(0.1);
		if (!m_drivetrain->getIsHighGear())
			m_drivetrain->Shift();
		m_stage = kStage1;
		break;

	case kStage1:
		DriverStation::ReportError("stage1");
		switch (autoselected)
		{
		case kAutoLeftGear:
		case kAutoRightGear:
			if (GoStraight(67.6/12.0, -1))
				m_stage = kStage2;
			break;

		case kAutoRedShoot:
		case kAutoBlueShoot:
			if (GoStraight(7.04, -1))
				m_stage = kStage2;
			break;

		case kAutoStraight:
			if (GoStraight(6.625, -1))
				m_stage = kDeploy;
			break;

		}
		break;

	case kStage2:
		DriverStation::ReportError("stage2");
		switch (autoselected)
		{
		case kAutoLeftGear:
			if (TurnDegree(-60))
				m_stage = kStage3;
			break;

		case kAutoRightGear:
			if (TurnDegree(60))
				m_stage = kStage3;
			break;

		case kAutoRedShoot:
			if (TurnDegree(90))
			{
				m_picker->Deploy();
				Wait(0.1);
				m_stage = kStage3;
			}
			break;

		case kAutoBlueShoot:
			if (TurnDegree(-90))
			{
				m_picker->Deploy();
				m_stage = kStage3;
			}
			break;

		case kAutoStraight:
			break;
		}
		break;

	case kStage3:
		DriverStation::ReportError("stage3");
		switch(autoselected)
		{
		case kAutoLeftGear:
		case kAutoRightGear:
			m_visiontarget->TargetGear();
			if (GoStraight(70.6/12.0, -0.6))
				m_stage = kDeploy;
			break;

		case kAutoRedShoot:
		case kAutoBlueShoot:
			if (GoStraight(-3.375, 1))
				m_stage = kDeploy;
			break;

		case kAutoStraight:
			break;
		}
		break;

	case kDeploy:
		DriverStation::ReportError("deploy");
		switch (autoselected)
		{
		case kAutoLeftGear:
		case kAutoRightGear:
		case kAutoStraight:
			m_picker->Deploy();
			break;

		case kAutoRedShoot:
		case kAutoBlueShoot:
			break;
		}
		m_stage = kIdle;
		break;
	}
}
