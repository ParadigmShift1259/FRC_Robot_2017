// Picker.h


#ifndef SRC_PICKER_H_
#define SRC_PICKER_H_


#include <Spark.h>
#include "OperatorInputs.h"
#include <Solenoid.h>


using namespace frc;


class Picker
{
public:

	enum Stage {kDeploy, kDeploying, kRunning};

	Picker(OperatorInputs *inputs);
	~Picker();
	void Init();
	void Loop();
	void Stop();

protected:
	OperatorInputs *m_inputs;
	Spark *m_motor;
	Stage m_stage;
	bool m_running;
	double m_ramping;
	Solenoid *m_solenoid;
};


#endif /* SRC_PICKER_H_ */
