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
	void SetP(double p) {m_P = p; SmartDashboard::PutNumber("DP00_P",m_P); CheckPIDValues();}
	void SetI(double i) {m_I = i; SmartDashboard::PutNumber("DP00_I",m_I); CheckPIDValues();}
	void SetD(double d) {m_D = d; SmartDashboard::PutNumber("DP00_D",m_D); CheckPIDValues();}

protected:
	Drivetrain* m_drivetrain;
	//OperatorInputs *m_inputs;
	bool isInitialized;
	bool isActive;
	double m_y;
	bool m_ramp;
	double m_P;
	double m_I;
	double m_D;
};


#endif /* SRC_DRIVEANGLEPID_H_ */
