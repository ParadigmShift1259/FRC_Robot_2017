/*
 * Shooter.h
 *
 *  Created on: Jan 14, 2017
 *      Author: Developer
 */


#ifndef SRC_SHOOTER_H_
#define SRC_SHOOTER_H_

#include "OperatorInputs.h"
#include <CANTalon.h>
#include <Talon.h>

using namespace frc;

class Shooter {
public:
	Shooter(OperatorInputs *operatorinputs);
	~Shooter();
	void Init();
	void Stop();
	void Shoot(double rpm);
protected:
	OperatorInputs *m_inputs;
	CANTalon *m_shootermotor;
	Talon *m_feedmotor;

};

#endif /* SRC_SHOOTER_H_ */
