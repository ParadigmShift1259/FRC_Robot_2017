// Autonomous.h


#ifndef SRC_AUTONOMOUS_H_
#define SRC_AUTONOMOUS_H_


#include <DriverStation.h>
#include "Drivetrain.h"
#include "DriveAngle.h"
#include "OperatorInputs.h"
#include "const.h"


class Autonomous
{
public:
	enum Stage { kIdle, kStart, kStage1, kStage2, kStage3, kStage4, kDeploy };

	Autonomous(DriverStation *driverstation, Drivetrain *drivetrain, DriveAngle *driveangle, OperatorInputs *operatorinputs);
	~Autonomous();
	void Init();
	void Stop();
	bool GoStraight(double feet, double power);
	bool TurnDegree(double degrees);
	void Loop(Auto autoselected);

protected:
	DriverStation *m_driverstation;
	Drivetrain *m_drivetrain;
	DriveAngle *m_driveangle;
	OperatorInputs *m_inputs;
	Stage m_stage;
	double m_leftposition;
	double m_rightposition;
};


#endif /* SRC_AUTONOMOUS_H_ */
