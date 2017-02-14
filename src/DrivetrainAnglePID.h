// DrivetrainAnglePID.h

#ifndef SRC_DRIVETRAINANGLEPID_H_
#define SRC_DRIVETRAINANGLEPID_H_


#include <Commands/PIDSubsystem.h>
#include "Drivetrain.h"
#include "Const.h"


class DrivetrainAnglePID: public frc::PIDSubsystem {
public:
	DrivetrainAnglePID(double p, double i, double d, CANTalon *lefttalon, CANTalon *righttalon, Drivetrain *drivetrain);
	~DrivetrainAnglePID();
	void UsePIDOutput(double output);
	double ReturnPIDInput();

protected:
	CANTalon *m_lefttalon;
	CANTalon *m_righttalon;
	Drivetrain *m_drivetrain;
};

#endif /* SRC_DRIVETRAINANGLEPID_H_ */
