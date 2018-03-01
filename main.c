#include <syslog.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "./include/stats.h"
#include "./include/service.h"

int main(int argc, char *argv[]){
	static struct option long_options[] = {
		{"daemon", no_argument, 0, 'd'},
		{"pid_file", required_argument, 0, 'p'},
		{NULL, 0, 0, 0}
	};

	char *pid_file_name = NULL;
	int value, option_index = 0;
	char *log_file_name = NULL;

	while ((value = getopt_long(argc, argv, "d:p:dh", long_options, &option_index)) != -1) {
		switch (value) {
			case 'd':
				daemonize(pid_file_name);
				break;
			case 'p':
				pid_file_name = malloc(sizeof(char) * strlen(optarg));
				pid_file_name = strdup(optarg);
				break;

		}
	}
	printf("Hola\n");
	if (pid_file_name != NULL) {
		free(pid_file_name);
	}

	/*daemonize();
	while (1) {
		syslog(LOG_NOTICE, "Trackermon started");
		sleep(30);
		break;
	}
	syslog (LOG_NOTICE, "Trackermon terminated.");
    closelog();*/

	return 0;
}