/*
 * Robot.h
 *
 *  Created on: Feb 18, 2016
 *      Author: eacobb
 */

#ifndef SRC_ROBOT_H_
#define SRC_ROBOT_H_


#include "WPILib.h"
#include "OperatorInputs.h"
#include "const.h"
#include "drivetrain.h"
#include "compressor.h"
#include "camera.h"
#include "climber.h"
#include "rangefinder.h"
#include "shooter.h"

using namespace std;
using namespace frc;


class Robot: public IterativeRobot
{
private:
	// live window variables
	LiveWindow *m_lw;
	//SendableChooser *m_chooser;
	string m_autonamedefault;
	string m_autonamecustom;
	string m_autoselected;

	OperatorInputs *m_inputs;
	Drivetrain *m_drivetrain;
	Compressor *m_compressor;
	Camera *m_camera;
	Climber *m_climber;
	RangeFinder *m_rangefinder;
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
