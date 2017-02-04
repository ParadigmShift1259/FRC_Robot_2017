/*
 * Augur.cpp
 *
 *  Created on: Feb 4, 2017
 *      Author: Developer
 */

#include "Augur.h"

Augur::Augur() {
	m_augurmotor = new Spark(AUGUR_CHANNEL);

}

Augur::~Augur() {
	// TODO Auto-generated destructor stub
}

void Augur::RunAugur(){
	if( m_augurmotor->Get()<AUGUR_POWER){
		m_augurmotor->Set(m_augurmotor->Get()+AUGUR_RAMP);
	} else {
		m_augurmotor->Set(AUGUR_POWER);
	}

}

void Augur::StopAugur(){
	if( m_augurmotor->Get()>0){
		m_augurmotor->Set(m_augurmotor->Get()-AUGUR_RAMP);
	} else {
		m_augurmotor->Set(0);
	}
}

void Augur::InitPulse(){
	m_augurtimer->Start();
	m_augurtimer->Reset();
	m_timetillchange = AUGUR_ON_TIME;
	m_auguron = true;
}

void Augur::PulseAugur(){
	if( m_augurtimer->HasPeriodPassed(m_timetillchange) && m_auguron == true){
		m_auguron = false;
		m_timetillchange = AUGUR_OFF_TIME;
		m_augurtimer->Reset();
	} else if( m_augurtimer->HasPeriodPassed(m_timetillchange) && m_auguron == false) {
		m_auguron = true;
		m_timetillchange = AUGUR_ON_TIME;
		m_augurtimer->Reset();
	}
	if (m_auguron) {
		RunAugur();
	} else {
		StopAugur();
	}

}
