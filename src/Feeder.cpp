/*
 * Feeder.cpp
 *
 *  Created on: Feb 4, 2017
 *      Author: Developer
 */

#include <Feeder.h>



Feeder::Feeder() {
	m_feedermotor = new Spark(FEEDER_CHANNEL);

}

Feeder::~Feeder() {
	// TODO Auto-generated destructor stub
}

void Feeder::RunFeeder(){
	if(m_feedermotor->Get()<FEEDER_POWER){
		m_feedermotor->Set(m_feedermotor->Get()+FEEDER_RAMP);
	} else {
		m_feedermotor->Set(FEEDER_POWER);
	}

}

void Feeder::StopFeeder(){
	if(m_feedermotor->Get()>0){
		m_feedermotor->Set(m_feedermotor->Get()-FEEDER_RAMP);
	} else {
		m_feedermotor->Set(0);
	}
}
