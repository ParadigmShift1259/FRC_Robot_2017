/*
 * Shooter.cpp
 *
 *  Created on: Jan 14, 2017
 *      Author: Developer
 */

#include <Shooter.h>
#include <const.h>
#include <driverstation.h>
#include <string>
#include <ctime>
#include <Commands/PIDSubsystem.h>


Shooter::Shooter(OperatorInputs *operatorinputs)
{
	// TODO Auto-generated constructor stub
	m_shootermotor = new CANTalon (CAN_SHOOTER_MOTOR);
	m_inputs = operatorinputs;
	m_feedmotor = new Talon(1);
}

Shooter::~Shooter()
{
	// TODO Auto-generated destructor stub
	delete m_shootermotor;
	delete m_feedmotor;

}

void Shooter::Init()
{
	m_shootermotor->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
	m_shootermotor->SetControlMode(CANSpeedController::ControlMode::kSpeed);
	//m_shootermotor->SetControlMode(CANSpeedController::ControlMode::kPercentVbus);
	m_shootermotor->SetPID(CAN_SHOOTER_P, CAN_SHOOTER_I, CAN_SHOOTER_D, CAN_SHOOTER_F);
	m_shootermotor->ConfigEncoderCodesPerRev(CAN_SHOOTER_ENCODER_TICKS);
	m_shootermotor->ClearIaccum();
	m_shootermotor->EnableControl();
	m_shootermotor->Enable();
	SmartDashboard::PutNumber("DB/Slider 0", SD_SHOOTER_SLIDER_DEFAULT);
	m_feedmotor->Set(0);

}

void Shooter::Stop()
{
	m_shootermotor->Disable();
	//m_shootermotor->DisableControl();
}

void Shooter::Loop()
{
	bool shootertogglebutton = m_inputs->joystickTrigger(OperatorInputs::ToggleChoice::kToggle);
	SmartDashboard::PutString("DB/String 1", std::to_string(shootertogglebutton));
	double slidervalue = SmartDashboard::GetNumber("DB/Slider 0", SD_SHOOTER_SLIDER_DEFAULT);
	//double newrpm = (slidervalue - SD_SHOOTER_SLIDER_DEFAULT) * (1.0 / 2.5);
	double newrpm = (slidervalue - SD_SHOOTER_SLIDER_DEFAULT) * SHOOTER_SLIDER_TO_RPM;
	//m_feedmotor->Set(newrpm);
	m_shootermotor->Set(newrpm);
	SmartDashboard::PutString("DB/String 0", "Input RPM: " + std::to_string(newrpm));
	double encodervalue = m_shootermotor->GetSpeed();
	SmartDashboard::PutString("DB/String 5", "Output RPM: " + std::to_string(encodervalue));
	SmartDashboard::PutString("DB/String 6", std::to_string(encodervalue));
	double velocity = encodervalue * 2 * 3.14159265359 * SHOOTER_RADIUS * (1/60.0); //60 secs per minute
	SmartDashboard::PutString("DB/String 8", "Velocity: " + std::to_string(velocity));
	double outputvoltage = m_shootermotor->GetOutputVoltage();
	SmartDashboard::PutString("DB/String 2", "Output Voltage: "+ std::to_string(outputvoltage));
	if (shootertogglebutton)
	{
		m_shootermotor->Set(newrpm);
	}
}
