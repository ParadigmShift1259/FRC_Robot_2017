/*
 * Shooter.h
 *
 *  Created on: Jan 11, 2017
 *      Author: Developer
 */

#ifndef SRC_SHOOTER_H_
#define SRC_SHOOTER_H_

#include <Spark.h>
#include "OperatorInputs.h"

using namespace frc;


class Shooter {
public:
	Shooter(OperatorInputs *opIn);
	void AdjustSpeed();
	void Loop();
	virtual ~Shooter();

protected:
	Spark *m_shooterMotor;
	OperatorInputs *input;

	double dashNum;


};

#endif /* SRC_SHOOTER_H_ */
