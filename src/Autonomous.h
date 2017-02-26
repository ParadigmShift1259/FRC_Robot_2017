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
#include "GearTarget.h"


class Autonomous
{
public:
	enum Stage { kIdle, kStart, kStage1, kStage2, kStage3, kDeploy };

	Autonomous(DriverStation *driverstation, Drivetrain *drivetrain, DriveAngle *driveangle, GearTarget* geartarget, Picker *picker, OperatorInputs *operatorinputs);
	~Autonomous();
	void Init();
	void Stop();
	bool GoStraight(double feet, double power);
	bool TurnDegree(double degrees);
	void Loop(Auto autoselected);

protected:
	std::shared_ptr<NetworkTable> m_nettable;
	int m_counter;
	DriverStation *m_driverstation;
	Drivetrain *m_drivetrain;
	DriveAngle *m_driveangle;
	GearTarget *m_geartarget;
	OperatorInputs *m_inputs;
	Stage m_stage;
	bool m_turning;
	double m_leftposition;
	double m_rightposition;
	Picker *m_picker;
};


#endif /* SRC_AUTONOMOUS_H_ */
