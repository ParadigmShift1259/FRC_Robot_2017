/**
 *  Autonomous.h
 *  Date:
 *  Last Edited By:
 */


#ifndef SRC_AUTONOMOUS_H_
#define SRC_AUTONOMOUS_H_


#include <DriverStation.h>
#include "Drivetrain.h"
#include "DriveAngle.h"
#include "OperatorInputs.h"
#include "const.h"
#include "Picker.h"


class Autonomous
{
public:
	enum Stage { kIdle, kStart, kStage1, kStage2, kStage3, kDeploy };

	Autonomous(DriverStation *driverstation, Drivetrain *drivetrain, DriveAngle *driveangle, Picker *picker, OperatorInputs *operatorinputs);
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
	bool m_turning;
	double m_leftposition;
	double m_rightposition;
	Picker *m_picker;
};


#endif /* SRC_AUTONOMOUS_H_ */
