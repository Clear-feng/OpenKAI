/*
 * _MotionDetector.cpp
 *
 *  Created on: Aug 4, 2018
 *      Author: yankai
 */

#include "_MotionDetector.h"

#ifdef USE_OPENCV
#ifdef USE_OPENCV_CONTRIB

namespace kai
{

_MotionDetector::_MotionDetector()
{
	m_pVision = NULL;
	m_algorithm = "";
	m_learningRate = -1;
}

_MotionDetector::~_MotionDetector()
{

}

bool _MotionDetector::init(void *pKiss)
{
	IF_F(!this->_DetectorBase::init(pKiss));
	Kiss *pK = (Kiss*) pKiss;

	pK->v<string>("algorithm", &m_algorithm);
	pK->v<double>("learningRate", &m_learningRate);

//	if(m_algorithm == "cnt")
//	{
//		m_pBS = cv::bgsegm::createBackgroundSubtractorCNT();
//	}
//	else if(m_algorithm == "gmg")
//	{
//		m_pBS = cv::bgsegm::createBackgroundSubtractorGMG();
//	}
//	else if(m_algorithm == "lsbp")
//	{
//		m_pBS = cv::bgsegm::createBackgroundSubtractorLSBP();
//	}
//	else if(m_algorithm == "mog")
//	{
//		m_pBS = cv::bgsegm::createBackgroundSubtractorMOG();
//	}
//	else
//	{
//		m_pBS = cv::bgsegm::createBackgroundSubtractorGSOC();
//	}
//

	string iName = "";
	F_ERROR_F(pK->v("_VisionBase", &iName));
	m_pVision = (_VisionBase*) (pK->getInst(iName));

	return true;
}

bool _MotionDetector::start(void)
{
	m_bThreadON = true;
	int retCode = pthread_create(&m_threadID, 0, getUpdateThread, this);
	if (retCode != 0)
	{
		m_bThreadON = false;
		return false;
	}

	return true;
}

void _MotionDetector::update(void)
{
	while (m_bThreadON)
	{
		this->autoFPSfrom();

		if (check() >= 0)
		{
			m_pU->updateObj();
			detect();
		}

		this->autoFPSto();
	}
}

int _MotionDetector::check(void)
{
	NULL__(m_pU, -1);
	NULL__(m_pV, -1);
	IF__(m_pV->BGR()->bEmpty(), -1);

	return 0;
}

void _MotionDetector::detect(void)
{
	Mat m = *m_pVision->BGR()->m();

	m_pBS->apply(m, m_mFG, m_learningRate);

	vector<vector<Point> > vContours;
	vector<Vec4i> vHierarchy;
	findContours(m_mFG, vContours, vHierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE,
			Point(0, 0));

	float kx = 1.0/m.cols;
	float ky = 1.0/m.rows;
	_Object o;
	for (int i = 0; i < vContours.size(); i++)
	{
		vector<Point> vContourPoly;
		approxPolyDP(Mat(vContours[i]), vContourPoly, 3, true);
		Rect r = boundingRect(Mat(vContourPoly));
		vContourPoly.clear();

		o.init();
		o.setTopClass(-1, 0);
		o.m_tStamp = m_tStamp;
		o.setBB2D(rect2BB < vFloat4 > (r));
		o.scale(kx,ky);

		m_pU->add(o);
	}
}

void _MotionDetector::draw(void)
{
	this->_DetectorBase::draw();
	IF_(!checkWindow());
	Mat *pM = ((Window*) this->m_pWindow)->getFrame()->m();

	if (!m_mFG.empty())
	{
		imshow(*this->getName(), m_mFG);
	}

}

}
#endif
#endif
