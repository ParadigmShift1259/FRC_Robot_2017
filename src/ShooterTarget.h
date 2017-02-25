/*
 * ShooterTarget.h
 *
 *  Created on: Feb 20, 2017
 *      Author: Developer
 */

#ifndef SRC_SHOOTERTARGET_H_
#define SRC_SHOOTERTARGET_H_

#include "DriveAngle.h"
#include "Drivetrain.h"
#include <ntCore.h>
#include "OperatorInputs.h"

class ShooterTarget {
public:
	ShooterTarget(std::shared_ptr<NetworkTable> newTable, DriveAngle *newAngle, OperatorInputs *newoi);
	void Init();
	void Loop(bool initonce = false);
	void Stop();
	virtual ~ShooterTarget();
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

#endif /* SRC_SHOOTERTARGET_H_ */
