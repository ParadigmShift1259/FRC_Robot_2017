//picker.cpp

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
}


Picker::~Picker()
{
	delete m_motor;
}


void Picker::Init()
{
	m_motor->Set(0);
	m_running = false;
}


void Picker::Loop()
{
	bool buttonpressed = m_inputs->xBoxLeftBumper();

	if (buttonpressed)
		m_running = !m_running;

	if (m_running)
	{
		m_motor->Set(1.0);
	}
	else
	{
		m_motor->Set(0.0);
	}
}


void Picker::Stop()
{
	m_motor->Set(0);
	m_running = false;
}
