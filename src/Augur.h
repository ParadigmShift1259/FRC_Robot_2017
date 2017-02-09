/*
 * Augur.h
 *
 *  Created on: Feb 4, 2017
 *      Author: Developer
 */

#ifndef AUGUR_H_
#define AUGUR_H_

#include <PWMSpeedController.h>
#include <Spark.h>
#include "Const.h"
#include <timer.h>

using namespace frc;

class Augur {
public:
	Augur();
	virtual ~Augur();
	void RunAugur();
	void StopAugur();
	void PulseAugur();
	void InitPulse();
protected:
	PWMSpeedController *m_augurmotor;
	Timer *m_augurtimer;
	bool m_auguron; //Returns if the Augur is on or not
	double m_timetillchange; //Time until the Augur changes direction

};

#endif /* AUGUR_H_ */
