//Picker.h

#ifndef SRC_AUGER_H_
#define SRC_AUGER_H_


#include <Spark.h>
#include "OperatorInputs.h"


using namespace std;


class Auger
{
public:
	Auger();
	~Auger();
	void Start();
	void Loop();
	void Stop();

protected:
	OperatorInputs *m_inputs;
	Spark *m_motor;
};

/* namespace std */

#endif /* SRC_AUGER_H_ */
