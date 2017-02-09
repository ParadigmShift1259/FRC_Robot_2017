/*
 * Auger.h
 *
 *  Created on: Feb 4, 2017
 *      Author: Developer
 */

#ifndef AUGER_H_
#define AUGER_H_

#include <PWMSpeedController.h>
#include <Spark.h>
#include "Const.h"
#include <timer.h>

using namespace frc;

class Auger {
public:
	Auger();
	virtual ~Auger();
	void RunAuger();
	void StopAuger();
	void PulseAuger();
	void InitPulse();
protected:
	PWMSpeedController *m_augermotor;
	Timer *m_augertimer;
	bool m_augeron; //Returns if the Auger is on or not
	double m_timetillchange; //Time until the Auger changes direction

};

#endif /* AUGER_H_ */
