/**
 *  Picker.cpp
 *  Date:
 *  Last Edited By:
 */

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
	m_running = false;
	m_stage = kDeploy;
	m_ramping = 0;
}


Picker::~Picker()
{
	delete m_motor;
}


void Picker::Init()
{
	m_motor->Set(0);
	m_running = false;
	m_stage = kDeploy;
}


void Picker::Loop()
{
	bool buttonpressed = m_inputs->xBoxLeftBumper();
	bool deploy = m_inputs->xBoxXButton();

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
		}

		m_stage = kDeploying;
		break;
	case kDeploying:
		if (buttonpressed)
		{
			m_stage = kRunning;
			break;
		}
		break;
	case kRunning:
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
	m_ramping = 0;
	m_stage = kDeploy;
}
