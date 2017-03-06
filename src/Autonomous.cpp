/**
 *  Autonomous.cpp
 *  Date: 2/18/17
 *  Last Edited By: Eric
 *  Note:
 */


#include <Autonomous.h>


Autonomous::Autonomous(DriverStation *driverstation, Drivetrain *drivetrain, DriveAngle *driveangle, VisionTarget *visiontarget, Picker *picker, OperatorInputs *operatorinputs, Shooter *shooter)
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
	m_shooter = shooter;
	m_timer = new Timer();
}


Autonomous::~Autonomous()
{
	delete m_timer;
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
	if (kSFoot == 0) 
		kSFoot = 0.87;									// Old: 0.955
	SmartDashboard::PutNumber("AU6_kSFoot", kSFoot);

	double distancepos = feet * kSFoot;
	SmartDashboard::PutNumber("AU8_distancepos", distancepos);

	double distancetotarget = abs(distancepos) - (abs((leftposition - rightposition) / 2));
	//double k = 1.0;
	if (distancetotarget <= (0.5 * abs(distancepos)))
		power = 0.15 * (power/abs(power));

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
	bool next = false; //reset to false each loop is intentional, do not make static

	switch (m_stage)
	{
	case kIdle:
		DriverStation::ReportError("idle");
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
		m_stage = kDrive1;
		break;

	case kDrive1:
		DriverStation::ReportError("Drive1");
		switch (autoselected)
		{
		case kAutoBoilerGear:
		case kAutoBoilerShootGear:
		case kAutoFeedGear:
		case kAutoFeedShootGear:
		case kAutoOldLeftGear:
		case kAutoOldRightGear:
			next = GoStraight(56.0/12.0, -1);
			break;

		case kAutoShootOnly:
		case kAutoOldRedShoot:
		case kAutoOldBlueShoot:
			next = GoStraight(84.5/12.0, -1)
			break;

		case kAutoStraightGear:
		case kAutoStraightShootGear:
			next = GoStraight(39.75/12.0, -1)
			break;

		}
		if(next)
			m_stage = kTurn1;
		break;

	case kTurn1:
		DriverStation::ReportError("Turn1");
		switch (autoselected)
		{
		case kAutoBoilerGear:
		case kAutoBoilerShootGear:
			switch (m_driverstation->GetAlliance())
			{
			case DriverStation::Alliance::kRed:
				next = TurnDegree(60);
				break;
			
			case DriverStation::Alliance::kBlue:
				next = TurnDegree(-60);
				break;

			default:
				next = true;
				break;
			}
		break;
			
		case kAutoFeedGear:
		case kAutoFeedShootGear:
			switch (m_driverstation->GetAlliance())
			{
			case DriverStation::Alliance::kRed:
				next = TurnDegree(-60);
				break;
			
			case DriverStation::Alliance::kBlue:
				next = TurnDegree(60);
				break;

			default:
				next = true;
				break;
			}
		break;
		
		case kAutoShootOnly:
			switch (m_driverstation->GetAlliance())
			{
			case DriverStation::Alliance::kRed:
				next = TurnDegree(90);
				break;
			
			case DriverStation::Alliance::kBlue:
				next = TurnDegree(-90);
				break;

			default:
				next = true;
				break;
			}
		break;
			
		case kAutoStraightGear:
		case kAutoStraightShootGear:
			next = true;
			break;

		case kAutoOldLeftGear:
			next = TurnDegree(-60);
			break;

		case kAutoOldRightGear:
			next = TurnDegree(60);
			break;

		case kAutoOldBlueShoot:
			next = TurnDegree(-90);
			break;

		case kAutoOldRedShoot:
			next = TurnDegree(90);
			break;

		}
		if(next)
			m_stage = kDrive2;
		break;

	case kDrive2:
		DriverStation::ReportError("Drive2");
		switch(autoselected)
		{
		case kAutoBoilerShootGear:
			m_visiontarget->TargetGear();
			if (GoStraight(70.6/12.0, -0.6))
				m_stage = kPrepShoot;
			break;
		
		case kAutoFeedShootGear:
			m_visiontarget->TargetGear();
			if (GoStraight(70.6/12.0, -0.6))
			{
				m_timer->Reset();
				m_timer->Start();
				m_stage = kPrepShoot;
			}
			break;
		
		case kAutoBoilerGear:
		case kAutoFeedGear:
		case kAutoOldLeftGear:
		case kAutoOldRightGear:
			m_visiontarget->TargetGear();
			if (GoStraight(70.6/12.0, -0.6))
				m_stage = kDeploy;
			break;

		case kAutoShootOnly:
		case kAutoOldRedShoot:
		case kAutoOldBlueShoot:
			if (GoStraight(34/12.0, 0.6))
			{
				m_timer->Reset();
				m_timer->Start();
				m_stage = kPrepShoot;
			}
			break;

		case kAutoStraightGear:
			if (GoStraight(39.75/12.0, -0.6))
				m_stage = kDeploy;
			break;

		case kAutoStraightShootGear:
			if (GoStraight(39.75/12.0, -0.6))
				m_stage = kPrepShoot;
			break;
		}
		break;

	case kPrepShoot:
		DriverStation::ReportError("PrepShoot");
		switch(autoselected)
		{
			case kAutoBoilerShootGear:
				m_shooter->SetShootRPM(860);
				next = true;
				break;

			case kAutoStraightShootGear:
				m_shooter->SetShootRPM(1030);
				next = true;
				break;

			case kAutoFeedShootGear:
				if (m_timer->HasPeriodPassed(3.0))
				{
					if (GoStraight(24.0/12.0, 1.0))
					{
						m_shooter->SetShootRPM(1200);
						next = true;
					}
				}
				break;

			case kAutoShootOnly:
			case kAutoOldRedShoot:
			case kAutoOldBlueShoot:
				if (m_timer->HasPeriodPassed(1.0))
				{
					if (GoStraight(10.0/12.0, -1.0))
					{
						m_shooter->SetShootRPM(740);
						next = true;
					}
				}
				break;
			
			case kAutoBoilerGear:
			case kAutoFeedGear:
			case kAutoOldRightGear:
			case kAutoOldLeftGear:
			case kAutoStraightGear:
				next = false;
				m_stage = kDeploy;
				break;

		}
		if (next) {
			m_shooter->StartShooter();
			m_picker->Deploy();
			m_timer->Reset();
			m_timer->Start();
			m_stage = kTurnShoot;
		}
		break;

	case kTurnShoot:
		DriverStation::ReportError("TurnShoot");
		switch(autoselected)
		{
		case kAutoBoilerShootGear:
			if(m_timer->HasPeriodPassed(3.0)
			{
				switch (m_driverstation->GetAlliance())
				{
				case DriverStation::Alliance::kRed:
					next = TurnDegree(-9.79);
					break;

				case DriverStation::Alliance::kBlue:
					next = TurnDegree(13.74);
					break;
			
				default:
					m_stage = kDeploy;
					break;
				}
			}
			break;

		case kAutoStraightShootGear:
			if(m_timer->HasPeriodPassed(3.0)
			{
				switch (m_driverstation->GetAlliance())
				{
				case DriverStation::Alliance::kRed:
					next = TurnDegree(69.11);
					break;

				case DriverStation::Alliance::kBlue:
					next = TurnDegree(-66.39);
					break;
			
				default:
					m_stage = kDeploy;
					break;
				}
			}
			break;

		case kAutoFeedShootGear:
			switch (m_driverstation->GetAlliance())
			{
			case DriverStation::Alliance::kRed:
				next = TurnDegree(140);
				break;

			case DriverStation::Alliance::kBlue:
				next = TurnDegree(-140);
				break;
		
			default:
				m_stage = kDeploy;
				break;
			}
			break;

		case kAutoShootOnly:
			switch (m_driverstation->GetAlliance())
			{
			case DriverStation::Alliance::kRed:
				next = TurnDegree(-86.5);
				break;

			case DriverStation::Alliance::kBlue:
				next = TurnDegree(65);
				break;
		
			default:
				m_stage = kDeploy;
				break;
			}
			break;

		case kAutoOldRedShoot:
			next = TurnDegree(-86.5);
			break;

		case kAutoOldBlueShoot:
			next = TurnDegree(65);
			break;

		case kAutoOldRightGear:
		case kAutoOldLeftGear:
		case kAutoStraightGear:
			m_stage = kDeploy;
			break;
		}
		if (next)
		{
			m_shooter->StartAuger();
			m_timer->Reset();
			m_timer->Start();
			m_stage = kShoot;
		}
		break;

	case kShoot:
		DriverStation::ReportError("shooting");
		switch(autoselected)
		{
		case kAutoBoilerShootGear:
		case kAutoFeedShootGear:
		case kAutoStraightShootGear:
		case kAutoShootOnly:
		case kAutoOldRedShoot:
		case kAutoOldBlueShoot:
			m_visiontarget->TargetShooter();
			if(m_timer->HasPeriodPassed(1.0)
			{
				m_stage = kIdle;
			}
			break;

		case kAutoOldRightGear:
		case kAutoOldLeftGear:
		case kAutoStraightGear:
			m_stage = kDeploy;
			break;
		}
		break;

	case kDeploy:
		DriverStation::ReportError("deploy");
		m_picker->Deploy();
		m_stage = kIdle;
		break;
	}
}