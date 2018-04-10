#ifndef __MULALARM_H__
#define __MULALARM_H__

#include <time.h>
#include "ev.h"

typedef struct alarm{
	ev_periodic timer;
	struct tm timeLocal;
	struct alarm* pNext;
}ALARM;

void alarmInit();
void alarmAdd(EV_P_ ev_periodic* alarmSet,struct tm timeSet);

#endif

