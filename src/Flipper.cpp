/**
 *  Flipper.cpp
 *  Date: 2/16/17
 *  Last Edited By: Ertl
 */

#include <Flipper.h>
#include <Const.h>


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
}


void Flipper::Loop()
{
	if (m_driverstation->IsTest())
	{
		 bool flipupbutton = m_inputs->xBoxBButton();
		 bool flipdownbutton = m_inputs->xBoxAButton();

		 if (flipupbutton)
		 {
			 m_solenoid->Set(true);
		 }
		 else if (flipdownbutton)
		 {
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

