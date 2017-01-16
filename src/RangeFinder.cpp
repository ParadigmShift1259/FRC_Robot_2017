// rangefinder.cpp


#include "RangeFinder.h"
#include "smartdashboard/smartdashboard.h"
#include "const.h"


RangeFinder::RangeFinder()
{
	m_ultrasonic = new Ultrasonic(DIO_RANGEFINDER_ECHO_OUT, DIO_RANGEFINDER_TRIGGER_IN);
}


RangeFinder::~RangeFinder()
{
	delete m_ultrasonic;
}


void RangeFinder::Init()
{
	m_ultrasonic->SetAutomaticMode(true);
}


void RangeFinder::Loop()
{
	double range = m_ultrasonic->GetRangeInches();

	SmartDashboard::PutNumber("RangerFinder", range);
}
