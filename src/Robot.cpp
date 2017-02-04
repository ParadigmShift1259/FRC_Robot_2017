// robot.cpp


#include "Robot.h"


const string kAutoDefault = "Default";


void Robot::RobotInit()
{
	NetworkTable::GlobalDeleteAll();
	netTable = NetworkTable::GetTable("OpenCV");

	// live window inits
	m_lw = LiveWindow::GetInstance();
	//m_chooser.AddDefault(kAutoDefault, kAutoDefault);
	//SmartDashboard::PutData("Auto Modes", &m_chooser);
	isTargetingGear = false;
	// class inits
	m_inputs = new OperatorInputs();
	m_drivetrain = new Drivetrain(m_inputs, &m_ds);
	//m_compressor = new Compressor(PCM_COMPRESSOR_SOLENOID);
	m_camera = new Camera();
	m_autonomous = new Autonomous(&m_ds, m_drivetrain, m_inputs);
	m_climber = new Climber(m_inputs);
	m_shooter = new Shooter(m_inputs);
	m_gearPlace = new AutoGearPlace(netTable, m_drivetrain);
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
	//m_autoselected = m_chooser.GetSelected();
	//m_compressor->Start();
	gearStage = GearStage::enabling;
	m_drivetrain->Init();
	m_autonomous->Init();
	//m_camera->Init();
	m_climber->Init();
	m_gearPlace->changeActive(false);
}


void Robot::AutonomousPeriodic()
{
	switch (gearStage)
	{
	case GearStage::disabled:
		netTable->PutString("R_gearStage","disabled");
		//everyone else shove stuff you want to do here
		//m_autonomous->Loop();
		gearStage = enabling;
		break;

	case GearStage::enabling:
		netTable->PutString("R_gearStage","enabling");
		//SmartDashboard::PutString("DB/String 4",std::to_string(netTable->GetNumber("xPos",0)));
		m_gearPlace->changeActive(true);
		gearStage = enabled;
		break;

	case GearStage::enabled:
		netTable->PutNumber("AGP_setpoint",m_gearPlace->GetSetpoint());
		netTable->PutString("R_gearStage","enabled");
		if(m_gearPlace->isDone())
				{
					gearStage = disabling;
				}

		break;

	case GearStage::disabling:
		netTable->PutString("R_gearStage","disabling");
			m_gearPlace->changeActive(false);
		gearStage = disabled;
		break;
	}

}


void Robot::TeleopInit()
{
	gearStage = disabled;
	m_gearPlace->changeActive(false);
	DriverStation::ReportError("Teleop Init");
	//m_compressor->Start();
	m_drivetrain->Init();
	//m_camera->Init();
	m_climber->Init();
	m_shooter->Init();

}


void Robot::TeleopPeriodic()
{
	switch (gearStage)
	{
	case disabled:
		netTable->PutString("R_gearStage","disabled");
		//everyone else shove stuff you want to do here
		m_drivetrain->Loop();
		m_climber->Loop();
		/*if(undecided button)
		{
			gearStage = enabling;
		}
		else
		{*/
		break;
		//}
	case enabling:
		netTable->PutString("R_gearStage","enabling");

		m_gearPlace->changeActive(true);
		gearStage = enabled;
		break;

	case enabled:
		netTable->PutString("R_gearStage","enabled");
		if(m_gearPlace->isDone() /* || other undecided button */)
				{
					gearStage = disabling;
				}
		break;

			case disabling:
		netTable->PutString("R_gearStage","disabling");
			m_gearPlace->changeActive(false);
			gearStage = disabled;
		break;
	}
//	m_drivetrain->Loop();
//	m_climber->Loop();
//	m_shooter->Loop();

}


void Robot::TestInit()
{
	DriverStation::ReportError("Test Init");
	//m_compressor->Start();
	m_drivetrain->Init();
	//m_camera->Init();
	m_climber->Init();
}


void Robot::TestPeriodic()
{
	m_drivetrain->Loop();
	m_climber->Loop();
}


void Robot::DisabledInit()
{
	DriverStation::ReportError("Disabled Init");
	//m_compressor->Stop();
	m_drivetrain->Stop();
	m_autonomous->Stop();
	m_climber->Stop();
	m_shooter->Stop();
	//m_gearPlace->changeActive(false);
}


START_ROBOT_CLASS(Robot)
