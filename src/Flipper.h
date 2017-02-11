// Flipper.h


#ifndef SRC_FLIPPER_H_
#define SRC_FLIPPER_H_


#include "OperatorInputs.h"
#include <Solenoid.h>


using namespace frc;


class Flipper
{
public:
	Flipper(OperatorInputs *operatorinputs);
	~Flipper();
	void Init();
	void Loop();
	void Stop();

protected:
	OperatorInputs *m_inputs;
	Solenoid *m_solenoid;
};


#endif /* SRC_SOLENOID_H_ */
