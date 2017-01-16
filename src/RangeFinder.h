// rangefinder.h


#ifndef RANGEFINDER_H_
#define RANGEFINDER_H_


#include <ultrasonic.h>


class RangeFinder
{
public:
	RangeFinder();
	~RangeFinder();
	void Init();
	void Loop();

protected:
	Ultrasonic *m_ultrasonic;
};


#endif /* RANGEFINDER_H_ */
