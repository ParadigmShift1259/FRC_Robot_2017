/**
 *  Shooter.h
 *  Date:
 *  Last Edited By:
 */


#ifndef SRC_SHOOTER_H_
#define SRC_SHOOTER_H_


#include "OperatorInputs.h"
#include <CANTalon.h>
#include <timer.h>


using namespace frc;

class Shooter
{
public:
	Shooter(OperatorInputs *operatorinputs);
	~Shooter();
	void Init();
	void Stop();
	void Loop();
protected:
	OperatorInputs *m_inputs;
	CANTalon *m_shootermotor;
	CANTalon *m_feedmotor;
	double m_lowrpm;
	double m_shootrpm;
	bool m_shoot;
	Timer m_timer;
};

#endif /* SRC_SHOOTER_H_ */
