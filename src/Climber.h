/**
 *  Climber.h
 *  Date:
 *  Last Edited By:
 */


#ifndef SRC_CLIMBER_H_
#define SRC_CLIMBER_H_


#include "OperatorInputs.h"
#include <Spark.h>
#include <CANTalon.h>
#include <SmartDashboard/SmartDashboard.h>
#include <PowerDistributionPanel.h>


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
	//Spark *m_climbmotor;
	CANTalon *m_climbmotor;

	PowerDistributionPanel *m_PDP;
};


#endif /* SRC_CLIMBER_H_ */
