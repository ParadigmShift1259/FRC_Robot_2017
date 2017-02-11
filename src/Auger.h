// Auger.h


#ifndef AUGER_H_
#define AUGER_H_

#include <Spark.h>
#include <Timer.h>
#include "Const.h"


using namespace frc;


class Auger
{
public:
	Auger();
	virtual ~Auger();
	void RunAuger();
	void StopAuger();
	void PulseAuger();
	void InitPulse();

protected:
	Spark *m_augermotor;
	Timer *m_augertimer;
	bool m_augeron; //Returns if the Auger is on or not
	double m_timetillchange; //Time until the Auger changes direction

};

#endif /* AUGER_H_ */
