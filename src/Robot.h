/*
 * Robot.h
 *
 *  Created on: Feb 18, 2016
 *      Author: eacobb
 */

#ifndef SRC_ROBOT_H_
#define SRC_ROBOT_H_


#include <WPILib.h>
#include "OperatorInputs.h"
#include "const.h"
#include "drivetrain.h"
#include "shooter.h"

using namespace std;


class Robot: public IterativeRobot
{
private:
	// live window variables
	LiveWindow *m_lw;
	string m_autonamedefault;
	string m_autonamecustom;
	string m_autoselected;

	OperatorInputs *m_inputs;
	Drivetrain *m_drivetrain;
	Shooter *m_shooter;


	virtual void RobotInit();
	virtual void AutonomousInit();
	virtual void AutonomousPeriodic();
	virtual void TeleopInit();
	virtual void TeleopPeriodic();
	virtual void TestInit();
	virtual void TestPeriodic();
	virtual void DisabledInit();
};


#endif /* SRC_ROBOT_H_ */
