#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ev.h"
#include "MulAlarm.h"

static void cbClock(EV_P_ ev_periodic* w,int revents){
	puts("\n**********Notification**********\nNew[n]  List[l]  Delete[d]  Modify[m]  Quit[q]");
}

time_t timeSet(void){
	struct tm tmSet;
	scanf("%d/%d/%d-%d:%d:%d",&tmSet.tm_year,&tmSet.tm_mon,&tmSet.tm_mday,&tmSet.tm_hour,&tmSet.tm_min,&tmSet.tm_sec);
	getchar();
	tmSet.tm_mon--;
	tmSet.tm_year -= 1900;
	return mktime(&tmSet);
}

void alarmList(ALARM* pAlarmList){
	ALARM* pAlarmRead = pAlarmList;
	if(!pAlarmRead) puts("\nThere is no alarm");
	else puts("\nAlarm List\nNo.\tTime");
	unsigned int numAlarm = 0;
	while(pAlarmRead){
		printf("%u\t%s",++numAlarm,ctime(&pAlarmRead->time));
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
	ev_periodic_start(EV_A_ &pAlarmNew->alarmSet);
	printf("Alarm is set at %s",ctime(&timeSet));
}

void alarmDel(EV_P_ ALARM** pAlarmList,unsigned int numRm){
	if(!numRm) return;
	ALARM* pAlarmRm = *pAlarmList;
	ALARM* pAlarmRmPv;
	unsigned int posRm = numRm;
	while(pAlarmRm && --posRm){
		pAlarmRmPv = pAlarmRm;
		pAlarmRm = pAlarmRm->pNext;
	}
	if(pAlarmRm){
		if(--numRm) pAlarmRmPv->pNext = pAlarmRm->pNext;
		else *pAlarmList = pAlarmRm->pNext;
		ev_periodic_stop(EV_A_ &pAlarmRm->alarmSet);
		free(pAlarmRm);
	}
}

void alarmMod(EV_P_ ALARM** pAlarmList,unsigned int numRm,time_t timeSet){
	alarmDel(EV_A_ pAlarmList,numRm);
	alarmAdd(EV_A_ pAlarmList,timeSet);
}

