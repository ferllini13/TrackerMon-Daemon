#include <syslog.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "./include/stats.h"
 
int main(int argC,char* argV[]){
	int count =0;
	char * log="/home/ferllini13/Desktop/log";
	checkCpu(20.0, log);
	checkMem(20.0,log);
	checkSyn(100,log);
	getSyslogStat(&count,log);
	return 0;
/*int main(int argc, char *argv[]) {
	openlog("Trackermon", LOG_PID, LOG_DAEMON);
	while (1) {
		syslog(LOG_NOTICE, "Prueba");
		sleep(20);
	}
	closelog();

	return EXIT_SUCCESS;*/
}