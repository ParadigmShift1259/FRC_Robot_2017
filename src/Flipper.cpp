/**
 *  Flipper.cpp
 *  Date: 2/16/17
 *  Last Edited By: Ertl
 */

#include <Flipper.h>
#include <Const.h>
#include <SmartDashboard/SmartDashboard.h>

Flipper::Flipper(DriverStation *driverstation, OperatorInputs *operatorinputs)
{
	m_driverstation = driverstation;
	m_inputs = operatorinputs;
	m_solenoid = new Solenoid(PWM_FLIPPER_SOLENOID);
	m_solenoid->Set(false);
	m_flippedup = false;
}


Flipper::~Flipper()
{
	delete m_solenoid;
}


void Flipper::Init()
{
	m_solenoid->Set(false);
	m_flippedup = false;
	m_timer.Start();
}


void Flipper::Loop()
{
	SmartDashboard::PutBoolean("FL01_IsTest",m_driverstation->IsTest());
	SmartDashboard::PutBoolean("FL02_FlippedUp",m_flippedup);
	SmartDashboard::PutBoolean("FL03_Solenoid",m_solenoid->Get());
	if (m_driverstation->IsTest())
	{
		 bool flipupbutton = m_inputs->xBoxAButton();
		 bool flipdownbutton = m_inputs->xBoxBButton();

		 if (flipupbutton && !m_flippedup)
		 {
			 m_flippedup = true;
			 m_solenoid->Set(true);
		 }
		 if (flipdownbutton && m_flippedup)
		 {
			 m_flippedup = false;
			 m_solenoid->Set(false);
		 }
	}
	else
	{
		bool flipbutton = m_inputs->xBoxAButton();

		if (flipbutton && !m_flippedup)
		{
			m_solenoid->Set(true);
			m_flippedup = true;
			m_timer.Reset();
		}
		if (m_flippedup && m_timer.HasPeriodPassed(1.0))
		{
			m_solenoid->Set(false);
			m_flippedup = false;
		}
	}
}


void Flipper::Stop()
{
	m_solenoid->Set(false);
	m_timer.Stop();
}

