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

void init_string(char* s,int size){
    int i=0;
    for(i=0;i<size;i++){
        s[i]='\0';
    }
}

char * decrypt(char *key, char * msg,int size){
    char *result;								//final result of decrypted message
    result=(char*)malloc(size);
    char temp_result[8];  						//8 bytes result--ecb block result
    int i=0; 									//current position
    const_DES_cblock input;
    DES_cblock output;
    init_string(result,size);
    DES_cblock DES_key;							/*						*/
    DES_key_schedule schedule;					/*						*/
    memcpy(DES_key,key,20);						/*initialize des setting*/
    DES_set_odd_parity(&DES_key);				/*						*/
    DES_set_key_checked(&DES_key,&schedule);	/*						*/
    
    for(i=0;i<size;i+=8){						//decrypt every 8-byte block in the message using ecb
        memcpy(input,msg+i,8);
        DES_ecb_encrypt(&input,&output,&schedule,DES_DECRYPT);
        memcpy(output,temp_result,8);				//copy the decrypted message to temp memory
        strcat(result,output);						//concatenate temp result to final result
    }
    return result;
}

char *verify_one(int line,char *msg,char* a0){
    int msg_len=strlen(msg);								//Lj length
    int w_len=1;											//mask length
    int y_len=20;											//y length
    int z_len=20;											//z length
    int a_len=20;											//a length
    int k_len=20;											//hashed key length
    int d_len=msg_len-w_len-y_len-z_len;					//encrypted msg length
    
    
    char *a_hash_message="Increment Hash";
    char a_hash[strlen(a_hash_message)+a_len];				//hash string for a
    char a[a_len];											//aj
    char k_hash[w_len+a_len];								//hash string for k
    char k[k_len];											//kj
    int i=0;
    int n=0;												//line counter
    init_string(a_hash,strlen(a_hash_message)+a_len);
    memcpy(a,a0,a_len);										//copy a0 to aj
    
    for(n=0;n<line;n++){
        strcat(a_hash,a_hash_message);
        strcat(a_hash,a);
        SHA1(a_hash,strlen(a_hash_message)+a_len,a);			//Aj+1=hash("Increment Hash",Aj)
        init_string(a_hash,strlen(a_hash_message)+a_len);
    }
    
    char * encrypted_msg=(char*)malloc(d_len);
    char *w=(char*)malloc(w_len);
    memcpy(w,msg,1);										//get W value
    memcpy(encrypted_msg,msg+1,d_len);						//get EkDj value
    init_string(k_hash,w_len+a_len);
    strcat(k_hash,w);
    strcat(k_hash,a);										//Wj+Aj
    SHA1(k_hash,w_len+a_len,k);								//Kj=H(Wj,Aj)
    char *decrypted_msg=decrypt(k,encrypted_msg,d_len);		//decrypt Lj with Kj
    printf("decrypted %s\n",decrypted_msg);
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
