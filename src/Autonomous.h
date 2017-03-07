/**
 *  Autonomous.h
 *  Date:
 *  Last Edited By:
 */


#ifndef SRC_AUTONOMOUS_H_
#define SRC_AUTONOMOUS_H_


#include <DriverStation.h>
#include <VisionTarget.h>
#include "Drivetrain.h"
#include "DriveAngle.h"
#include "OperatorInputs.h"
#include "const.h"
#include "Picker.h"
#include "Shooter.h"
#include "Timer.h"

class Autonomous
{
public:
	enum Stage { kIdle, kStart, kStage1, kStage2, kStage3, kStage4, kStage5, kShoot, kDeploy };

	Autonomous(DriverStation *driverstation, Drivetrain *drivetrain, DriveAngle *driveangle, VisionTarget* visiontarget, Picker *picker, OperatorInputs *operatorinputs, Shooter *shooter);
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
	VisionTarget *m_visiontarget;
	OperatorInputs *m_inputs;
	Shooter *m_shooter;
	Stage m_stage;
	Timer *m_timer;
	bool m_turning;
	double m_leftposition;
	double m_rightposition;
	Picker *m_picker;
};


#endif /* SRC_AUTONOMOUS_H_ */
