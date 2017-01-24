// robot.cpp


#include "Robot.h"


const string kAutoDefault = "Default";


void Robot::RobotInit()
{
	NetworkTable::GlobalDeleteAll();

	// live window inits
	m_lw = LiveWindow::GetInstance();
	m_chooser.AddDefault(kAutoDefault, kAutoDefault);
	SmartDashboard::PutData("Auto Modes", &m_chooser);

	// class inits
	m_inputs = new OperatorInputs();
	m_drivetrain = new Drivetrain(m_inputs, &m_ds);
	//m_compressor = new Compressor(PCM_COMPRESSOR_SOLENOID);
	m_camera = new Camera();
	m_autonomous = new Autonomous(&m_ds, m_drivetrain, m_inputs);
	m_climber = new Climber(m_inputs);
	m_rangefinder = new RangeFinder();
	m_shooter = new Shooter(m_inputs);
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
	m_autoselected = m_chooser.GetSelected();
	//m_compressor->Start();
	m_drivetrain->Init();
	m_autonomous->Init();
	//m_camera->Init();
	m_climber->Init();
	m_rangefinder->Init();
}


void Robot::AutonomousPeriodic()
{
	m_autonomous->Loop();
}


void Robot::TeleopInit()
{
	DriverStation::ReportError("Teleop Init");
	//m_compressor->Start();
	m_drivetrain->Init();
	//m_camera->Init();
	m_climber->Init();
	m_rangefinder->Init();
	m_shooter->Init();
}


void Robot::TeleopPeriodic()
{
	m_drivetrain->Loop();
	m_climber->Loop();
	m_rangefinder->Loop();
	m_shooter->Loop();
}


void Robot::TestInit()
{
	DriverStation::ReportError("Test Init");
	//m_compressor->Start();
	m_drivetrain->Init();
	//m_camera->Init();
	m_climber->Init();
	m_rangefinder->Init();
}


void Robot::TestPeriodic()
{
	m_drivetrain->Loop();
	m_climber->Loop();
	m_rangefinder->Loop();
}


void Robot::DisabledInit()
{
	DriverStation::ReportError("Disabled Init");
	//m_compressor->Stop();
	m_drivetrain->Stop();
	m_autonomous->Stop();
	m_climber->Stop();
	m_shooter->Stop();
}


START_ROBOT_CLASS(Robot)
