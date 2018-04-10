#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ev.h"
#include "MulAlarm.h"

static void cbClock(EV_P_ ev_periodic* w,int revents){
	puts("\n**********Notification**********");
	//ev_break(EV_A_ EVBREAK_ONE);
}

void alarmInit(){
}

void alarmAdd(EV_P_ ev_periodic* alarmSet,struct tm timeSet){
	ev_periodic_init(alarmSet,cbClock,(double)mktime(&timeSet),0,0);
	ev_periodic_start(loop,alarmSet);
	printf("Alarm is set at %s\n",asctime(&timeSet));
}

