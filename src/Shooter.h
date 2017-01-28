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
protected:
	CANTalon *m_CANTalon;

};

#endif /* SRC_SHOOTER_H_ */
