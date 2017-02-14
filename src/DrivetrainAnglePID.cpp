// DrivetrainAnlgePID.cpp

#include <DrivetrainAnglePID.h>


DrivetrainAnglePID::DrivetrainAnglePID(double p, double i, double d, CANTalon *lefttalon, CANTalon *righttalon, Drivetrain *drivetrain) : PIDSubsystem(p,i,d)
{
	m_lefttalon = lefttalon;
	m_righttalon = righttalon;
	m_drivetrain = drivetrain;
}


DrivetrainAnglePID::~DrivetrainAnglePID()
{
}


void DrivetrainAnglePID::UsePIDOutput(double output)
{
	m_drivetrain->setAutoX(output);
	m_drivetrain->driveAuto();
}


double DrivetrainAnglePID::ReturnPIDInput()
{
	return ((m_righttalon->GetPosition() - m_lefttalon->GetPosition()) / DRIVE_ENCODER_CPR) * 360 * (DRIVE_WHEEL_CIRCUMFERENCE / (6.28318531 * DRIVE_WHEEL_BASE));
}

