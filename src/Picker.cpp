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
	m_solenoid->Set(false);
	m_running = false;
	m_ramping = 0;
	m_motor->SetControlMode(CANSpeedController::ControlMode::kPercentVbus);
	m_motor->Set(0);
	motorOnOff = false;
}


Picker::~Picker()
{
	delete m_motor;
	delete m_solenoid;
}


void Picker::Init()
{
	//m_motor->SetControlMode(CANSpeedController::ControlMode::kPercentVbus);
	m_motor->Set(0);
	m_running = false;
	//Note, do NOT set the solenoid to false here. That will cause an issue where the picker rises up mid match
}


void Picker::Loop()
{
	bool changePickerDirection = m_inputs->xBoxXButton(OperatorInputs::ToggleChoice::kToggle, 1);
	bool deploy = m_inputs->xBoxBackButton(OperatorInputs::ToggleChoice::kToggle, 1);
	SmartDashboard::PutNumber("P1_PickerState", m_running);

	if (m_inputs->xBoxLeftBumper(OperatorInputs::ToggleChoice::kToggle,1))
	{
		if(!motorOnOff)
		{
			m_motor->Set(0);
			motorOnOff = true;
		}
		else
		{
			m_motor->Set(m_ramping*-0.7);
			motorOnOff = false;
		}
	}
	//m_solenoid->Set(false);
	/*if (changePickerDirection && m_solenoid->Get())
		m_running = !m_running;
	else
	if (!m_solenoid->Get())
		m_running = false;*/

	if (deploy)
		m_solenoid->Set(true);
	if(changePickerDirection)
		Stop();

	if (m_running)
	{
		if(m_ramping < 1)
			m_ramping += 0.1;
		else
			m_ramping = 1;
		m_motor->Set(m_ramping*-0.7);
	}
	else
	{
		if(m_ramping > -1)
			m_ramping -= 0.25;
		else
			m_ramping = -1;
		if (!m_solenoid->Get())
			m_ramping = 0;
		m_motor->Set(m_ramping*-0.7);
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
