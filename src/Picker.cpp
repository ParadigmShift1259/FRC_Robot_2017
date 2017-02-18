/*picker.cpp
 *Editor: Agastya
 * */


#include <Picker.h>
#include <const.h>
#include <driverstation.h>
#include "smartdashboard/smartdashboard.h"
#include <XboxController.h>
#include <Talon.h>


using namespace std;


Picker::Picker(OperatorInputs *operatorinputs)
{
	m_inputs = operatorinputs;
	m_motor = new Spark(PWM_PICKER_MOTOR);
	m_solenoid = new Solenoid(PWM_PICKER_SOLENOID);
	m_running = false;
	m_stage = kDeploy;
	m_ramping = 0;
}


Picker::~Picker()
{
	delete m_motor;
	delete m_solenoid;
}


void Picker::Init()
{
	m_motor->Set(0);
	m_running = false;
	m_solenoid->Set(false);
	m_stage = kDeploy;
}


void Picker::Loop()
{
	bool buttonpressed = m_inputs->xBoxStartButton();
	bool deploy = m_inputs->xBoxBackButton();

	switch (m_stage)
	{
	case kDeploy:
		if (buttonpressed)
		{
			m_stage = kRunning;
			break;
		}
		if (deploy)
		{
			m_stage = kDeploying;
		}

		m_stage = kDeploying;
		break;
	case kDeploying:
		if (buttonpressed)
		{
			m_stage = kRunning;
			break;
		}
		m_solenoid->Set(true);
		break;
	case kRunning:
		m_solenoid->Set(false);
		if (buttonpressed)
			m_running = !m_running;

		if (m_running)
		{
			if(m_ramping < 1)
			{
				m_ramping += 0.1;
			}
			m_motor->Set(m_ramping);
		}
		else
		{
			if(m_ramping > 1)
			{
				m_ramping -= 0.25;
			}
			m_motor->Set(m_ramping);
		}

	}
}


void Picker::Stop()
{
	m_motor->Set(0);
	m_running = false;
	m_solenoid->Set(false);
	m_ramping = 0;
	m_stage = kDeploy;
}
