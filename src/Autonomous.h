// Autonomous.h


#ifndef SRC_AUTONOMOUS_H_
#define SRC_AUTONOMOUS_H_


#include <DriverStation.h>
#include "Drivetrain.h"
#include "OperatorInputs.h"
#include "const.h"


class Autonomous
{
public:
	enum Stage { kIdle, kStart, kStage1, kStage2, kStage3, kDeploy };

	Autonomous(DriverStation *driverstation, Drivetrain *drivetrain, OperatorInputs *operatorinputs);
	~Autonomous();
	void Init();
	void Stop();
	bool GoStraight(double feet, double power);
	bool TurnDegree(double degrees);
	void Loop(Auto autoselected);

protected:
	DriverStation *m_driverstation;
	Drivetrain *m_drivetrain;
	OperatorInputs *m_inputs;
	Timer m_timer;
	Stage m_stage;
	double m_newleftpos;
	double m_newrightpos;
	bool m_inited;
	bool m_turninited;
};


#endif /* SRC_AUTONOMOUS_H_ */
