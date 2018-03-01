#ifndef _FILE_H
#define _FILE_H

void writeLog(int pType, double * pCurrentInfo, double * pThreshold, char * pSystemError, char * pLogFile);
void readConfigFile(float * pCPU, float * pMEM, float * pSYNN, char * plogFilePath);


#endif
