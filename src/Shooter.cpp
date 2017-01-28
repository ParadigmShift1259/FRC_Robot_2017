/*
 * Shooter.cpp
 *
 *  Created on: Jan 14, 2017
 *      Author: Developer
 */

#include <Shooter.h>
#include <const.h>

Shooter::Shooter() {
	// TODO Auto-generated constructor stub
	m_CANTalon = new CANTalon (PWM_SHOOTER_MOTOR);

}

Shooter::~Shooter() {
	// TODO Auto-generated destructor stub
	delete m_CANTalon;

}

void Shooter::Init() {
	m_CANTalon->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
	m_CANTalon->SetControlMode(CANSpeedController::ControlMode::kSpeed);
	m_CANTalon->SetPID(PWM_SHOOTER_P, PWM_SHOOTER_I, PWM_SHOOTER_D);

}
