#ifndef OpenKAI_src_Autopilot_AP__AP_GPS_H_
#define OpenKAI_src_Autopilot_AP__AP_GPS_H_

#include "../../../Filter/Median.h"
#include "../../../Navigation/Coordinate.h"
#include "../../../SLAM/_RStracking.h"
#include "../ArduPilot/_AP_base.h"

#ifdef USE_REALSENSE

namespace kai
{

class _AP_GPS: public _AutopilotBase
{
public:
	_AP_GPS();
	~_AP_GPS();

	bool init(void* pKiss);
	bool start(void);
	int check(void);
	void update(void);
	void draw(void);

	void reset(void);

protected:
	void updateGPS(void);
	static void* getUpdateThread(void* This)
	{
		((_AP_GPS *) This)->update();
		return NULL;
	}

public:
	_AP_base* m_pAP;
	_RStracking* m_pRS;
	Coordinate m_GPS;

	double	m_yaw;
	double	m_dYaw;

	LL_POS m_llPos;
	UTM_POS m_utmPos;
	LL_POS m_llOrigin;
	UTM_POS m_utmOrigin;
	bool	m_bUseApOrigin;

	mavlink_gps_input_t m_D;

};

}
#endif
#endif