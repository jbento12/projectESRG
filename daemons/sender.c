#include <stdio.h>
#include <mqueue.h>   /* mq_* functions */
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
#include <sys/ipc.h>
#include <fcntl.h>
#include  <sys/syslog.h>


/* name of the POSIX object referencing the queue */
#define MSGQOBJ_NAME    "/daemonMessage"
/* max length of a message (just for this process) */
#define MAX_MSG_LEN     10000
//define message priority
#define MSG_PRIO 1


//--------------- global variables ----------------------------
pid_t DaemonPid;
static char strlog[255];
char volatile charSignal = 0;


void sig_handler(int sig){

    if(sig == SIGUSR2){
        charSignal = 1;//read
 	syslog(LOG_ERR, "%s\n", "RECEBEU SIGUSR2");
    }
    
    else if(sig == SIGUSR1){
        charSignal = 0;//stop
	syslog(LOG_ERR, "%s\n", "RECEBEU SIGUSR1");
    }
}



// void DaemonProc(pid_t pid)
// {
//     pid_t sid;
//     char mypid[12];

//     /* Fork off the parent process */
//     pid = fork();
//     if (pid < 0)// on error exit 
//     { 
// 		syslog(LOG_ERR, "%s\n", "fork");
// 		exit(EXIT_FAILURE);
// 	}
//     /* Success: Let the parent terminate */
//     if (pid > 0)
//     {
//         memset(strlog, 0, sizeof strlog);
//         strcpy(strlog, "\nHeartRate PID = ");  
//         sprintf(mypid, "%d", pid);
//         strcat(strlog, mypid);
//         strcat(strlog, "\n");
//         WriteLog(strlog);
        
//         exit(EXIT_SUCCESS);
//     }

//     /* On success: The child process becomes session leader */
//     sid = setsid(); // create a new session
// 	if (sid < 0)// on error exit
//     { 
// 		syslog(LOG_ERR, "%s\n", "setsid");
// 		exit(EXIT_FAILURE);
// 	}

//     // make '/' the root directory
// 	if (chdir("/") < 0) { // on error exit
// 		syslog(LOG_ERR, "%s\n", "chdir");
// 		exit(EXIT_FAILURE);
// 	}
    
// 	umask(0);

//     close(STDIN_FILENO);  // close standard input file descriptor
// 	close(STDOUT_FILENO); // close standard output file descriptor
// 	close(STDERR_FILENO); // close standard error file descriptor
// }




int main(int argc, char *argv[]) {
    //----- communication varibles -------
    mqd_t msgq_id;
    char buffer[MAX_MSG_LEN];    
    unsigned int m_prio = 1;
    unsigned int msg_num = 0;
    int mq_recv_ret;
    
    //-------- Devide varibales ----------
    int fd = 0; 
    int count=0;
    char devBuff[512];
    char sendBuff[64];
    int heartRate = 0;
    int heartStamp = 0;
    char heartName1[32];
    char heartName2[32];
    
    //-------- daemon varibles -----------
    pid_t pid, sid;
    char mypid[12];
    
    
    
    // ---------- signals -----------
   signal(SIGUSR2, sig_handler);
   signal(SIGUSR1, sig_handler);
    
    
    
   //------------------------ Turn into a daemon -----------------------
   /* Fork off the parent process */
    pid = fork();
    syslog(LOG_ERR, "%s - %d\n", "fork", pid);
    if (pid < 0)// on error exit 
    { 
		syslog(LOG_ERR, "%s\n", "fork");
		exit(EXIT_FAILURE);
	}
    /* Success: Let the parent terminate */
    if (pid > 0)
    {
        memset(strlog, 0, sizeof strlog);
        strcpy(strlog, "\nHeartRate PID = ");  
        sprintf(mypid, "%d", pid);
        strcat(strlog, mypid);
        strcat(strlog, "\n");
        //WriteLog(strlog);
        
        exit(EXIT_SUCCESS);
    }

    /* On success: The child process becomes session leader */
    sid = setsid(); // create a new session
	if (sid < 0)// on error exit
    { 
		syslog(LOG_ERR, "%s\n", "setsid");
		exit(EXIT_FAILURE);
	}

    // make '/' the root directory
	if (chdir("/") < 0) { // on error exit
		syslog(LOG_ERR, "%s\n", "chdir");
		exit(EXIT_FAILURE);
	}
    
	umask(0);

    	close(STDIN_FILENO);  // close standard input file descriptor
	close(STDOUT_FILENO); // close standard output file descriptor
	close(STDERR_FILENO); // close standard error file descriptor
	
    
    
    
    
    
	// --------------------- Message Queque ------------------------------------------
	    
	    /* opening the queue using default attributes  --  mq_open() */
	    msgq_id = mq_open(MSGQOBJ_NAME, O_RDWR | O_CREAT, S_IRWXU | S_IRWXG, NULL);
	    if (msgq_id == (mqd_t)-1) {
		perror("In mq_open()");
		exit(1);
	    }
    
   	// ----------- sends PID to Main process ----------------------------------
    	sprintf(buffer, "DaemonPID %d %d", getpid(), 0);
	mq_send(msgq_id, buffer, strlen(buffer) + 1, m_prio);
	syslog(LOG_ERR, "%s - %d\n", buffer, strlen(buffer));
	
	
	
	 //------------ Open NRF device --------------------------------------------
            
	        
	while(1)
	{
		if(charSignal)
		{
		    
		    
		    while(charSignal)
		    {
		    	syslog(LOG_ERR, "%s\n", "Opening NRF Device...");
			    fd = open("/dev/nrf", O_RDWR);
			    if(fd < 0) {
				        syslog(LOG_ERR, "%s\n", "ERROR Opening NRF Device...");
				return 0;
			    }
            
		        syslog(LOG_ERR, "%s\n", "Reading NRF Device...");
		        read(fd, devBuff, count);
		        sscanf(devBuff, "%s %s %d %d", heartName1, heartName2, &heartRate, &heartStamp);	//get name and value
		        syslog(LOG_ERR, "%s\n", devBuff);
		        
		        if(!strcmp(heartName1, "NRF") && !strcmp(heartName2, "HeartRate"))
		        {
		            sprintf(sendBuff, "HeartRate %d %d", heartRate, heartStamp);
		            mq_send(msgq_id, sendBuff, strlen(sendBuff) + 1, m_prio);	
		            msg_num++;
		        }
		    	
		    	close(fd);
		        sleep(1);
		        
		    }
		}
		
		sleep(1);
	}
	
	
    /* closing the queue        -- mq_close() */
    mq_close(msgq_id);     
    return 0;
}








	//--------------- get Main PID and store it ------------
	/*mq_recv_ret = mq_receive(msgq_id, buffer, MAX_MSG_LEN, NULL);
        if (mq_recv_ret == -1) {
            perror("In mq_receive()");
        }
        
	if(sscanf(buffer, "%*[^0123456789]%d", &mainProcessPid) != 1)
		perror("In obtaining main process PID()");
        */
