/**
 *  Picker.cpp
 *  Date:
 *  Last Edited By:
 */

#include <Picker.h>
#include <const.h>
#include <driverstation.h>
#include <XboxController.h>
#include <Talon.h>


using namespace std;


Picker::Picker(OperatorInputs *operatorinputs)
{
	m_inputs = operatorinputs;
	//m_motor = new Spark(PWM_PICKER_MOTOR);
	m_motor = new CANTalon(CAN_PICKER_MOTOR);
	m_solenoid = new Solenoid(PWM_PICKER_SOLENOID);
	m_running = false;
	m_ramping = 0;
}


Picker::~Picker()
{
	delete m_motor;
	delete m_solenoid;
}


void Picker::Init()
{
	m_motor->SetControlMode(CANSpeedController::ControlMode::kPercentVbus);
	m_motor->Set(0);
	m_running = false;
	m_solenoid->Set(false);
}


void Picker::Loop()
{
	bool buttonpressed = m_inputs->xBoxStartButton();
	bool deploy = m_inputs->xBoxBackButton();

	//m_solenoid->Set(false);
	if (buttonpressed == true)
		m_running = !m_running;
	if (buttonpressed == false)
		m_motor->Set(m_ramping*1.0);

	if (deploy)
		m_solenoid->Set(true);

	if (m_running)
	{
		if(m_ramping < 1)
			m_ramping += 0.1;
		else
			m_ramping = 1;
		m_motor->Set(m_ramping*-1.0);
	}
	else
	{
		if(m_ramping > 0)
			m_ramping -= 0.25;
		else
			m_ramping = 0;
		m_motor->Set(m_ramping);
	}

}



void Picker::Stop()
{
	m_motor->Set(0);
	m_running = false;
	m_solenoid->Set(false);
	m_ramping = 0;
}


void Picker::Deploy()
{
	m_solenoid->Set(true);
}
