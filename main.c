#include <stdio.h>
#include <stdlib.h>
#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include <stdbool.h>
#include <openssl/sha.h>
#include <unistd.h>
#include <time.h>

bool log_opened=false;
char * log_id=NULL;
char * A_0,A_j;
time_t d,d_plus;
int id=0;
FILE *fp=NULL;


char * w[] = {
        "LogfileInitializationType", "ResponseMessageType",
        "AbnormalCloseType", "NormalCloseType"
    };
    


void createlog(const char* filename){
	if(log_opened){
		printf("Log is opened already");
		return;
	}
	if( access( filename, F_OK ) != -1 ) {
    	printf("file is already exist");
	} 
	//create new file
	
	if((log_id ==NULL)||(log_id == "" )){
		
	}else{
		printf("Log is opened already");
		log_opened = true;
		return;
	}
		id = 0;
		
		fp=fopen(filename,"a+");
		log_id = filename;
		
		
		//===time
		time(&d);
		d_plus=d+360000;
		//printf("%ld   %ld",d,d_plus);
		A_j=A_0;
}

int main(){
    
    char input[300];				//stdin
    char command[20];			
    char arg1[140];
    char arg2[140];
    int entry=0;					//entry countr
    
    char fileName[140];

    while(1){
 		printf("\n>>");
        fgets(input,300,stdin);
        
        sscanf(input,"%s %s %s",command,arg1,arg2);
       
        if(strcmp(command,"add")==0){
			if(fp==NULL){
			printf("log has not been created");
			}else{
			printf("added log entry %d",entry);
            entry++;
			}
        }else if(strcmp(command,"createlog")==0){
            strncpy(fileName,arg1,140);
            //fp=fopen(fileName,"a+");
            //printf("created %s",fileName);
      		
			createlog(fileName);
        }else if(strcmp(command,"closelog")==0){
			
			if(fp!=NULL){
            fclose(fp);
            printf("closed %s",fileName);
			}
			return 0;

            
        }else if(strcmp(command,"verify")==0){
          
            
        }else if(strcmp(command,"verifyall")==0){
    
            
        }else{
            printf("invalid command");
        }
       
        
    }
}
