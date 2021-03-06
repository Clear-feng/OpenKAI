/*
 * _GPhoto.cpp
 *
 *  Created on: Feb 20, 2020
 *      Author: yankai
 */

#include "_GPhoto.h"

#ifdef USE_OPENCV

namespace kai
{

_GPhoto::_GPhoto()
{
	m_type = vision_gphoto;
	m_threadMode = T_NOTHREAD;

	m_cmdUnmount = "gio mount -s gphoto2";
}

_GPhoto::~_GPhoto()
{
	close();
}

bool _GPhoto::init(void* pKiss)
{
	IF_F(!_VisionBase::init(pKiss));
	Kiss* pK = (Kiss*) pKiss;

	pK->v("mount", &m_cmdUnmount);

	return true;
}

bool _GPhoto::open(void)
{
	if(!m_cmdUnmount.empty())
		system(m_cmdUnmount.c_str());

	return true;
}

void _GPhoto::close(void)
{
	if(m_threadMode == T_THREAD)
	{
		goSleep();
		while(!bSleeping());
	}

	this->_VisionBase::close();
}

bool _GPhoto::start(void)
{
	IF_F(!this->_VisionBase::start());

	m_bThreadON = true;
	int retCode = pthread_create(&m_threadID, 0, getUpdateThread, this);
	if (retCode != 0)
	{
		m_bThreadON = false;
		return false;
	}

	return true;
}

void _GPhoto::update(void)
{
	while (m_bThreadON)
	{
		if (!m_bOpen)
		{
			if (!open())
			{
				this->sleepTime(USEC_1SEC);
				continue;
			}
		}

		this->autoFPSfrom();

		this->autoFPSto();
	}
}

bool _GPhoto::shutter(string& fName)
{
	return true;
}

}
#endif
