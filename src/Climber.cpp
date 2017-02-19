/**
 *  Climber.cpp
 *  Date:
 *  Last Edited By:
 */


#include <Climber.h>
#include <Const.h>


Climber::Climber(OperatorInputs *operatorinputs) : m_PDP(CAN_PDP)
{
	m_inputs = operatorinputs;
	//m_climbmotor = new Spark(PWM_CLIMBER_MOTOR);
	m_climbmotor = new CANTalon(CAN_CLIMBER_MOTOR);
}


Climber::~Climber()
{
	delete m_climbmotor;
}


void Climber::Init()
{
	m_climbmotor->SetControlMode(CANSpeedController::ControlMode::kVoltage);
	m_climbmotor->Set(0);
}


void Climber::Loop()
{
	bool climbupbutton = m_inputs->xBoxYButton(OperatorInputs::ToggleChoice::kHold);
	bool climbdownbutton = false;//m_inputs->xBoxXButton();
	//double current = m_PDP->GetCurrent(PDP_CLIMBER_MOTOR);
	double current = m_climbmotor->GetOutputCurrent();

	SmartDashboard::PutNumber("Climber", current);

	if (climbupbutton)
	{
		m_climbmotor->Set(9);
	}
	else
	if (climbdownbutton)
	{
		m_climbmotor->Set(-9);
	}
	else
	{
		m_climbmotor->Set(0);
	}

	//if (current > 0.5)
		//m_climbmotor->Set(0);
}


void Climber::Stop()
{
	m_climbmotor->Set(0);
}
