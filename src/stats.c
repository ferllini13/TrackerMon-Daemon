#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>


double getCPUStat(){
	FILE* file = fopen("/proc/stat","r"); 

	if(file == NULL){ 
		printf("Error: cant open file\n");
		return -1;
	}
	else{

		char line[100];
		char* token;
		int i = 0;
		double sum = 0;
		double idle = 0;
		fgets(line,100,file);
		fclose(file);
		token = strtok(line," ");
		
		while(token!=NULL){
			token = strtok(NULL," ");
			if(token!=NULL){
				sum += atof(token);
				if(i==3)
					idle = atof(token);
				i++;
			}				
		}	
		float cpuUsage= (1-(idle/sum))*100;
		printf("%f %s\n",cpuUsage,"%");
		return cpuUsage;	
	}  
}
 

double memStat(){

	
	FILE *file = fopen ("/proc/meminfo", "r");

    if (file == NULL){
    			printf("Error: cant open file\n");
    	fclose(file);	
    	return -1;
    }
    else{
    	double mem;
		double memAvailable;
    	char line[100];
    	int i = 0;
    	int j = 0;
    	char* token;
    	while(i<2){
    	 	fgets(line, sizeof(line), file);
    	 	token = strtok(line," ");
    	 	while(token!=NULL && j< 4){          
				token = strtok(NULL," ");
				if (j == 0){
					mem = atof(token);
				}
				if (j == 3){
					memAvailable = atof(token); 
				}
				j++;	
			}
            i++;
    	} 

    	fclose(file);
    	double memUsage=100*(mem- memAvailable)/mem;
    	printf("%f %s\n",memUsage,"%");
    	return memUsage;

    }
}