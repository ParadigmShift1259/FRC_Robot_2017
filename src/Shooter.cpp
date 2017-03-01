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

Shooter::Shooter(OperatorInputs *operatorinputs) {
	m_inputs = operatorinputs;
	m_shootermotor = new CANTalon(CAN_SHOOTER_MOTOR);
	m_feedmotor = new CANTalon(CAN_FEED_MOTOR);
	m_lowrpm = SHOOTER_LOW_RPM;
	m_shootrpm = SHOOTER_SHOOT_RPM;
	m_ramprpm = 0;
	m_shoot = false;
	m_rampdown = false;
	m_feedvoltage = 9;
	m_P = CAN_SHOOTER_P;
	m_I = CAN_SHOOTER_I;
	m_D = CAN_SHOOTER_D;
	m_F = CAN_SHOOTER_F;
	m_prevshootrpm = 0;
	m_2prevshootrpm = 0;
}

Shooter::~Shooter() {
	delete m_shootermotor;
	delete m_feedmotor;
}

void Shooter::Init() {
	m_lowrpm = SHOOTER_LOW_RPM;
	m_shootrpm = SHOOTER_SHOOT_RPM;
	m_ramprpm = 0;
	m_shoot = false;
	m_rampdown = false;
	m_timer.Stop();
	m_timer.Reset();
	SmartDashboard::PutNumber("SH00_P", m_P);
	SmartDashboard::PutNumber("SH00_I", m_I);
	SmartDashboard::PutNumber("SH00_D", m_D);
	SmartDashboard::PutNumber("SH00_F", m_F);
	m_P = SmartDashboard::GetNumber("SH00_P", m_P);
	m_I = SmartDashboard::GetNumber("SH00_I", m_I);
	m_D = SmartDashboard::GetNumber("SH00_D", m_D);
	m_F = SmartDashboard::GetNumber("SH00_D", m_F);

	m_shootermotor->ConfigNeutralMode(
			CANSpeedController::NeutralMode::kNeutralMode_Coast);
	m_shootermotor->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
	m_shootermotor->SetControlMode(CANSpeedController::ControlMode::kSpeed);
	//m_shootermotor->SetControlMode(CANSpeedController::ControlMode::kVoltage);
	m_shootermotor->SetPID(m_P, m_I, m_D, m_F);
	m_shootermotor->SetSensorDirection(true);
	m_shootermotor->ConfigEncoderCodesPerRev(CAN_SHOOTER_ENCODER_TICKS);
	m_shootermotor->ClearIaccum();
	m_shootermotor->SetCloseLoopRampRate(SHOOTER_RAMP_RATE);
	m_shootermotor->Enable();
	m_shootermotor->Set(m_lowrpm);

	m_feedmotor->SetFeedbackDevice(CANTalon::FeedbackDevice::QuadEncoder);
	m_feedmotor->SetControlMode(CANSpeedController::ControlMode::kVoltage);
	m_feedmotor->ConfigEncoderCodesPerRev(CAN_SHOOTER_ENCODER_TICKS);
	m_feedmotor->Set(0);

	if (SHOOTER_DIRECTION == 1){
		m_feedmotor->ConfigPeakOutputVoltage(+12.0,+0.0);
	} else if (SHOOTER_DIRECTION == -1) {
		m_feedmotor->ConfigPeakOutputVoltage(-0.0,-12.0);
	} else {
		m_feedmotor->ConfigPeakOutputVoltage(+0.0,-0.0);
	}

	SmartDashboard::PutString("SH99_FeedStatus", "");
}

void Shooter::Stop() {
	m_feedmotor->Set(0);
	m_shootermotor->Disable();
	m_shoot = false;
	m_timer.Stop();
	m_timer.Reset();
}

