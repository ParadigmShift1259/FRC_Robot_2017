// DiveAnglePID.h


#ifndef SRC_DRIVEANGLEPID_H_
#define SRC_DRIVEANGLEPID_H_


#include "WPILib.h"
#include <networktables/NetworkTable.h>
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
	void SetNewRelativeSetpoint(double newSetpoint);
	void UsePIDOutput(double output);
	double ReturnCurrentPosition();
	void CheckPIDValues();
	void SetY(double y);
	double GetY();
	void SetRamp(bool ramp);
	bool GetRamp();

protected:
	Drivetrain* m_drivetrain;
	//OperatorInputs *m_inputs;
	shared_ptr<NetworkTable> m_netTable;
	bool isInitialized;
	bool isActive;
	double m_y;
	bool m_ramp;
};


#endif /* SRC_DRIVEANGLEPID_H_ */
