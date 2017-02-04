// Picker.h


#ifndef SRC_PICKER_H_
#define SRC_PICKER_H_


#include <Spark.h>
#include "OperatorInputs.h"


using namespace frc;


class Picker
{
public:
	Picker(OperatorInputs *inputs);
	~Picker();
	void Init();
	void Loop();
	void Stop();

protected:
	OperatorInputs *m_inputs;
	Spark *m_motor;
	bool m_running;
};


#endif /* SRC_PICKER_H_ */
