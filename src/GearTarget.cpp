/**
 *  GearTarget.cpp
 *  Date:
 *  Last Edited By:
 */

#include "GearTarget.h"

GearTarget::GearTarget(std::shared_ptr<NetworkTable> newTable, DriveAngle * newAngle, OperatorInputs *oi) {
	// TODO Auto-generated constructor stub
	m_xDegree = 0;
	m_nettable = newTable;
	m_driveangle = newAngle;
	m_prevCounter = 0;
	m_counter = 0;
	m_isActive = false;
	m_stage = stopped;
	m_inputs = oi;
}

void GearTarget::Init()
{
//	m_isActive = true;
//	m_driveangle->EnableAnglePID();
	m_prevCounter = 0;
	//m_stage = stopped;
}

void GearTarget::Loop()
{
	SmartDashboard::PutNumber("GT_00_IsEnabled", m_isActive);
	m_nettable->PutNumber("PIDEnabled", m_driveangle->IsEnabled());
	//if(m_isActive && !m_driveangle->IsEnabled())
				//m_driveangle->EnableAnglePID();

	if(m_inputs->xBoxRightBumper())
	{
		m_isActive = !m_isActive;
		if(m_isActive)
		{
			m_driveangle->EnableAnglePID();
			m_driveangle->SetToCurrentAngle();
		}
		else
		{
			m_driveangle->Stop();
		}
	}
	if (!m_driveangle->IsEnabled()) {
		m_driveangle->RunNormalDrive();
	}

	if(m_isActive)
	{
		m_driveangle->Drive(m_inputs->xBoxLeftY(), true);
		TargetGear();
	}
//	switch (stage)
//	{
//		case stopped:
//			break;
//
//		case read:
//			if(counter < 3)
//			{
//				prevCounter = netTable->GetNumber("counter", 0);
//				counter++;
//			}
//			else if(netTable->GetNumber("counter", 0) > prevCounter)
//			{
//				xDegree = netTable->GetNumber("xPos", 0) / 10;
//				container->EnableAnglePID();
//				container->SetRelativeAngle(xDegree);
//				stage = targeting;
//			}
//			else
//			{
//				isDone = true;
//				stage = stopped;
//			}
//			break;
////		case targeting:
////			if(container->IsOnTarget())
////			{
////				isDone = true;
////				stage = stopped;
////			}
//
//
//	}
}

void GearTarget::TargetGear() {
	if(/*container->IsOnTarget() &&*/ m_nettable->GetNumber("counter",0) != m_counter)
	{
		m_counter = m_nettable->GetNumber("counter",0);
		m_xDegree = (m_nettable->GetNumber("xPos", 0) / 20); // how fast it turns (making it larger is slower)
		int areaDegree = (m_nettable->GetNumber("areaDifference", 0) * 50); // how sensitive the arcing is
		areaDegree = (abs(areaDegree)>6) ? (areaDegree>0?6:-6) : areaDegree; // maximum arc
		areaDegree = (m_nettable->GetNumber("xSpread",0)>180)?0:areaDegree; // distance to stop arcing
		m_driveangle->SetVisionAngle((m_xDegree+areaDegree));
	}
}


void GearTarget::Stop()
{
	m_isActive = 0;
	m_driveangle->Stop();
}

GearTarget::~GearTarget() {
	// TODO Auto-generated destructor stub
}

