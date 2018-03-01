#include <syslog.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "./include/stats.h"
#include "./include/service.h"

int main(int argc, char *argv[]) {
	openlog("Trackermon", LOG_PID, LOG_DAEMON);
	while (1) {
		syslog(LOG_NOTICE, "Prueba");
		sleep(20);
	}
	closelog();

	return EXIT_SUCCESS;
}