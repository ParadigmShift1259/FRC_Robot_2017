/*
 * GearPlaceContainer.cpp
 *
 *  Created on: Feb 11, 2017
 *      Author: Developer
 */

#include "GearPlaceContainer.h"

GearPlaceContainer::GearPlaceContainer(Drivetrain *drivetrain, std::shared_ptr<NetworkTable> nTable, OperatorInputs *oi) {
	m_autoGearPlace = new AutoGearPlace(nTable, drivetrain, oi);
	m_drivetrain = drivetrain;
	m_netTable = nTable;
	angleTarget = 0;
	netLoopCount = 0;
	m_inputs = oi;
}

void GearPlaceContainer::StartGearPlace()
{
	if(m_drivetrain->getIsHighGear())
	{
		m_drivetrain->Shift();
	}
	m_autoGearPlace->CheckPIDValues();
	//angle target must be defined by this point
	m_autoGearPlace->SetNewRelativeSetpoint(angleTarget);
	m_autoGearPlace->ChangeActive(true);
}

void GearPlaceContainer::MaintainGearPlace()
{
	if(!(int)m_netTable->GetValue("LoopCount").get()->GetDouble() == netLoopCount)
	{
		//change angleTarget
		m_autoGearPlace->CheckPIDValues();
		m_autoGearPlace->SetNewRelativeSetpoint(angleTarget);
	}
}

GearPlaceContainer::~GearPlaceContainer() {

}

