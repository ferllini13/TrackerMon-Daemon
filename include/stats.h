#ifndef _STATS_H
#define _STATS_H

double getCPUStat();
double getMemStat();
int getSynStat();
void getSyslogStat(int * criticalCount);

void checkCpu();
void checkMem();
void checkSyn();
#endif
