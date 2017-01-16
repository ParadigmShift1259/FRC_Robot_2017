/*
 * Shooter.h
 *
 *  Created on: Jan 14, 2017
 *      Author: Developer
 */


#ifndef SRC_SHOOTER_H_
#define SRC_SHOOTER_H_

#include <CANTalon.h>


using namespace frc;

class Shooter {
public:
	Shooter();
	~Shooter();
	void Init();
	void Stop();
	void Loop();
protected:
	CANTalon *m_shootermotor;

};

#endif /* SRC_SHOOTER_H_ */
