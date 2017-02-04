/*
 * Feeder.h
 *
 *  Created on: Feb 4, 2017
 *      Author: Developer
 */

#ifndef SRC_FEEDER_H_
#define SRC_FEEDER_H_

#include <PWMSpeedController.h>
#include <Spark.h>
#include "Const.h"

using namespace frc;

class Feeder {
public:
	Feeder();
	virtual ~Feeder();
	void RunFeeder();
	void StopFeeder();
protected:
	PWMSpeedController *m_feedermotor;
};

#endif /* SRC_FEEDER_H_ */
