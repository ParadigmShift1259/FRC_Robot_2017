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
	void SetShootRPM(double rpm);
	void Init();
	void Stop();
	void Loop();
	void StartShooting();
protected:
	OperatorInputs *m_inputs;
	CANTalon *m_shootermotor;
	CANTalon *m_feedmotor;
	double m_feedvoltage;
	double m_lowrpm;
	double m_shootrpm;
	double m_ramprpm;
	bool m_shoot;
	bool m_rampdown;
	Timer m_timer;
	double m_P;
	double m_I;
	double m_D;
	double m_F;
	double m_prevshootrpm;
	double m_2prevshootrpm;
	bool m_shooting;
};

#endif /* SRC_SHOOTER_H_ */
