// robot.cpp


#include "Robot.h"


const string strAutoDefault = "Left Gear";
const string strAutoLeftGear = "Left Gear";
const string strAutoRightGear = "Right Gear";
const string strAutoRedShoot = "Red Shoot";
const string strAutoBlueShoot = "Blue Shoot";
const string strAutoStraight = "Straight";


void Robot::RobotInit()
{
	NetworkTable::GlobalDeleteAll();

	// live window inits
	m_lw = LiveWindow::GetInstance();
	m_chooser.AddDefault(strAutoDefault, strAutoDefault);
	m_chooser.AddObject(strAutoLeftGear, strAutoRightGear);
	m_chooser.AddObject(strAutoRightGear, strAutoRightGear);
	m_chooser.AddObject(strAutoRedShoot, strAutoRedShoot);
	m_chooser.AddObject(strAutoBlueShoot, strAutoBlueShoot);
	m_chooser.AddObject(strAutoStraight, strAutoStraight);
	SmartDashboard::PutData("Auto Selector", &m_chooser);

	// class inits
	m_pigeon = new PigeonImu(0);
	m_inputs = new OperatorInputs();
	m_drivetrain = new Drivetrain(m_inputs, &m_ds);
	m_compressor = new Compressor(PCM_COMPRESSOR_SOLENOID);
	m_camera = new Camera();
	m_autonomous = new Autonomous(&m_ds, m_drivetrain, m_inputs);
	m_climber = new Climber(m_inputs);
	m_picker = new Picker(m_inputs);
	m_pidauto = new PIDAutonomous(m_drivetrain);
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
	m_autoselected = kAutoLeftGear;
	m_compressor->Start();
	m_drivetrain->Init();
	m_autonomous->Init();
	m_climber->Init();
	m_picker->Init();
	m_pidauto->Init();
}


void Robot::AutonomousPeriodic()
{
	//m_autonomous->Loop(m_autoselected);
	m_pidauto->Loop();
}


void Robot::TeleopInit()
{
	DriverStation::ReportError("Teleop Init");
	m_compressor->Start();
	m_drivetrain->Init();
	m_climber->Init();
	m_picker->Init();
	m_pigeon->SetFusedHeading(0.0);
}


void Robot::TeleopPeriodic()
{
	double ypr[3];
	m_pigeon->GetYawPitchRoll(ypr);
	SmartDashboard::PutNumber("yaw",ypr[0]);
	SmartDashboard::PutNumber("pitch",ypr[1]);
	SmartDashboard::PutNumber("roll",ypr[2]);
	m_drivetrain->Loop();
	m_climber->Loop();
	m_picker->Loop();
}


void Robot::TestInit()
{
	DriverStation::ReportError("Test Init");
	m_compressor->Start();
	m_drivetrain->Init();
	m_climber->Init();
	m_picker->Init();
}


void Robot::TestPeriodic()
{
	m_drivetrain->Loop();
	m_climber->Loop();
	m_picker->Loop();
}


void Robot::DisabledInit()
{
	DriverStation::ReportError("Disabled Init");
	m_compressor->Stop();
	m_drivetrain->Stop();
	m_autonomous->Stop();
	m_climber->Stop();
	m_picker->Stop();
	m_pidauto->Stop();
}


START_ROBOT_CLASS(Robot)
