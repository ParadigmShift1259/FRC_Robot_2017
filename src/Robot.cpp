// robot.cpp


#include "Robot.h"


void Robot::RobotInit()
{
	NetworkTable::GlobalDeleteAll();
	// live window inits
	m_lw = LiveWindow::GetInstance();
	m_autonamedefault = "Default";
	m_autonamecustom = "My Auto";
	// class inits
	m_inputs = new OperatorInputs();
	m_shooter = new Shooter(m_inputs);
	m_drivetrain = new Drivetrain(m_inputs, &m_ds);


}


/*
 * This autonomous (along with the chooser code above) shows how to select between different autonomous modes
 * using the dashboard. The sendable chooser code works with the Java SmartDashboard. If you prefer the LabVIEW
 * Dashboard, remove all of the chooser code and uncomment the GetString line to get the auto name from the text box
 * below the Gyro
 *
 * You can add additional auto modes by adding additional comparisons to the if-else structure below with additional strings.
 * If using the SendableChooser make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit()
{
	DriverStation::ReportError("Autonomous Init");

}


void Robot::AutonomousPeriodic()
{

}


void Robot::TeleopInit()
{

}


void Robot::TeleopPeriodic()
{
	m_shooter->Loop();
	m_drivetrain->Loop();

}


void Robot::TestInit()
{

}


void Robot::TestPeriodic()
{

}


void Robot::DisabledInit()
{

}


START_ROBOT_CLASS(Robot)
