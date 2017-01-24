// Autonomous.h


#ifndef SRC_AUTONOMOUS_H_
#define SRC_AUTONOMOUS_H_


#include <DriverStation.h>
#include "Drivetrain.h"
#include "OperatorInputs.h"


class Autonomous
{
public:
	enum Stage { kIdle, kStage1, kStage2, kStage3, kStage4, kStage5 };

	Autonomous(DriverStation *driverstation, Drivetrain *drivetrain, OperatorInputs *operatorinputs);
	~Autonomous();
	void Init();
	void Loop();
	void Stop();
	void EnablePID(double kP, double kI, double kPosLeft, double kPosRight);
	void DisablePID();

protected:
	DriverStation *m_driverstation;
	Drivetrain *m_drivetrain;
	OperatorInputs *m_inputs;
	Timer m_timer;
	Stage m_stage;
};


#endif /* SRC_AUTONOMOUS_H_ */
