#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Method that write a log file
 * @details This method writes in the log file the different kind of alert messages
 * 
 * @param pType         Recieve the type of alert 0=CPU 1=Memory 2=SYN 3=System
 * @param pCurrentInfo  Recieve the current value for the alert
 * @param pThreshold    Recieve the threshold
 * @param pSystemError  Recieve the System Error
 * @param pLogFile      Recieve the Log File path
 */
void writeLog(int pType, double * pCurrentInfo, double * pThreshold, char * pSystemError, char * pLogFile){ //Recieve the information and logfile path
    FILE * pFile = fopen(pLogFile, "a"); //a read the file and append the info
    if (pFile == NULL) //Verify if the file is open
    {
            printf("Error opening file! %s", pLogFile);
            
    }
    else
    {
        switch(pType) // Type of alert 0=CPU 1=Memory 2=SYN 3=System
        {
            case 0  : //CPU
                fprintf(pFile, "[CRITICAL] – CPU Usage is currently %f which is over %f\n", *pCurrentInfo, *pThreshold); // Write the alert message in the log file
                fclose(pFile); // Close the file
                break;
        
            case 1  : //Memory
                fprintf(pFile, "[CRITICAL] – Memory Usage is currently %f which is over %f\n", *pCurrentInfo, *pThreshold); // Write the alert message in the log file
                fclose(pFile); // Close the file
                break;
        
            case 2  : //SYN
                fprintf(pFile, "[CRITICAL] – SYN flood connections detected. Currently there are %f active SYN_RECV connections which is over the defined limit %f\n", *pCurrentInfo, *pThreshold); // Write the alert message in the log file
                fclose(pFile); // Close the file
                break;
        
            case 3  : //System critical errors
                fprintf(pFile, "[CRITICAL] – System critical error has been detected: %s\n", pSystemError); // Write the system error in the log file
                fclose(pFile); // Close the file
                break;
        }
    }    
}

/**
 * @brief setting global variables
 */
#define CONFIG_FILE_NAME "/etc/trackermon/config.conf"

/**
 * @brief method that read a config file
 * @details this method read a config file and save it values into a struct
 * 
 * @param pfilename name of the config file to read
 */
void readConfigFile(double * pCPU, double * pMEM, double * pSYNN, char * pLogFilePath){
    FILE * fp;    

    fp = fopen(CONFIG_FILE_NAME, "r");
    if (fp == NULL){
        fclose(fp); 
        exit(EXIT_FAILURE);
    }
    else{
        char key[256], value[256];
        char * line = NULL;
        size_t len = 0;
        ssize_t read;

        while ((read = getline(&line, &len, fp)) != -1) {
            if(line[0] == '#' || line[0] == '\n')
                continue;
            else{
                sscanf(line, "%s = %s", key, value);
                if(strcmp(key, "LOGFILE") == 0){       //Identify the LOGFILE path
                    if(strcmp(value,"") == 0){
                        strncpy(pLogFilePath,"/var/log/messages", 255);
                    } else {
                        strncpy(pLogFilePath,value, 255);                    
                    }
                } else if(strcmp(key, "CPUthreshold") == 0){  //Read the CPUthreshold
                    sscanf(value, "%lf", &(*pCPU));
                } else if(strcmp(key, "MEMthreshold") == 0){  //Read the Memthreshold
                    sscanf(value, "%lf", &(*pMEM));
                } else if(strcmp(key, "SYNthreshold") == 0){  //Read the SYNthreshold
                    sscanf(value, "%lf", &(*pSYNN));
                }
            }
        }
        fclose(fp);    
    }
    
}


/*

int main(){
    //WRITELOG
    int type = 6;
    scanf("%d",&type);
    double currentInfo = 90;
    double threshold = 75;
    char * systemError = "ERROR DEL SISTEMA";
    // char * logFile = "/var/log/trackermon.log";
    char * logFile = "/var/log/messages";
    writeLog(type, &currentInfo, &threshold, systemError, logFile);
    
    //READCONF
    double CPU_TRESHOLD = 0, MEM_TRESHOLD = 0, SYNNCONN_TRESHOLD = 0;
    char * logFilePath;
    readConfigFile(&CPU_TRESHOLD, &MEM_TRESHOLD, &SYNNCONN_TRESHOLD, logFilePath); 
    printf("%s\n", logFilePath);      
    printf("%f\n", CPU_TRESHOLD);
    printf("%f\n", MEM_TRESHOLD);
    printf("%f\n", SYNNCONN_TRESHOLD);           
    return 0;

}
*/