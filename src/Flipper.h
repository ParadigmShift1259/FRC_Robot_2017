/**
 *  Flipper.h
 *  Date: 2/16/17
 *  Last Edited By: Ertl
 */


#ifndef SRC_FLIPPER_H_
#define SRC_FLIPPER_H_


#include "OperatorInputs.h"
#include <Solenoid.h>
#include <timer.h>
#include <DriverStation.h>


using namespace frc;

class Flipper
{
public:
	Flipper(DriverStation *driverstation, OperatorInputs *operatorinputs);
	~Flipper();
	void Init();
	void Loop();
	void Stop();

protected:
	DriverStation *m_driverstation;
	OperatorInputs *m_inputs;
	Solenoid *m_solenoid;
	Timer m_timer;
	double m_flippedup;
};


#endif /* SRC_SOLENOID_H_ */
