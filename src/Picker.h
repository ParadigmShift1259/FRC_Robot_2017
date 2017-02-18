/**
 *  Picker.h
 *  Date:
 *  Last Edited By:
 */


#ifndef SRC_PICKER_H_
#define SRC_PICKER_H_


#include <Spark.h>
#include "OperatorInputs.h"
#include <Solenoid.h>


using namespace frc;


class Picker
{
public:

	Picker(OperatorInputs *inputs);
	~Picker();
	void Init();
	void Loop();
	void Stop();
	void Deploy();

protected:
	OperatorInputs *m_inputs;
	Spark *m_motor;
	bool m_running;
	double m_ramping;
	Solenoid *m_solenoid;
};


#endif /* SRC_PICKER_H_ */
