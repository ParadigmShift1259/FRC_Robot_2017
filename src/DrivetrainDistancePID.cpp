// DrivetrainDistancePID.cpp


#include <DrivetrainDistancePID.h>


DrivetrainDistancePID::DrivetrainDistancePID(double p, double i, double d, CANTalon *lefttalon, CANTalon *righttalon, Drivetrain *drivetrain) : PIDSubsystem(p,i,d)
{
	m_lefttalon = lefttalon;
	m_righttalon = righttalon;
	m_drivetrain = drivetrain;
}


DrivetrainDistancePID::~DrivetrainDistancePID()
{

}


void DrivetrainDistancePID::UsePIDOutput(double output)
{
	m_drivetrain->setAutoY(output);
	m_drivetrain->driveAuto();
}


double DrivetrainDistancePID::ReturnPIDInput()
{
	return ((m_righttalon->GetPosition() + m_lefttalon->GetPosition()) / 2) / DRIVE_ENCODER_CPR * DRIVE_WHEEL_CIRCUMFERENCE;
}
