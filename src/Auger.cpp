// Auger.h


#include "Auger.h"


Auger::Auger()
{
	m_augermotor = new Spark(AUGER_CHANNEL);
	m_augertimer = 0;
	m_augeron = false;
	m_timetillchange = 0;
}


Auger::~Auger()
{

}


void Auger::RunAuger()
{
	if(m_augermotor->Get()<AUGER_POWER)
	{
		m_augermotor->Set(m_augermotor->Get()+AUGER_RAMP);
	}
	else
	{
		m_augermotor->Set(AUGER_POWER);
	}

}


void Auger::StopAuger()
{
	if(m_augermotor->Get()>0)
	{
		m_augermotor->Set(m_augermotor->Get()-AUGER_RAMP);
	}
	else
	{
		m_augermotor->Set(0);
	}
}


void Auger::InitPulse()
{
	m_augertimer->Start();
	m_augertimer->Reset();
	m_timetillchange = AUGER_ON_TIME;
	m_augeron = true;
}


void Auger::PulseAuger()
{
	if(m_augertimer->HasPeriodPassed(m_timetillchange) && m_augeron == true)
	{
		m_augeron = false;
		m_timetillchange = AUGER_OFF_TIME;
		m_augertimer->Reset();
	}
	else if(m_augertimer->HasPeriodPassed(m_timetillchange) && m_augeron == false)
	{
		m_augeron = true;
		m_timetillchange = AUGER_ON_TIME;
		m_augertimer->Reset();
	}

	if (m_augeron)
	{
		RunAuger();
	}
	else
	{
		StopAuger();
	}
}


