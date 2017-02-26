/**
 *  Climber.cpp
 *  Date:
 *  Last Edited By:
 */


#include <Climber.h>
#include <Const.h>


Climber::Climber(OperatorInputs *operatorinputs, Shooter *shooter) : m_PDP(CAN_PDP)
{
	m_inputs = operatorinputs;
	m_timer.Reset();
	m_timer.Stop();
	//m_climbmotor = new Spark(PWM_CLIMBER_MOTOR);
	m_climbmotor = new CANTalon(CAN_CLIMBER_MOTOR);
	m_shooter = shooter;
}


Climber::~Climber()
{
	delete m_climbmotor;
}


void Climber::Init()
{
	m_climbmotor->SetControlMode(CANSpeedController::ControlMode::kVoltage);
	m_timer.Reset();
	m_timer.Stop();
	m_climbmotor->Set(0);
}


void Climber::Loop()
{
	static bool timerStarted = false;
	bool climbupbutton = m_inputs->xBoxYButton(OperatorInputs::ToggleChoice::kHold);
	bool climbdownbutton = m_inputs->xBoxXButton(OperatorInputs::ToggleChoice::kHold);
	//double current = m_PDP->GetCurrent(PDP_CLIMBER_MOTOR);
	//double current = m_climbmotor->GetOutputCurrent();

	//SmartDashboard::PutNumber("Climber", current);

	if (climbupbutton)
	{
		m_climbmotor->Set(9);
		if(!timerStarted)
		{
			m_timer.Start();
			timerStarted = true;
		}
		if(m_timer.HasPeriodPassed(1.0))
			m_shooter->Stop();
	}
	else
	if (climbdownbutton)
	{
		m_climbmotor->Set(-9);
	}
	else
	{
		m_climbmotor->Set(0);
		if(m_timer.HasPeriodPassed(1.0))
		{
			timerStarted = false;
			m_timer.Reset();
			m_timer.Stop();
		}
	}

	//if (current > 17.0)
		//m_climbmotor->Set(0);
}


void Climber::Stop()
{
	m_climbmotor->Set(0);
}
