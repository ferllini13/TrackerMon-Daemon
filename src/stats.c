#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

//return CPU usage
double getCPUStat(){
	FILE* file = fopen("/proc/stat","r"); // open the file with CPU info (stat)


	if(file == NULL){ // if file cant be opened
		printf("Error: can't open file\n");// print error
		fclose(file);// close file
		return -1;// return error
	}
	else{

		char line[100];// will load a line of memeinfo
		char* token;//will load a lime element
		int i = 0; //index to iterate in line
		double total = 0; // will load the total of CPU capacity
		double idle = 0; // will load the CPU available(idle)
		fgets(line,100,file);//load first line
		fclose(file);// close file after read
		token = strtok(line," ");// load a line element 
		
		while(token!=NULL){
			token = strtok(NULL," ");// eliminate line description
			if(token!=NULL){ // if isnt null
				total += atof(token);// add to the total
				if(i==3) // to get the iddle wich is in the third position
					idle = atof(token);// cast to double and assign to idle
				i++;// incrementes the index
			}				
		}	
		double cpuUsage= (1-(idle/total))*100;// calculate the CPU usage
		printf("%f %s\n",cpuUsage,"%");
		return cpuUsage;// return the result
	}  
}
 


//return memory usage
double getMemStat(){
	FILE *file = fopen ("/proc/meminfo", "r");

    if (file == NULL){// if file cant be opened
    	printf("Error: canit open file\n");// print error
    	fclose(file);// close file
    	return -1;// return error
    }
    else{
    	double memTotal;// will total of memory
		double memFree;// will free memory
    	char line[100];// will load a line of memeinfo
    	int i = 0; // index to iterate in lines
    	int j = 0; //index to iterate in line
    	char* token; //will load a lime element
    	while(i<2){
    	 	fgets(line, sizeof(line), file);// load a line
    	 	token = strtok(line," "); // load a line element
    	 	while(token!=NULL && j< 4){          
				token = strtok(NULL," ");// eliminate line description
				if (j == 0){
					memTotal = atof(token); // cast token to double and assign memTotal
				}
				if (j == 3){
					memFree = atof(token);// cast token to double and assign memTotal
				} 
				j++;// incrementes index
			}
		i++;//incremet index

    	} 

    	fclose(file);
    	double memUsage=100*(memTotal- memFree)/memTotal;//calculate the percent
    	printf("%f %s\n",memUsage,"%");
    	return memUsage;// retrurn the result

    }
}

// return the number of SYN_RECV
int getSynStat(){
	
   	FILE *file = popen ("netstat -tuna | grep -c SYN_RECV", "r");//load  the command output with syn information

    if (!file){// if file cant be opened
    	printf("Error: can't open file\n");// print error
    	fclose(file);// close file
    	return -1;// return error
    }
    else{
    	char line[100];// will load a line of tmd
    	fgets(line, sizeof(line), file);// load a line

    	fclose(file);// close file after read
    	int synRecv = atof(line);// cast line to int and assing to sysRecv
    	printf("%d\n",synRecv);
  
  		return synRecv;// return the result
  	} 
}


//gest the critical messages from syslog
void getSyslogStat(int * criticalCount){
	FILE *file = popen ("cat /var/log/syslog | grep CRITICAL", "r");//load  the command output with syn information

    if (file==NULL){// if file cant be opened
    	printf("Error: can't open file\n");// print error
    	fclose(file);// close file
    	//return -1;// return error
    }
    else{
    	int count=0;    		
    	char line[500];// will load a line of tmd
    	while(fgets(line, sizeof(line), file)!=NULL){ // run while the line is not null
    		if (count >= *criticalCount){
    			//write log
    			printf("%s\n",line);
    			criticalCount++;
    		}
    		count++;
    		
    	}
    	fclose(file);// close file after read

	}
}





void checkCpu(double cpuThreshold){
	double cpuUsage=getCPUStat();

	if (cpuUsage>cpuThreshold){
		// wtrite log
	}
}		


void checkMem(double memThreshold){
	double memUsage=getMemStat();
	if (memUsage>memThreshold){
		//wtrite log
	}	
}

void checkSyn(int synThreshold){
	int synRecv=getSynStat();
	if (synRecv>synThreshold){
		//wtrite logc
	}
}