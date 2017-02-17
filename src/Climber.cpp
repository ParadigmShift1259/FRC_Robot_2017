/* Climber.cpp
 * Editor: Agastya
 * */



#include <Climber.h>
#include <Const.h>


Climber::Climber(OperatorInputs *operatorinputs)
{
	m_inputs = operatorinputs;
	m_spark = new Spark(PWM_CLIMBER_MOTOR);
}


Climber::~Climber()
{
	delete m_spark;
}


void Climber::Init()
{
	m_spark->Set(0);
}


void Climber::Loop()
{
	bool climbupbutton = m_inputs->xBoxRightY() < -0.5;
	bool climbdownbutton = m_inputs->xBoxRightY() > 0.5;

	if (climbupbutton)
	{
		m_spark->Set(0.5);
	}
	else
	if (climbdownbutton)
	{
		m_spark->Set(-0.5);
	}
	else
	{
		m_spark->Set(0);
	}
}


void Climber::Stop()
{
	m_spark->Set(0);
}
