#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ev.h"
#include "MulAlarm.h"

static void cbClock(EV_P_ ev_periodic* w,int revents){
	puts("\n**********Notification**********");
	//ev_break(EV_A_ EVBREAK_ONE);
}

void alarmList(ALARM* pAlarmList){
	ALARM* pAlarmRead = pAlarmList;
	puts("\nAlarm List");
	while(pAlarmRead){
		printf("%s\n",ctime(&pAlarmRead->time));
		pAlarmRead = pAlarmRead->pNext;
	}
}

void alarmAdd(EV_P_ ALARM** pAlarmList,time_t timeSet){
	ALARM* pAlarmNew = (ALARM*)malloc(sizeof(ALARM));
	if(!pAlarmNew) puts("\nMemory is not enough");
	pAlarmNew->time = timeSet;
	if(*pAlarmList && timeSet > (*pAlarmList)->time){
		ALARM* pAlarmNewPv = *pAlarmList;
		pAlarmNew->pNext = (*pAlarmList)->pNext;
		while(pAlarmNew->pNext && timeSet > pAlarmNew->pNext->time){
			pAlarmNewPv = pAlarmNew->pNext;
			pAlarmNew->pNext = pAlarmNew->pNext->pNext;
		}
		pAlarmNewPv->pNext = pAlarmNew;
	}
	else{
		pAlarmNew->pNext = *pAlarmList;
		*pAlarmList = pAlarmNew;
	}
	ev_periodic_init(&pAlarmNew->alarmSet,cbClock,(double)timeSet,0,0);
	ev_periodic_start(loop,&pAlarmNew->alarmSet);
	printf("Alarm is set at %s\n",ctime(&timeSet));
}

