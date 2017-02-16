/*
 * GearTarget.cpp
 *
 *  Created on: Feb 15, 2017
 *      Author: Developer
 */

#include "GearTarget.h"

GearTarget::GearTarget(std::shared_ptr<NetworkTable> newTable, DriveAngle * newAngle) {
	// TODO Auto-generated constructor stub
	xDegree = 0;
	netTable = newTable;
	container = newAngle;
	prevCounter = 0;
	counter = 0;
	isDone = true;
	stage = stopped;
}

void GearTarget::Init()
{
	prevCounter = 0;
	stage = stopped;
}

void GearTarget::Target()
{
	isDone = false;
	stage = read;
}

void GearTarget::Loop()
{
	switch (stage)
	{
		case stopped:
			break;

		case read:
			if(counter < 3)
			{
				prevCounter = netTable->GetValue("counter")->GetDouble();
				counter++;
			}
			else if(netTable->GetValue("counter")->GetDouble() > prevCounter)
			{
				xDegree = netTable->GetValue("xPos")->GetDouble() / 10;
				container->EnableAnglePID();
				container->SetRelativeAngle(xDegree);
				stage = targeting;
			}
			else
			{
				isDone = true;
				stage = stopped;
			}
			break;
		case targeting:
			if(container->IsOnTarget())
			{
				isDone = true;
				stage = stopped;
			}


	}
}

void GearTarget::Stop()
{

}

GearTarget::~GearTarget() {
	// TODO Auto-generated destructor stub
}

