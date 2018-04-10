#include <stdio.h>
#include <math.h>
#include <time.h>
#include "ev.h"
#include "MulAlarm.h"

struct ev_loop* alarmLoop;
ev_io inputSet;
ev_periodic alarmSet;

static void cbCmd(EV_P_ ev_io* w,int revents){
	char cmd = getchar();
	getchar();
	if(cmd == 'n' || cmd == 'N'){
		puts("\nAlarm Setting");
		struct tm timeSet;
		scanf("%d/%d/%d-%d:%d:%d",&timeSet.tm_year,&timeSet.tm_mon,&timeSet.tm_mday,&timeSet.tm_hour,&timeSet.tm_min,&timeSet.tm_sec);
		getchar();
		timeSet.tm_year -= 1900;
		timeSet.tm_mon --;
		alarmAdd(alarmLoop,&alarmSet,timeSet);
	}
	else if(cmd == 'l' || cmd == 'L'){
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
	alarmLoop = EV_DEFAULT;
	ALARM test;
	
	ev_io_init(&inputSet,cbCmd,0,EV_READ);
	ev_io_start(alarmLoop,&inputSet);
	
	puts("\nWelcome to MulAlarm!\nNew[n]\t\tList[l]\t\tDelete[d]\t\tQuit[q]");
	ev_run(alarmLoop,0);
	
	return 0;
}

