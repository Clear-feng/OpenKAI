/*
 * ZED.h
 *
 *  Created on: Aug 22, 2015
 *      Author: yankai
 */

#ifndef SRC_VISION_ZED_H_
#define SRC_VISION_ZED_H_

#include "../Base/common.h"
#include "_VisionBase.h"
#include "../Utility/util.h"

#ifdef USE_ZED
#include <sl/Camera.hpp>
#include <sl/Core.hpp>
#include <sl/defines.hpp>
#include <opencv2/core/eigen.hpp>

namespace kai
{

enum tracking_status
{
	track_idle, track_start, tracking, track_stop
};

class _ZED: public _VisionBase
{
public:
	_ZED();
	virtual ~_ZED();

	bool init(void* pKiss);
	bool link(void);
	bool start(void);
	bool draw(void);

	double dist(Rect* pR);

	void startTracking(void);
	void stopTracking(void);
	void setAttitude(vDouble3* pYPR);
	bool isTracking(void);
	int getMotionDelta(vDouble3* pT, vDouble3* pR, uint64_t* pDT);

	vDouble2 range(void);

private:
	GpuMat slMat2cvGpuMat(sl::Mat& input);
	void zedTrackReset(void);
	bool open(void);
	void update(void);
	static void* getUpdateThread(void* This)
	{
		((_ZED *) This)->update();
		return NULL;
	}

public:
	sl::Camera* m_pZed;
	sl::RuntimeParameters m_zedRuntime;
	sl::SENSING_MODE m_zedSenseMode;
	sl::TRACKING_STATE m_zedTrackState;
	int m_zedResolution;
	int m_zedFPS;
	int m_zedDepthMode;
	bool m_bZedFlip;
	double m_zedMinDist;
	double m_zedMaxDist;
	int m_zedConfidence;

	sl::Mat* m_pzImg;
	sl::Mat* m_pzDepth;
	GpuMat m_gImg;
	GpuMat m_gImg2;
	GpuMat m_gDepth;
	GpuMat m_gDepth2;

	tracking_status m_trackState;
    Eigen::Matrix4f m_mMotion;
    vDouble3 m_vT;
    vDouble3 m_vR;
    int	m_trackConfidence;
    uint64_t m_tLastTrack;

	Window* m_pDepthWin;

};

}

#endif
#endif
