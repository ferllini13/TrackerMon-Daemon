#include <syslog.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
//#include <syslog.h>
#include "./include/stats.h"
#include "./include/File.h"

int main(){
	int count;
	double pCPU;
	double pMem;
	double pSYN;
	char log[100];
	
	readConfigFile(&pCPU, &pMem, &pSYN, (char*)log);

	while (1) {
		checkCpu(pCPU, log);
		checkMem(pMem,log);
		checkSyn(pSYN,log);
		
		getSyslogStat(&count,log);
		sleep(1);
	}
	
	return EXIT_SUCCESS;
}