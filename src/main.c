#include <stdio.h>
#include <math.h>
#include <time.h>
#include "ev.h"
#include "MulAlarm.h"

struct ev_loop* pAlarmLoop;
ev_io inputSet;
ALARM* pAlarmList = 0;

static void cbCmd(EV_P_ ev_io* w,int revents){
	char cmd = getchar();
	getchar();
	if(cmd == 'n' || cmd == 'N'){
		puts("\nAlarm Setting");
		struct tm tmSet;
		scanf("%d/%d/%d-%d:%d:%d",&tmSet.tm_year,&tmSet.tm_mon,&tmSet.tm_mday,&tmSet.tm_hour,&tmSet.tm_min,&tmSet.tm_sec);
		getchar();
		tmSet.tm_mon--;
		tmSet.tm_year -= 1900;
		alarmAdd(pAlarmLoop,&pAlarmList,mktime(&tmSet));
	}
	else if(cmd == 'l' || cmd == 'L'){
		alarmList(pAlarmList);
	}
	else if(cmd == 'd' || cmd == 'D'){
	}
	else if(cmd == 'q' || cmd == 'Q'){
		ev_break(EV_A_ EVBREAK_ALL);
	}
	else{
		puts("\nInvalid Command");
	}
	puts("\nNew[n]\t\tList[l]\t\tDelete[d]\t\tQuit[q]");
}

int main(){
	pAlarmLoop = EV_DEFAULT;
	ALARM test;
	
	ev_io_init(&inputSet,cbCmd,0,EV_READ);
	ev_io_start(pAlarmLoop,&inputSet);
	
	puts("\nWelcome to MulAlarm!\nNew[n]\t\tList[l]\t\tDelete[d]\t\tQuit[q]");
	ev_run(pAlarmLoop,0);
	
	return 0;
}

