// TimerTest.h


#ifndef SRC_TIMERTEST_H_
#define SRC_TIMERTEST_H_


#include <timer.h>


using namespace frc;


class TimerTest
{
public:
	TimerTest();
	~TimerTest();
	void Init();
	void Loop();
	void Stop();

protected:
	Timer *m_timer;
};


#endif /* SRC_TIMERTEST_H_ */
