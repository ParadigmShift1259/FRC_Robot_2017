/**
 *  VisionTarget.h
 *  Date:
 *  Last Edited By:
 */

#ifndef VISIONTARGET_H_
#define VISIONTARGET_H_

#include "DriveAngle.h"
#include "Drivetrain.h"
#include <ntCore.h>
#include "OperatorInputs.h"
#include <SmartDashboard/SmartDashboard.h>

class VisionTarget {
public:
	VisionTarget(std::shared_ptr<NetworkTable> newTable, DriveAngle *newAngle, OperatorInputs *newoi);
	void Init();
	void Loop();
	void Stop();
	void TargetGear();
	void TargetShooter();
	virtual ~VisionTarget();
private:
	double ConvAreaToRPM(double area);
	int m_gearcounter;
	int m_shootercounter;
	DriveAngle* m_driveangle;
	std::shared_ptr<NetworkTable> m_nettable;
	OperatorInputs * m_inputs;
	bool m_targetinggear;
	bool m_targetingshooter;
};

#endif /* VISIONTARGET_H_ */
