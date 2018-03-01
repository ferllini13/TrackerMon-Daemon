#ifndef _FILE_H
#define _FILE_H

void writeLog(int pType, double * pCurrentInfo, double * pThreshold, char * pSystemError, char * pLogFile);
void readConfigFile(double * pCPU, double * pMEM, double * pSYNN, char * pLogFilePath);


#endif
