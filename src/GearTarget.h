/**
 *  GearTarget.h
 *  Date:
 *  Last Edited By:
 */

#ifndef GEARTARGET_H_
#define GEARTARGET_H_

#include "DriveAngle.h"
#include "Drivetrain.h"
#include <ntCore.h>
#include "OperatorInputs.h"

class GearTarget {
public:
	GearTarget(std::shared_ptr<NetworkTable> newTable, DriveAngle *newAngle, OperatorInputs *newoi);
	void Init();
	void Loop();
	void Stop();
	void TargetGear();
	virtual ~GearTarget();
	void Enable();
	void Disable();
private:
	int m_prevCounter;
	int m_counter;
	double m_xDegree;
	DriveAngle* m_driveangle;
	enum Stage {stopped, read, targeting};
	std::shared_ptr<NetworkTable> m_nettable;
	Stage m_stage;
	OperatorInputs * m_inputs;
	bool m_isActive;
};

#endif /* GEARTARGET_H_ */
