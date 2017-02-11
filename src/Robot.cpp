// robot.cpp


#include "Robot.h"
#include <string>

const string strAutoDefault = "Left Gear";
const string strAutoLeftGear = "Left Gear";
const string strAutoRightGear = "Right Gear";
const string strAutoRedShoot = "Red Shoot";
const string strAutoBlueShoot = "Blue Shoot";
const string strAutoStraight = "Straight";


void Robot::RobotInit()
{
	NetworkTable::GlobalDeleteAll();
	m_netTable = NetworkTable::GetTable("OpenCV");
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
	m_inputs = new OperatorInputs();
	m_drivetrain = new Drivetrain(m_inputs, &m_ds);
	m_compressor = new Compressor(PCM_COMPRESSOR_SOLENOID);
	m_camera = new Camera();
	m_autonomous = new Autonomous(&m_ds, m_drivetrain, m_inputs);
	m_climber = new Climber(m_inputs);
	m_shooter = new Shooter(m_inputs);
	m_picker = new Picker(m_inputs);
	m_autoGearPlacer = new AutoGearPlace(m_netTable, m_drivetrain, m_inputs);
	SmartDashboard::PutNumber("DB/Slider 3", 0);
	turnValue = SmartDashboard::GetNumber("DB/Slider 3", 0);
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
	//m_autoselected = Chooser2Auto(m_chooserselected);
	m_compressor->Start();
	m_drivetrain->Init();
	m_autonomous->Init();
	m_climber->Init();
	m_picker->Init();
	SmartDashboard::PutNumber("DB/Slider 3", 0);
	turnValue = SmartDashboard::GetNumber("DB/Slider 3", 0);
	//m_autoGearPlacer->ChangeActive(true);
}


void Robot::AutonomousPeriodic()
{
	m_autoGearPlacer->CheckPIDValues();
	if(turnValue != SmartDashboard::GetNumber("DB/Slider 3", 0))
	{
		turnValue = SmartDashboard::GetNumber("DB/Slider 3", 0);
		m_autoGearPlacer->SetNewRelativeSetpoint(turnValue);
	}
	m_autoGearPlacer->ChangeActive(true);

	//m_autonomous->Loop(m_autoselected);
	m_netTable->PutNumber("DTAngle",m_autoGearPlacer->ReturnCurrentPosition());

}


void Robot::TeleopInit()
{
	DriverStation::ReportError("Teleop Init");
	m_compressor->Start();
	m_drivetrain->Init();
	m_climber->Init();
	m_picker->Init();
	m_shooter->Init();
}


void Robot::TeleopPeriodic()
{
	m_drivetrain->Loop();
	m_climber->Loop();
	m_picker->Loop();
	m_shooter->Loop();
}


void Robot::TestInit()
{
	DriverStation::ReportError("Autonomous Init");
	m_autoselected = kAutoLeftGear;
	//m_autoselected = Chooser2Auto(m_chooserselected);
	m_compressor->Start();
	m_drivetrain->Init();
	m_autonomous->Init();
	m_climber->Init();
	m_picker->Init();
	SmartDashboard::PutNumber("DB/Slider 3", 0);
	turnValue = SmartDashboard::GetNumber("DB/Slider 3", 0);
	//m_autoGearPlacer->ChangeActive(true);
}


void Robot::TestPeriodic()
{
	m_autoGearPlacer->CheckPIDValues();
	if(turnValue != SmartDashboard::GetNumber("DB/Slider 3", 0))
	{
		turnValue = SmartDashboard::GetNumber("DB/Slider 3", 0);
		m_autoGearPlacer->SetNewRelativeSetpoint(turnValue);
	}
	m_autoGearPlacer->ChangeActive(true);
	//m_autonomous->Loop(m_autoselected);
	m_netTable->PutNumber("DTAngle",m_autoGearPlacer->ReturnCurrentPosition());
}


void Robot::DisabledInit()
{
	m_autoGearPlacer->ChangeActive(false);
	DriverStation::ReportError("Disabled Init");
	m_compressor->Stop();
	m_drivetrain->Stop();
	m_autonomous->Stop();
	m_climber->Stop();
	m_picker->Stop();
	m_shooter->Stop();
	m_autoGearPlacer->isInitialized = false;
}


Auto Robot::Chooser2Auto(string selected)
{
	if (selected == strAutoLeftGear)
		return kAutoLeftGear;
	if (selected == strAutoRightGear)
		return kAutoRightGear;
	if (selected == strAutoRedShoot)
		return kAutoRedShoot;
	if (selected == strAutoBlueShoot)
		return kAutoBlueShoot;
	if (selected == strAutoStraight)
		return kAutoStraight;
	return kAutoLeftGear;
}


START_ROBOT_CLASS(Robot)
