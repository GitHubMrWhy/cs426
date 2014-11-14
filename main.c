#include <stdio.h>
#include <stdlib.h>
#include <openssl/ssl.h>
#include <openssl/rsa.h>
#include <stdbool.h>
#include <openssl/sha.h>
#include <openssl/des.h>
#include <openssl/evp.h>
#include <openssl/hmac.h>
#include <openssl/md5.h>
#include <unistd.h>
#include <time.h>

bool log_opened=false;
char * log_id=NULL;
char  A_0[20],* A_j;
time_t d,d_plus;
int id=0;
FILE *fp=NULL;


char * w[] = {
        "LogfileInitializationType", "ResponseMessageType",
        "AbnormalCloseType", "NormalCloseType"
    };
    
char * Hash(char* str){






}

char* concat(char *s1, char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1);//+1 for the zero-terminator
    //in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

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
		strcpy(log_id,filename);
		
		RAND_bytes(A_0,20);
		//printf("%s  ",A_0);
		
		//===time
		time(&d);
		d_plus=d+360000;
		//printf("%ld   %ld",d,d_plus);
		A_j=A_0;
		
		
		char * k = Hash(concat(A_0,w[0]));
		printf("%s  ",k);
		 
}

int main(){
    
    char input[300];				//stdin
    char command[20];			
    char arg1[140];
    char arg2[140];
    int entry=0;					//entry countr
    
    char fileName[140];
	//printf("%s\n",concat("aaaa","bbbbb"));
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
