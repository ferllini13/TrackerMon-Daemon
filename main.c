#include "./include/stats.h"
 
int main(int argC,char* argV[]){
	int count =0;
	char * log="/home/ferllini13/Desktop/log";
	checkCpu(20.0, log);
	checkMem(20.0,log);
	checkSyn(100,log);
	getSyslogStat(&count,log);
	return 0;
}