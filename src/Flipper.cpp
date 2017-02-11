// Flipper.cpp


#include <Flipper.h>
#include <Const.h>


Flipper::Flipper(OperatorInputs *operatorinputs)
{
	m_inputs = operatorinputs;
	m_solenoid = new Solenoid(PWM_FLIPPER_SOLENOID);
}


Flipper::~Flipper()
{
	delete m_solenoid;
}


void Flipper::Init()
{
	m_solenoid->Set(false);
}


void Flipper::Loop()
{
	bool flipupbutton = m_inputs->xBoxBButton();
	bool flipdownbutton = m_inputs->xBoxAButton();

	if (flipupbutton)
	{
		m_solenoid->Set(true);
	}
	else
	if (flipdownbutton)
	{
		m_solenoid->Set(false);
	}
}


void Flipper::Stop()
{
	m_solenoid->Set(false);
}
