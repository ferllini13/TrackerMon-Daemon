#include <syslog.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "./include/stats.h"
#include "./include/File.h"

 
int main(){
	double pCPU;
	double pMem;
	double pSYN;
	char * log;

 	readConfigFile(&pCPU,&pMem, &pSYN,log);
 	printf("%s\n",log);

 	while (1) {
 		checkCpu(pCPU, log);

 		checkMem(pMem,log);
 		checkSyn(pSYN,log);
 		getSyslogStat(log);
 		sleep(5);
 	}
 	
 	return EXIT_SUCCESS;
}