/**
 *  VisionTarget.cpp
 *  Date:
 *  Last Edited By:
 */

#include "VisionTarget.h"

VisionTarget::VisionTarget(std::shared_ptr<NetworkTable> newTable,
		DriveAngle * newAngle, OperatorInputs *oi) {
	// TODO Auto-generated constructor stub
	m_nettable = newTable;
	m_driveangle = newAngle;
	m_shootercounter = 0;
	m_gearcounter = 0;
	m_targetinggear = false;
	m_targetingshooter = false;
	m_inputs = oi;
}

void VisionTarget::Init() {
	m_targetinggear = false;
	m_targetingshooter = false;
	m_driveangle->Stop();
}

void VisionTarget::Loop() {
	SmartDashboard::PutBoolean("VT_00_GearImageFound",
			m_nettable->GetNumber("gear/counter", 0) != m_gearcounter);
	SmartDashboard::PutBoolean("VT_00_ShooterImageFound",
			m_nettable->GetNumber("shooter/counter", 0) != m_shootercounter);
	SmartDashboard::PutBoolean("VT_01_TargetingGear", m_targetinggear);
	SmartDashboard::PutBoolean("VT_01_TargetingShooter", m_targetingshooter);
	SmartDashboard::PutNumber("VT_02_TargetingGear", m_targetinggear);
	SmartDashboard::PutNumber("VT_02_GearXSpread",
			m_nettable->GetNumber("gear/xSpread", 0));
	SmartDashboard::PutNumber("VT_02_ShooterXSpread",
			m_nettable->GetNumber("shooter/xSpread", 0));
	SmartDashboard::PutBoolean("VT_03_PIDEnabled", m_driveangle->IsEnabled());
	//if(m_isActive && !m_driveangle->IsEnabled())
	//m_driveangle->EnableAnglePID();

	if (m_inputs->xBoxRightBumper()) {
		m_driveangle->Stop();
		m_targetingshooter = false;
		m_targetinggear = !m_targetinggear;
		if (m_targetinggear) {
			m_driveangle->EnableAnglePID();
			m_driveangle->SetToCurrentAngle();
		}
	} else if (m_inputs->xBoxAButton()) {
		m_targetinggear = false;
		m_driveangle->Stop();
		m_targetingshooter = !m_targetingshooter;
		if (m_targetingshooter) {
			m_driveangle->EnableAnglePID();
			m_driveangle->SetToCurrentAngle();
		}
	} else if (m_inputs->xBoxBButton()) {
		m_driveangle->Stop();
		m_targetingshooter = false;
		m_targetinggear = false;
	}
	if (!m_driveangle->IsEnabled())
		m_driveangle->RunNormalDrive();
	else if (!m_driveangle->IsHighGear())
		m_driveangle->Shift();

	if (m_targetinggear) {
		m_driveangle->Drive(m_inputs->xBoxLeftY(), true);
		TargetGear();
	} else {
		m_gearcounter = m_nettable->GetNumber("gear/counter", 0);
	}

	if (m_targetingshooter) {
		m_driveangle->Drive(m_inputs->xBoxLeftY(), true);
		TargetShooter();
		SmartDashboard::PutNumber("SH00_Target", ConvAreaToRPM(m_nettable->GetNumber("shooter/area",500)));
	} else {
		m_shootercounter = m_nettable->GetNumber("shooter/counter", 0);
	}
}

void VisionTarget::TargetGear() {
	if (m_nettable->GetNumber("gear/counter", 0) != m_gearcounter) {
		m_gearcounter = m_nettable->GetNumber("gear/counter", 0);
		// todo change the subtract value, it's the angle info, the divisor is how fast it turns (making it larger is slower)
		double m_xDegree = ((m_nettable->GetNumber("gear/xPos", 0) - 27.0) / 18);
		// the multiplier is how sensitive arcing is
		int areaDegree = (m_nettable->GetNumber("gear/areaDifference", 0) * 50);
		// capping of the arcing, change higher to arc more at maximum
		areaDegree =
				(abs(areaDegree) > 6) ? (areaDegree > 0 ? 6 : -6) : areaDegree;
		// the number is the distance to stop arcing in the spread of the x values of the contours
		areaDegree =
				(m_nettable->GetNumber("gear/xSpread", 0) > 180) ?
						0 : areaDegree;
		m_driveangle->SetVisionAngle((m_xDegree + areaDegree));
	}
}

void VisionTarget::TargetShooter() {
	if (m_nettable->GetNumber("shooter/counter", 0) != m_shootercounter) {
		m_gearcounter = m_nettable->GetNumber("shooter/counter", 0);
		// todo change the subtract value, it's the angle info, the divisor is how fast it turns (making it larger is slower)
		double m_xDegree = ((m_nettable->GetNumber("shooter/xPos", 0) - 0) / 10);
		m_driveangle->SetVisionAngle((-m_xDegree));
	}
}

/**
 * Calculated transfer function from experimental data
 */
double VisionTarget::ConvAreaToRPM(double area) {
	double rpm = 3634.854683 + (-26.16295573 * area)
			+ (0.097678298 * pow(area, 2)) + (-0.000177295 * pow(area, 3))
			+ (1.55298E-07 * pow(area, 4)) + (-5.26577E-11 * pow(area, 5));
	return rpm;
}

void VisionTarget::Stop() {
	m_targetinggear = 0;
	m_driveangle->Stop();
}

VisionTarget::~VisionTarget() {
}

