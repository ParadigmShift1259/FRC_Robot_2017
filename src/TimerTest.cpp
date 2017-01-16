// timertest.cpp


#include <TimerTest.h>
#include "smartdashboard/smartdashboard.h"
#include <driverstation.h>
#include <string>


using namespace std;


TimerTest::TimerTest()
{
	m_timer = new Timer();
}


TimerTest::~TimerTest()
{
	delete m_timer;
}


void TimerTest::Init()
{
	m_timer->Reset();
	m_timer->Start();
}


void TimerTest::Loop()
{
	bool timepassed = m_timer->HasPeriodPassed(.05);
	double currenttime = m_timer->GetFPGATimestamp();

	if (timepassed)
	{
		DriverStation::ReportError("Time has passed" + to_string(currenttime));
	}
	else
	{

	}
}


void TimerTest::Stop()
{
	m_timer->Stop();
}
