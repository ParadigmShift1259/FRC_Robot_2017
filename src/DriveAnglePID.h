/**
 *  DriveAnglePID.h
 *  Date:
 *  Last Edited By:
 */


#ifndef SRC_DRIVEANGLEPID_H_
#define SRC_DRIVEANGLEPID_H_


#include "WPILib.h"
#include <Smartdashboard/Smartdashboard.h>
#include <Commands/PIDSubsystem.h>
#include <Const.h>
#include "Drivetrain.h"
//#include <ntCore.h>
//#include <nt_Value.h>


class DriveAnglePID: public PIDSubsystem
{
public:
	DriveAnglePID(Drivetrain *drive);
	virtual ~DriveAnglePID();
	double ReturnPIDInput();
	void ChangeActive(bool newState);
	bool IsDone();
	void SetSetpointRelativeToError(double newSetpoint);
	void UsePIDOutput(double output);
	double ReturnCurrentPosition();
	void CheckPIDValues();
	void SetY(double y);
	double GetY();
	void SetRamp(bool ramp);
	bool GetRamp();
	bool IsEnabled();
	void SetRelativeSetpoint(double setpoint);

protected:
	Drivetrain* m_drivetrain;
	//OperatorInputs *m_inputs;
	bool isInitialized;
	bool isActive;
	double m_y;
	bool m_ramp;
	double m_P = 0.1;
	double m_I = 0.0125;
	double m_D = 0.0;
};


#endif /* SRC_DRIVEANGLEPID_H_ */
