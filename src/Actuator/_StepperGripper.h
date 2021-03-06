/*
 * _StepperGripper.h
 *
 *  Created on: June 22, 2020
 *      Author: yankai
 */

#ifndef OpenKAI_src_Actuator__StepperGripper_H_
#define OpenKAI_src_Actuator__StepperGripper_H_

#include "_DRV8825_RS485.h"

namespace kai
{

class _StepperGripper: public _DRV8825_RS485
{
public:
	_StepperGripper();
	~_StepperGripper();

	bool init(void* pKiss);
	bool start(void);
	void draw(void);

	void grip(bool bOpen);

private:
	void updateGripper(void);
	void update(void);
	static void* getUpdateThread(void* This)
	{
		((_StepperGripper*) This)->update();
		return NULL;
	}

public:
	bool m_bState;
	bool m_bOpen;

};

}
#endif
