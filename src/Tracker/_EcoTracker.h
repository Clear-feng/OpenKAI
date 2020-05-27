/*
 * _EcoTracker.h
 *
 *  Created on: Aug 21, 2015
 *      Author: yankai
 */

#ifndef OpenKAI_src_Tracker__EcoTracker_H_
#define OpenKAI_src_Tracker__EcoTracker_H_

#include "../Base/_ThreadBase.h"

#ifdef USE_OPENCV
#ifdef USE_OPENTRACKER
#include "../Vision/_VisionBase.h"
#include "_TrackerBase.h"


#include "eco.hpp"
using namespace eco;

namespace kai
{

class _EcoTracker: public _TrackerBase
{
public:
	_EcoTracker();
	virtual	~_EcoTracker();

	bool init(void* pKiss);
	bool start(void);
	int check(void);

private:
	void track(void);
	void update(void);
	static void* getUpdateThread(void* This)
	{
		((_EcoTracker*) This)->update();
		return NULL;
	}

public:
    ECO m_eco;
	EcoParameters m_param;

};

}
#endif
#endif
#endif
