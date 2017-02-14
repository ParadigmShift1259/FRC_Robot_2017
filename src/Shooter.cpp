// Shooter.cpp


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
	m_shootermotor->ConfigNeutralMode(CANSpeedController::NeutralMode::kNeutralMode_Coast);
	m_shootermotor->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
	m_shootermotor->SetControlMode(CANSpeedController::ControlMode::kSpeed);
	m_shootermotor->SetPID(CAN_SHOOTER_P, CAN_SHOOTER_I, CAN_SHOOTER_D, CAN_SHOOTER_F);
	m_shootermotor->ConfigEncoderCodesPerRev(CAN_SHOOTER_ENCODER_TICKS);
	m_shootermotor->ClearIaccum();
	m_shootermotor->Enable();
	m_shootermotor->Set(0);

	m_feedmotor->SetControlMode(CANSpeedController::ControlMode::kVoltage);
	m_feedmotor->Set(0);

	m_lowrpm = SHOOTER_LOW_RPM;
	m_shootrpm = SHOOTER_SHOOT_RPM;
	m_shoot = false;
}


void Shooter::Stop()
{
	m_feedmotor->Set(0);
	m_shootermotor->Disable();
}


void Shooter::Loop()
{

	//SmartDashboard::PutString("DB/String 1", "Shooter On: " + std::to_string(!shootertogglebutton));

	/*
	double slidervalue = SmartDashboard::GetNumber("DB/Slider 0", SD_SHOOTER_SLIDER_DEFAULT);
	double newrpm = (slidervalue - SD_SHOOTER_SLIDER_DEFAULT) * SHOOTER_SLIDER_TO_RPM;
	m_shootermotor->Set(newrpm);

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

	double speed = m_shootermotor->GetSpeed() * SHOOTER_DIRECTION;
	bool shooterbutton = m_inputs->xBoxRightBumper();
	bool rpmup = m_inputs->xBoxDPadUp(OperatorInputs::ToggleChoice::kHold);
	bool rpmdown = m_inputs->xBoxDPadDown(OperatorInputs::ToggleChoice::kHold);

	if (shooterbutton)
	{
		m_shoot = !m_shoot;
		if (m_shoot)
			m_shootermotor->Set(m_shootrpm * SHOOTER_DIRECTION);
		else
			m_shootermotor->Set(m_lowrpm * SHOOTER_DIRECTION);
	}
	if (rpmup)
	{
		if (m_shoot)
			m_shootrpm++;
		else
			m_lowrpm++;
	}
	if (rpmdown)
	{
		if (m_shoot)
			m_shootrpm--;
		else
			m_lowrpm--;
	}
	if (m_shoot)
	{
		if (abs(speed - m_shootrpm) < (SHOOTER_ERROR_RPM * m_shootrpm))
		{
			m_feedmotor->Set(4.0);
		}
	}
	else
	{
		m_feedmotor->Set(0);
	}
}



