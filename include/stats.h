#ifndef _STATS_H
#define _STATS_H

double getCPUStat();
double getMemStat();
int getSynStat();
void getSyslogStat(int * criticalCount, char*logfile);

void checkCpu(double cpuThreshold, char*logfile);
void checkMem(double memThreshold, char*logfile);
void checkSyn(int synThreshold, char*logfile);
#endif
