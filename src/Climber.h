// Climber.h


#ifndef SRC_CLIMBER_H_
#define SRC_CLIMBER_H_


#include "OperatorInputs.h"
#include <Spark.h>


using namespace frc;


class Climber
{
public:
	Climber(OperatorInputs *operatorinputs);
	~Climber();
	void Init();
	void Loop();
	void Stop();

protected:
	OperatorInputs *m_inputs;
	Spark *m_spark;
};


#endif /* SRC_CLIMBER_H_ */
