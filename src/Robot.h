/**
 *  Robot.h
 *  Date:
 *  Last Edited By:
 */

#ifndef SRC_ROBOT_H_
#define SRC_ROBOT_H_


#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>


#include "const.h"
#include "operatorinputs.h"
#include "drivetrain.h"
#include "DriveAngle.h"
#include "compressor.h"
#include "camera.h"
#include "autonomous.h"
#include "climber.h"
#include "picker.h"
#include "shooter.h"
#include "Flipper.h"
#include <ntCore.h>
#include <VisionTarget.h>

using namespace std;
using namespace frc;


class Robot: public IterativeRobot
{
private:

	// live window variables
	LiveWindow *m_lw;
	SendableChooser<string> m_chooser;
	string m_chooserselected;
	Auto m_autoselected;
	OperatorInputs *m_inputs;
	Drivetrain *m_drivetrain;
	DriveAngle *m_driveangle;
	Compressor *m_compressor;
	Camera *m_camera;
	Autonomous *m_autonomous;
	Climber *m_climber;
	Picker *m_picker;
	Shooter *m_shooter;
	Flipper *m_flipper;
	std::shared_ptr<NetworkTable> m_netTable;
	//std::shared_ptr<NetworkTable> m_netTable2;

	VisionTarget *m_visiontarget;

	enum Test {foHigh, foLow, baHigh, baLow, done};
	Test test;

	virtual void RobotInit();
	virtual void AutonomousInit();
	virtual void AutonomousPeriodic();
	virtual void TeleopInit();
	virtual void TeleopPeriodic();
	virtual void TestInit();
	virtual void TestPeriodic();
	virtual void DisabledInit();

	Auto Chooser2Auto(string selected);

	void Driving();
};


#endif /* SRC_ROBOT_H_ */
