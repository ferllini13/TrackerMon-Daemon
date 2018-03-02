#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief   Method that write a log file
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
        fclose(pFile); // Close the file
        printf("Error opening file!\n");
            
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
 * @brief Setting global variables
 */
#define CONFIG_FILE_NAME "/etc/trackermon/config.conf"

/**
 * @brief   Method that read the config file
 * @details This method read the config file and save it values
 *
 * reference: https://www.pacificsimplicity.ca/blog/simple-read-configuration-file-struct-example = link that helps to resolve the problem
 * 
 * @param pCPU          Read the threshold from the CPU
 * @param pMEM          Read the threshold from the Mem
 * @param pSYN          Read the threshold from the SYN
 * @param pLogFilePath  Read the Log File path
 */
void readConfigFile(double * pCPU, double * pMEM, double * pSYN, char * pLogFilePath){
    FILE * pFile = fopen(CONFIG_FILE_NAME, "r"); //r read the file
    if (pFile == NULL) //Verify if the file is open
    { 
        fclose(pFile); // Close the file
        exit(EXIT_FAILURE);
    }
    else
    {
        char key[256], value[256]; //Create the char variables to store the values
        char * line = NULL;
        size_t len = 0;
        ssize_t read;

        while ((read = getline(&line, &len, pFile)) != -1) {
            if(line[0] == '#' || line[0] == '\n')       //Ignores the empty
                continue;
            else{
                sscanf(line, "%s = %s", key, value);    //Search for a "=" in the configuration file
                if(strcmp(key, "LOGFILE") == 0){        //Identify the LOGFILE path in the configuration file
                    if(strcmp(value,"") == 0){          //If the LOGFILE path is empty
                        strncpy(pLogFilePath,"/var/log/messages", 255); //Set the LOGFILE path as "/var/log/messages"
                    } else {
                        strncpy(pLogFilePath,value, 255);   //Set the LOGFILE path as the one in the configuration file
                    }
                } else if(strcmp(key, "CPUthreshold") == 0){  //Read the CPUthreshold
                    sscanf(value, "%lf", &(*pCPU));
                } else if(strcmp(key, "MEMthreshold") == 0){  //Read the Memthreshold
                    sscanf(value, "%lf", &(*pMEM));
                } else if(strcmp(key, "SYNthreshold") == 0){  //Read the SYNthreshold
                    sscanf(value, "%lf", &(*pSYN));
                }
            }
        }
        fclose(pFile); // Close the file  
    }
    
}

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