void Shooter::Loop() {
	m_P = SmartDashboard::GetNumber("SH00_P", m_P);
	m_I = SmartDashboard::GetNumber("SH00_I", m_I);
	m_D = SmartDashboard::GetNumber("SH00_D", m_D);

	m_shootermotor->SetP(m_P);
	m_shootermotor->SetI(m_I);
	m_shootermotor->SetD(m_D);

	double shootrpm = m_shootermotor->GetSpeed() * SHOOTER_DIRECTION;
	double feedrpm = m_feedmotor->GetSpeed();
	double feedcurrent = m_feedmotor->GetOutputCurrent(); // * FEEDER_DIRECTION;
	double shootvoltage = m_shootermotor->GetOutputVoltage() * FEEDER_DIRECTION;
	bool shooterbutton = m_inputs->xBoxLeftBumper();
	bool shooterrpmup = m_inputs->xBoxDPadUp(
			OperatorInputs::ToggleChoice::kHold);
	bool shooterrpmdown = m_inputs->xBoxDPadDown(
			OperatorInputs::ToggleChoice::kHold);
	bool feedrpmup = m_inputs->xBoxDPadRight(
			OperatorInputs::ToggleChoice::kHold);
	bool feedrpmdown = m_inputs->xBoxDPadLeft(
			OperatorInputs::ToggleChoice::kHold);
	static bool feedjammed = false;
	double feedpos = m_feedmotor->GetPosition();
	static double feedjampos = 0;

	SmartDashboard::PutNumber("SH01_shooter_rpm", shootrpm);
	SmartDashboard::PutNumber("SH02_feeder_rpm", feedrpm);
	SmartDashboard::PutNumber("SH03_shootvolt", shootvoltage);
	SmartDashboard::PutNumber("SH04_feedcurr", feedcurrent);
	SmartDashboard::PutNumber("SH05_Is_Shooting", m_shoot);
	SmartDashboard::PutNumber("SH06_Error",
			m_shootermotor->GetClosedLoopError());

	if (shooterbutton) {
		m_shoot = !m_shoot;
		if (m_shoot) {
			m_shootermotor->Set(m_shootrpm * SHOOTER_DIRECTION);
			m_rampdown = false;
		} else {
			//m_shootermotor->Set(m_lowrpm * SHOOTER_DIRECTION);
			m_rampdown = true;
			m_ramprpm = m_shootrpm;
		}
	}

	if (shooterrpmup) {
		if (m_shoot)
			m_shootermotor->Set(++m_shootrpm * SHOOTER_DIRECTION);
		else
			m_shootermotor->Set(++m_lowrpm * SHOOTER_DIRECTION);
	}
	if (shooterrpmdown) {
		if (m_shoot)
			m_shootermotor->Set(--m_shootrpm * SHOOTER_DIRECTION);
		else
			m_shootermotor->Set(--m_lowrpm * SHOOTER_DIRECTION);
	}
	switch (m_feedmotor->IsSensorPresent(CANTalon::FeedbackDevice::QuadEncoder)) {
		case CANTalon::FeedbackDeviceStatus::FeedbackStatusPresent:
			SmartDashboard::PutString("SH99_FeedStatus", "Present");
			break;
		case CANTalon::FeedbackDeviceStatus::FeedbackStatusNotPresent:
			SmartDashboard::PutString("SH99_FeedStatus", "NotPresent");
			break;
		case CANTalon::FeedbackDeviceStatus::FeedbackStatusUnknown:
			SmartDashboard::PutString("SH99_FeedStatus", "Unknown");
			break;
	}

	if (m_shoot) {
		if (!feedjammed && (abs(shootrpm - m_shootrpm) < (SHOOTER_ABS_ERROR))) {
			if (feedrpmup) {
				m_feedvoltage += 0.01;
			}
			if (feedrpmdown) {
				m_feedvoltage -= 0.01;

			}

			m_feedmotor->Set(m_feedvoltage * FEEDER_DIRECTION);
		} else if (!feedjammed) {
			m_feedmotor->Set(0);
		}
		/**
		 //error 1, feedmotor speed is constantly reset to -6.5 volts
		 if (!feedjammed && (abs(shootrpm - m_shootrpm) < (SHOOTER_ERROR_RPM * m_shootrpm))
		 	 	 && (abs(m_prevshootrpm - m_shootrpm) < (SHOOTER_ERROR_RPM * m_shootrpm))
		 	 	 && (abs(m_2prevshootrpm - m_shootrpm) < (SHOOTER_ERROR_RPM * m_shootrpm)))
		 {
		 	 if (feedrpmup)
		 	 	 m_feedvoltage += 0.01;

		 	 if (feedrpmdown)
		 	 	 m_feedvoltage -= 0.01;

		 	 m_feedmotor->Set(m_feedvoltage * FEEDER_DIRECTION);
		 }
		 bool jamtest = false;//(m_feedmotor->IsSensorPresent(CANTalon::FeedbackDevice::QuadEncoder) == CANTalon::FeedbackDeviceStatus::FeedbackStatusUnknown) ?
		 //(abs(feedrpm) < 5) : false;
		 if (!feedjammed && (abs(m_feedmotor->Get()) > 0) && jamtest)
		 {
		 	 feedjammed = true;
		 	 feedjampos = feedpos;
		 	 m_timer.Start();
		 }
		 else if(feedjammed)
		 {
		 if ((abs(feedpos-feedjampos) < 0.5) && !(m_timer.HasPeriodPassed(0.5)))
		 {
		 m_feedmotor->Set(-m_feedvoltage * FEEDER_DIRECTION);
		 }
		 else
		 {
		 feedjammed = false;
		 }
		 }
		 else
		 {
		 m_timer.Stop();
		 m_timer.Reset();
		 }
		 */
	} else {
		m_feedmotor->Set(0);
		m_shootermotor->Set(SHOOTER_LOW_RPM * SHOOTER_DIRECTION);
	}

	m_2prevshootrpm = m_prevshootrpm;
	m_prevshootrpm = shootrpm;
}
