#ifndef __MULALARM_H__
#define __MULALARM_H__

#include <time.h>
#include "ev.h"

typedef struct alarm{
	ev_periodic alarmSet;
	time_t time;
	struct alarm* pNext;
}ALARM;

void alarmList(ALARM* pAlarmList);
void alarmAdd(EV_P_ ALARM** pAlarmList,time_t timeSet);

#endif

