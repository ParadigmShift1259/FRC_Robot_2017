/**
 *  VisionTarget.cpp
 *  Date:
 *  Last Edited By:
 */

#include "VisionTarget.h"

VisionTarget::VisionTarget(std::shared_ptr<NetworkTable> newTable, DriveAngle * newAngle, OperatorInputs *oi) {
	// TODO Auto-generated constructor stub
	m_nettable = newTable;
	m_driveangle = newAngle;
	m_shootercounter = 0;
	m_gearcounter = 0;
	m_targetinggear = false;
	m_targetingshooter = false;
	m_inputs = oi;
}

void VisionTarget::Init()
{
//	m_isActive = true;
//	m_driveangle->EnableAnglePID();
	//m_stage = stopped;
}

void VisionTarget::Loop()
{
	SmartDashboard::PutBoolean("VT_00_GearImageFound",m_nettable->GetNumber("gear/counter",0) != m_gearcounter);
	SmartDashboard::PutBoolean("VT_00_ShooterImageFound",m_nettable->GetNumber("shooter/counter",0) != m_shootercounter);
	SmartDashboard::PutBoolean("VT_01_TargetingGear", m_targetinggear);
	SmartDashboard::PutBoolean("VT_01_TargetingShooter",m_targetingshooter);
	SmartDashboard::PutNumber("VT_02_TargetingGear", m_targetinggear);
	SmartDashboard::PutNumber("VT_02_GearXSpread",m_nettable->GetNumber("gear/xSpread",0));
	SmartDashboard::PutNumber("VT_02_ShooterXSpread",m_nettable->GetNumber("shooter/xSpread",0));
	SmartDashboard::PutBoolean("VT_03_PIDEnabled", m_driveangle->IsEnabled());
	//if(m_isActive && !m_driveangle->IsEnabled())
				//m_driveangle->EnableAnglePID();

	if(m_inputs->xBoxRightBumper() && !m_targetingshooter)
	{
		m_targetinggear = !m_targetinggear;
		if(m_targetinggear)
		{
			m_driveangle->EnableAnglePID();
			m_driveangle->SetToCurrentAngle();
		}
		else
		{
			m_driveangle->Stop();
		}
	} else if (m_inputs->xBoxAButton() && !m_targetinggear) {
		m_targetingshooter = !m_targetingshooter;
		if(m_targetingshooter)
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
	} else if (m_driveangle->IsHighGear()) {
		m_driveangle->Shift();
	}

	if(m_targetinggear)
	{
			m_driveangle->Drive(m_inputs->xBoxLeftY(), true);
			TargetGear();
	}
	else
	{
		m_gearcounter = m_nettable->GetNumber("gear/counter",0);
	}

	if(m_targetingshooter)
	{
			m_driveangle->Drive(m_inputs->xBoxLeftY(), true);
			TargetShooter();
	}
	else
	{
		m_shootercounter = m_nettable->GetNumber("shooter/counter",0);
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

void VisionTarget::TargetGear() {
	if(/*container->IsOnTarget() &&*/ m_nettable->GetNumber("gear/counter",0) != m_gearcounter)
	{
		m_gearcounter = m_nettable->GetNumber("gear/counter",0);
		double m_xDegree = (m_nettable->GetNumber("gear/xPos", 0) / 20); // how fast it turns (making it larger is slower)
		int areaDegree = (m_nettable->GetNumber("gear/areaDifference", 0) * 50); // how sensitive the arcing is
		areaDegree = (abs(areaDegree)>6) ? (areaDegree>0?6:-6) : areaDegree; // maximum arc
		areaDegree = (m_nettable->GetNumber("gear/xSpread",0)>180)?0:areaDegree; // distance to stop arcing
		m_driveangle->SetVisionAngle((m_xDegree+areaDegree));
	}
}

void VisionTarget::TargetShooter() {
	if(/*container->IsOnTarget() &&*/ m_nettable->GetNumber("shooter/counter",0) != m_shootercounter)
	{
		m_gearcounter = m_nettable->GetNumber("shooter/counter",0);
		double m_xDegree = (m_nettable->GetNumber("shooter/xPos", 0) / 20); // how fast it turns (making it larger is slower)
		m_driveangle->SetVisionAngle((m_xDegree));
	}
}


void VisionTarget::Stop()
{
	m_targetinggear = 0;
	m_driveangle->Stop();
}

VisionTarget::~VisionTarget() {
	// TODO Auto-generated destructor stub
}

