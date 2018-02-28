#include <syslog.h>
#include <unistd.h>
#include <getopt.h>
#include "./include/stats.h"
#include "./include/service.h"

int main(int argC,char* argV[]){
	daemonize();
	while (1) {
		syslog(LOG_NOTICE, "Trackermon started");
		sleep(30);
		break;
	}
	syslog (LOG_NOTICE, "Trackermon terminated.");
    closelog();

	return 0;
}