// PIDAutonomous.h


#ifndef SRC_PIDAUTONOMOUS_H_
#define SRC_PIDAUTONOMOUS_H_

#include "Drivetrain.h"
#include "DrivetrainAnglePID.h"
#include "DrivetrainDistancePID.h"

class PIDAutonomous
{
public:
	enum Stage { kStart, kDrive1, kDriving1, kTurn1, kTurning1, kDrive2, kDriving2, kDeploy, kIdle};

	PIDAutonomous(Drivetrain *drivetrain);
	~PIDAutonomous();
	void Init();
	void Loop();
	void Stop();

protected:
	Drivetrain *m_drivetrain;
	DrivetrainAnglePID *m_driveanglepid;
	DrivetrainDistancePID *m_drivedistancepid;

	//Move these variables to const.h when finished
	double m_angleP = 0.75;
	double m_angleI = 0.001;
	double m_angleD = 10;
	double m_angletolerance = 0.1;

	double m_distanceP = 0.4;
	double m_distanceI = 0;
	double m_distanceD = 2;
	double m_distancetolerance = 0.5;


	Stage m_stage;

	double m_drivedistances[2] = {72.0, 72.0};
	double m_driveangles[1] = {60.0};
};


#endif /* SRC_PIDAUTONOMOUS_H_ */
