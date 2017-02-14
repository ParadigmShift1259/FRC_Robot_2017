// DrivetrainDistancePID.h


#ifndef SRC_DRIVETRAINDISTANCEPID_H_
#define SRC_DRIVETRAINDISTANCEPID_H_


#include <Commands/PIDSubsystem.h>
#include "Drivetrain.h"
#include "Const.h"

class DrivetrainDistancePID: public frc::PIDSubsystem {
public:
	DrivetrainDistancePID(double p, double i, double d, CANTalon *lefttalon, CANTalon *righttalon, Drivetrain *drivetrain);
	~DrivetrainDistancePID();
	void UsePIDOutput(double output);
	double ReturnPIDInput();

protected:
	CANTalon *m_lefttalon;
	CANTalon *m_righttalon;
	Drivetrain *m_drivetrain;
};

#endif /* SRC_DRIVETRAINDISTANCEPID_H_ */
