/**
 *  DriveAngle.h
 *  Date:
 *  Last Edited By:
 */


#ifndef SRC_DRIVE_ANGLE_H_
#define SRC_DRIVE_ANGLE_H_


#include <DriveAnglePID.h>
#include "Drivetrain.h"
#include "OperatorInputs.h"
#include <SmartDashboard/SmartDashboard.h>


class DriveAngle
{
public:
	DriveAngle(Drivetrain *drivetrain, OperatorInputs *inputs);
	virtual ~DriveAngle();
	void EnableAnglePID();
	void DisableAnglePID();
	void SetRelativeAngle(double target);
	double GetAngle();
	bool IsOnTarget();
	void Init(bool enable=false);
	void Loop();
	void Drive(double y, bool ramp = false);
	void Stop();
	void SetVisionAngle(double angle);
	void RunNormalDrive();
	bool IsEnabled();
	bool IsHighGear();
	void Shift();
	void SetToCurrentAngle();
	void SetP(double p) {m_driveAnglePID->SetP(p);};
	void SetI(double i) {m_driveAnglePID->SetI(i);};
	void SetD(double d) {m_driveAnglePID->SetD(d);};

protected:
	Drivetrain *m_drivetrain;
	OperatorInputs *m_inputs;
	DriveAnglePID *m_driveAnglePID;
	double m_angle;
};


#endif /* SRC_DRIVE_ANGLE_H_ */
