/**
 *  Climber.h
 *  Date:
 *  Last Edited By:
 */


#ifndef SRC_CLIMBER_H_
#define SRC_CLIMBER_H_


#include "OperatorInputs.h"
#include "Shooter.h"
#include <Spark.h>
#include <CANTalon.h>
#include <SmartDashboard/SmartDashboard.h>
#include <PowerDistributionPanel.h>
#include <timer.h>
#include <Picker.h>

using namespace frc;


class Climber
{
public:
	Climber(OperatorInputs *operatorinputs, Shooter *shooter, Picker *picker);
	~Climber();
	void Init();
	void Loop();
	void Stop();

protected:
	Picker *m_picker;
	OperatorInputs *m_inputs;
	Shooter *m_shooter;
	//Spark *m_climbmotor;
	CANTalon *m_climbmotor;
	Timer m_timer;
	PowerDistributionPanel *m_PDP;
	bool timerStarted = false;
};


#endif /* SRC_CLIMBER_H_ */
