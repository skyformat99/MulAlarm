#include <stdio.h>
#include <time.h>
#include "ev.h"
#include "MulAlarm.h"

struct ev_loop* pAlarmLoop;
ev_io inputSet;
ALARM* pAlarmList = 0;

static void cbCmd(EV_P_ ev_io* w,int revents){
	char cmd = getchar();
	getchar();
	if(cmd == 'l' || cmd == 'L'){
		alarmList(pAlarmList);
	}
	else if(cmd == 'n' || cmd == 'N'){
		puts("\nAlarm Setting at...[yyyy/MM/dd-HH:mm:ss]");
		alarmAdd(pAlarmLoop,&pAlarmList,timeSet());
	}
	else if(cmd == 'd' || cmd == 'D'){
		unsigned int numRm;
		alarmList(pAlarmList);
		puts("\nWhich Alarm do you want to delete?[No.]");
		scanf("%u",&numRm);
		getchar();
		alarmDel(pAlarmLoop,&pAlarmList,numRm);
	}
	else if(cmd == 'm' || cmd == 'M'){
		unsigned int numEd;
		alarmList(pAlarmList);
		puts("\nWhich Alarm do you want to modify?[No.]");
		scanf("%u",&numEd);
		getchar();
		puts("\nAlarm Modify to...[yyyy/MM/dd-HH:mm:ss]");
		alarmMod(pAlarmLoop,&pAlarmList,numEd,timeSet());
	}
	else if(cmd == 'q' || cmd == 'Q'){
		ev_break(EV_A_ EVBREAK_ALL);
		return;
	}
	else{
		puts("\nInvalid Command");
	}
	puts("\nNew[n]  List[l]  Delete[d]  Modify[m]  Quit[q]");
}

int main(){
	pAlarmLoop = EV_DEFAULT;
	ALARM test;
	
	ev_io_init(&inputSet,cbCmd,0,EV_READ);
	ev_io_start(pAlarmLoop,&inputSet);
	
	puts("\nWelcome to MulAlarm!\nNew[n]  List[l]  Delete[d]  Modify[m]  Quit[q]");
	ev_run(pAlarmLoop,0);
	
	return 0;
}

