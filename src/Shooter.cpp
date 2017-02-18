/**
 *  Shooter.cpp
 *  Date:
 *  Last Edited By:
 */


#include <Shooter.h>
#include <const.h>
#include <driverstation.h>
#include <string>
#include <ctime>
#include <cmath>
#include <Joystick.h>


Shooter::Shooter(OperatorInputs *operatorinputs)
{
	m_inputs = operatorinputs;
	m_shootermotor = new CANTalon(CAN_SHOOTER_MOTOR);
	m_feedmotor = new CANTalon(CAN_FEED_MOTOR);
	m_lowrpm = SHOOTER_LOW_RPM;
	m_shootrpm = SHOOTER_SHOOT_RPM;
	m_shoot = false;
}


Shooter::~Shooter()
{
	delete m_shootermotor;
	delete m_feedmotor;
}


void Shooter::Init()
{
	m_lowrpm = SHOOTER_LOW_RPM;
	m_shootrpm = SHOOTER_SHOOT_RPM;
	m_shoot = false;
	m_timer.Stop();
	m_timer.Reset();

	m_shootermotor->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Coast);
	m_shootermotor->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
	m_shootermotor->SetControlMode(CANSpeedController::ControlMode::kSpeed);
	m_shootermotor->SetPID(CAN_SHOOTER_P, CAN_SHOOTER_I, CAN_SHOOTER_D, CAN_SHOOTER_F);
	m_shootermotor->SetSensorDirection(true);
	m_shootermotor->ConfigEncoderCodesPerRev(CAN_SHOOTER_ENCODER_TICKS);
	m_shootermotor->ClearIaccum();
	m_shootermotor->Enable();
	m_shootermotor->Set(m_lowrpm);

	m_feedmotor->SetControlMode(CANSpeedController::ControlMode::kVoltage);
	m_feedmotor->Set(0);
}


void Shooter::Stop()
{
	m_feedmotor->Set(0);
	m_shootermotor->Disable();
	m_shoot = false;
	m_timer.Stop();
	m_timer.Reset();
}


void Shooter::Loop()
{

	//SmartDashboard::PutString("DB/String 1", "Shooter On: " + std::to_string(!shootertogglebutton));

	/*
	double slidervalue = SmartDashboard::GetNumber("DB/Slider 0", SD_SHOOTER_SLIDER_DEFAULT);
	double newrpm = (slidervalue - SD_SHOOTER_SLIDER_DEFAULT) * SHOOTER_SLIDER_TO_RPM;
	*m_shootermotor->Set(newrpm);

	double encodervalue = m_shootermotor->GetSpeed();
	double velocity = encodervalue * 2 * 3.14159265359 * SHOOTER_RADIUS * (1/60.0); //60 secs per minute
	double outputvoltage = m_shootermotor->GetOutputVoltage();

 	 if (!shootertogglebutton)
	{
		SmartDashboard::PutString("DB/String 1", "Shooter On: Yes");
	}
	else
	{
		SmartDashboard::PutString("DB/String 1", "Shooter On: No");
	}
	SmartDashboard::PutString("DB/String 0", "Input RPM: " + std::to_string(abs(newrpm)));
	SmartDashboard::PutString("DB/String 5", "Output RPM: " 	//+ std::to_string(encodervalue));
	SmartDashboard::PutString("DB/String 6", std::to_string(abs(encodervalue)));
	SmartDashboard::PutString("DB/String 4", "Velocity: " + std::to_string(abs(velocity)));
	SmartDashboard::PutString("DB/String 2", "Output Voltage: "); 	//+ std::to_string(abs(outputvoltage)));
	SmartDashboard::PutString("DB/String 3", std::to_string(abs(outputvoltage)));
	*/

	double shootrpm = m_shootermotor->GetSpeed() * SHOOTER_DIRECTION;
	double feedrpm = m_feedmotor->GetSpeed();
	//Error 2: feedvoltage needs to be multiplied by FEEDER_DIRECTION for the math to work
	double feedvoltage = m_feedmotor->GetOutputVoltage();
	bool shooterbutton = m_inputs->xBoxRightBumper();
	bool shooterrpmup = m_inputs->xBoxDPadUp(OperatorInputs::ToggleChoice::kHold);
	bool shooterrpmdown = m_inputs->xBoxDPadDown(OperatorInputs::ToggleChoice::kHold);
	bool feedrpmup = m_inputs->xBoxDPadRight(OperatorInputs::ToggleChoice::kHold);
	bool feedrpmdown = m_inputs->xBoxDPadLeft(OperatorInputs::ToggleChoice::kHold);

	SmartDashboard::PutNumber("SH01_shooter", shootrpm);
	SmartDashboard::PutNumber("SH02_feeder", feedrpm);
	SmartDashboard::PutNumber("SH03_feedvolt", feedvoltage);

	if (shooterbutton)
	{
		m_shoot = !m_shoot;
		if (m_shoot)
			m_shootermotor->Set(m_shootrpm * SHOOTER_DIRECTION);
		else
			m_shootermotor->Set(m_lowrpm * SHOOTER_DIRECTION);
	}
	if (shooterrpmup)
	{
		if (m_shoot)
			m_shootermotor->Set(++m_shootrpm * SHOOTER_DIRECTION);
		else
			m_shootermotor->Set(++m_lowrpm * SHOOTER_DIRECTION);
	}
	if (shooterrpmdown)
	{
		if (m_shoot)
			m_shootermotor->Set(--m_shootrpm * SHOOTER_DIRECTION);
		else
			m_shootermotor->Set(--m_lowrpm * SHOOTER_DIRECTION);
	}

	if (m_shoot)
	{
		if (feedrpmup)
		{
			m_feedmotor->Set((feedvoltage += 0.01) * FEEDER_DIRECTION);
		}

		if (feedrpmdown)
		{
			m_feedmotor->Set((feedvoltage -= 0.01) * FEEDER_DIRECTION);
		}
		//error 1, feedmotor speed is constantly reset to -6.5 volts
		if (abs(shootrpm - m_shootrpm) < (SHOOTER_ERROR_RPM * m_shootrpm))
		{
			m_feedmotor->Set(-6.5);
		}
		if (((abs(m_feedmotor->Get())) > 0) && (abs(feedrpm) < 50))
		{
			m_timer.Start();
			if (m_timer.HasPeriodPassed(0.5))
				m_feedmotor->Set(0);
		}
		else
		{
			m_timer.Stop();
			m_timer.Reset();
		}
	}
	else
	{
		m_feedmotor->Set(0);
	}
}
