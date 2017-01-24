// Autonomous.cpp


#include <Autonomous.h>


Autonomous::Autonomous(DriverStation *driverstation, Drivetrain *drivetrain, OperatorInputs *operatorinputs)
{
	m_driverstation = driverstation;
	m_drivetrain = drivetrain;
	m_inputs = operatorinputs;
	m_stage = kIdle;
}


Autonomous::~Autonomous()
{

}


void Autonomous::Init()
{
	m_timer.Stop();
	m_timer.Reset();
	m_stage = kIdle;
}

/*
void Autonomous::Loop()
{
	if (m_stage == kIdle)
		if (!m_driverstation->IsAutonomous())
			return;

	switch (m_stage)
	{
	case kIdle:
		m_stage = kStage1;
		break;
	case kStage1:
		m_timer.Start();
		m_drivetrain->Drive(0, 0.25);
		if (m_timer.HasPeriodPassed(1.0))
		{
			m_drivetrain->Drive(0, 0);
			m_timer.Stop();
			m_timer.Reset();
			m_stage = kStage2;
		}
		break;
	case kStage2:
		m_timer.Start();
		m_drivetrain->Drive(0.25, 0);
		if (m_timer.HasPeriodPassed(0.5))
		{
			m_drivetrain->Drive(0, 0);
			m_timer.Stop();
			m_timer.Reset();
			m_stage = kStage1;
		}
		break;
	case kStage3:
		m_timer.Start();
		m_drivetrain->Drive(0.5, 0.25);
		if (m_timer.HasPeriodPassed(1.0))
		{
			m_drivetrain->Drive(0, 0);
			m_timer.Stop();
			m_timer.Reset();
			m_stage = kStage4;
		}
		break;
	case kStage4:
		break;
	case kStage5:
		break;
	}
}
*/


void Autonomous::Loop()
{
	double kP = SmartDashboard::GetNumber("DB/Slider 0", 0);
	if (kP == 0) {kP = 0.2;}

	double kI = SmartDashboard::GetNumber("DB/Slider 1", 0);
	if (kI == 0) {kI = 0.001;}

	double leftposition = m_drivetrain->LeftTalon()->GetPosition();
	double rightposition = m_drivetrain->RightTalon()->GetPosition();
	double leftvolts = m_drivetrain->LeftTalon()->GetOutputVoltage();
	double rightvolts = m_drivetrain->RightTalon()->GetOutputVoltage();

	SmartDashboard::PutNumber("VT1_leftpos", leftposition);
	SmartDashboard::PutNumber("VT2_rightpos", rightposition);
	SmartDashboard::PutNumber("VT3_kP", kP);
	SmartDashboard::PutNumber("VT4_kI", kI);
	SmartDashboard::PutNumber("VT8_leftvolts", leftvolts);
	SmartDashboard::PutNumber("VT9_rightvolts", rightvolts);

	switch (m_stage)
	{
	case kIdle:
		m_drivetrain->LeftTalon()->SetPosition(0);
		m_drivetrain->RightTalon()->SetPosition(0);
		m_stage = kStage1;
		break;
	case kStage1:
		DriverStation::ReportError("stage1");
		m_drivetrain->Drive(0, -0.25);
		m_stage = kStage2;
		break;
	case kStage2:
		DriverStation::ReportError("stage2");
		if ((leftposition > 2.0) || (-rightposition > 2.0))
		{
			m_drivetrain->Drive(0, 0);
			m_stage = kStage3;
		}
		break;
	case kStage3:

		DriverStation::ReportError("stage3");
		m_drivetrain->LeftTalon()->SetPosition(0);
		m_drivetrain->RightTalon()->SetPosition(0);
		m_drivetrain->Drive(-0.25, 0);
		m_stage = kStage4;
		break;
	case kStage4:
		DriverStation::ReportError("stage4");
		if ((leftposition > 2.0) || (-rightposition > 2.0))
		{
			m_drivetrain->Drive(0, 0);
			m_stage = kStage5;
		}
		break;
	case kStage5:
		break;
	}
}


void Autonomous::Stop()
{
	m_timer.Stop();
	m_timer.Reset();
	m_stage = kIdle;
}


void Autonomous::EnablePID(double kP, double kI, double kPosLeft, double kPosRight)
{
	m_drivetrain->LeftTalon()->SelectProfileSlot(0);
	m_drivetrain->LeftTalon()->ConfigNominalOutputVoltage(+0.0f, -0.0f);
	m_drivetrain->LeftTalon()->ConfigPeakOutputVoltage(+6.0f, -6.0f);
	m_drivetrain->LeftTalon()->SetAllowableClosedLoopErr(0.0);

	m_drivetrain->RightTalon()->SelectProfileSlot(0);
	m_drivetrain->RightTalon()->ConfigNominalOutputVoltage(+0.0f, -0.0f);
	m_drivetrain->RightTalon()->ConfigPeakOutputVoltage(+6.0f, -6.0f);
	m_drivetrain->RightTalon()->SetAllowableClosedLoopErr(0.0);

	m_drivetrain->LeftTalon()->SetP(kP);
	m_drivetrain->LeftTalon()->SetI(kI);
	m_drivetrain->LeftTalon()->SetD(0);
	m_drivetrain->LeftTalon()->SetF(0);

	m_drivetrain->RightTalon()->SetP(kP);
	m_drivetrain->RightTalon()->SetI(kI);
	m_drivetrain->RightTalon()->SetD(0);
	m_drivetrain->RightTalon()->SetF(0);

	m_drivetrain->LeftTalon()->SetPosition(0);
	m_drivetrain->RightTalon()->SetPosition(0);

	Wait(0.1);

	m_drivetrain->LeftTalon()->SetControlMode(CANTalon::kPosition);
	m_drivetrain->RightTalon()->SetControlMode(CANTalon::kPosition);
	m_drivetrain->LeftTalon()->Set(kPosLeft);
	m_drivetrain->RightTalon()->Set(kPosRight);
}


void Autonomous::DisablePID()
{
	m_drivetrain->LeftTalon()->ConfigPeakOutputVoltage(+12.0f, -12.0f);
	m_drivetrain->LeftTalon()->SetControlMode(CANTalon::kPercentVbus);
	m_drivetrain->LeftTalon()->Set(0);

	m_drivetrain->RightTalon()->ConfigPeakOutputVoltage(+12.0f, -12.0f);
	m_drivetrain->RightTalon()->SetControlMode(CANTalon::kPercentVbus);
	m_drivetrain->RightTalon()->Set(0);
}
