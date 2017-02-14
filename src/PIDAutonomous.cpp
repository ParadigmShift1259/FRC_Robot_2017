// PIDAutonomous.cpp


#include <PIDAutonomous.h>


PIDAutonomous::PIDAutonomous(Drivetrain *drivetrain)
{
	m_drivetrain = drivetrain;
	m_driveanglepid = new DrivetrainAnglePID(m_angleP, m_angleI, m_angleD, m_drivetrain->LeftTalon(), m_drivetrain->RightTalon(), drivetrain);
	m_drivedistancepid = new DrivetrainDistancePID(m_distanceP, m_distanceI, m_distanceD, m_drivetrain->LeftTalon(), m_drivetrain->RightTalon(), drivetrain);
	m_stage = kIdle;
}


PIDAutonomous::~PIDAutonomous()
{
	delete m_driveanglepid;
}


void PIDAutonomous::Init()
{
	m_drivetrain->LeftTalon()->SetPosition(0);
	m_drivetrain->RightTalon()->SetPosition(0);
	m_driveanglepid->SetAbsoluteTolerance(m_angletolerance);
	m_driveanglepid->SetAbsoluteTolerance(m_distancetolerance);
	m_stage = kStart;
}

void PIDAutonomous::Stop() {
	m_drivetrain->setAutoX(0);
	m_drivetrain->setAutoY(0);
	m_drivetrain->driveAuto();
	m_driveanglepid->Disable();
	m_drivedistancepid->Disable();
}

void PIDAutonomous::Loop()
{
	switch(m_stage)
	{
		case kIdle:
			m_drivetrain->setAutoX(0);
			m_drivetrain->setAutoY(0);
			m_drivetrain->driveAuto();
			m_driveanglepid->Disable();
			m_drivedistancepid->Disable();
			break;
		case kStart:
			m_driveanglepid->Enable();
			m_drivedistancepid->Enable();
			m_driveanglepid->SetSetpoint(0);
			m_drivedistancepid->SetSetpoint(0);
			m_stage= (enum Stage)((int)m_stage + 1);
			DriverStation::ReportError("Starting");
			break;
		case kDrive1:
			m_drivedistancepid->SetSetpointRelative(m_drivedistances[0]); //Pass in inches
			m_stage= (enum Stage)((int)m_stage + 1);
			DriverStation::ReportError("Drive Stage 1");
			break;
		case kDriving1:
			if(m_drivedistancepid->OnTarget()) {
				m_stage= (enum Stage)((int)m_stage + 1);
			}
			break;
		case kDrive2:
			m_drivedistancepid->SetSetpointRelative(m_drivedistances[1]); //Pass in inches
			m_stage= (enum Stage)((int)m_stage + 1);
			DriverStation::ReportError("Drive Stage 2");
			break;
		case kDriving2:
			if(m_drivedistancepid->OnTarget()) {
				m_stage= (enum Stage)((int)m_stage + 1);
			}
			break;
		case kTurn1:
			m_driveanglepid->SetSetpointRelative(m_driveangles[0]); //Pass in inches
			m_stage= (enum Stage)((int)m_stage + 1);
			DriverStation::ReportError("Turn Stage 1");
			break;
		case kTurning1:
			if(m_driveanglepid->OnTarget()) {
				m_stage= (enum Stage)((int)m_stage + 1);
			}
			break;
		case kDeploy:
			DriverStation::ReportError("deploy");
			m_stage= (enum Stage)((int)m_stage + 1);
			break;
	}
}
