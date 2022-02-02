#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>
#include <errno.h>
#include <string>
#include "main.h"

static char strlog[255];
char volatile charSignal = 0;

/* message structure for messages in the shared segment */
struct msg_s {
    int type;
    char content[MAX_MSG_LENGTH];
};

void sig_handler(int sig){

    else if(sig == SIGUSR2){
        charSignal = 1;//read
	WriteLog("Signal USR2 received!\n");
    }
    
    else if(sig == SIGUSR1){
        charSignal = 0;//stop
	WriteLog("Signal USR1 received!\n");
    }
}


int main(int argc, char *argv[])
{
    char *str;
    char logaux[12];
    Heart HeartDaemon;
    pid_t pid;
    int shmfd;
    int shared_seg_size = (1 * sizeof(struct msg_s));   /* want shared segment capable of storing 1 message */
    struct msg_s *shared_msg;      /* the shared segment, and head of the messages list */

    signal(SIGUSR2, sig_handler);
    signal(SIGUSR1, sig_handler);

    // Turn process into daemon 
    DaemonProc(pid);
    // share process ID 
    ShareID();

    int fd0 = open("/dev/nrf", O_WRONLY);

    //Runs until the program ends
    while(1)
    {
        //wait for something in the shared memory
        while(!charSignal);
        charSignal = 1;
        WriteLog("Signal received!\n");

        read(fd0, )
        



       

        //Detach from memory
        shmdt(str);

        /* open the file and get the decoding format */
       
    }

    
    //Deamon shutding down
    syslog (LOG_NOTICE, "close Heart Daemon");
    closelog();

    return 0;
}


void WriteLog(const char *message)
{
    int len = strlen(message);
    int fd;

	char *buf = (char *)malloc(sizeof(char) + len + 1);
	if (buf == NULL) 
    {
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	if ((fd = open("/var/log/heartratedaemon.log",	O_CREAT | O_WRONLY | O_APPEND, 0600)) < 0) 
    {
		perror("open");
		exit(EXIT_FAILURE);
	}

	strncpy(buf, message, len + 1);
	write(fd, buf, len + 1);
	close(fd);
}

void DaemonProc(pid_t pid)
{
    pid_t sid;
    char mypid[12];

    /* Fork off the parent process */
    pid = fork();
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
        WriteLog(strlog);
        
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
}

void ShareID(void)
{

    int nSharedMemoryID = 10; 
    int nSharedMemorySize = 4096;
    // generate unique ID
    key_t key = ftok("/Daemons/HeartDaemon",nSharedMemoryID);

    if (key == -1)  {
    std::cerr << "ERROR: ftok(id: " << nSharedMemoryID << ") failed, " << strerror(errno) << std::endl;
    exit(3);
}
    // request a shared memory segment 
    int id = shmget(key,nSharedMemorySize, IPC_CREAT | 0666);
     if (id == -1)  {
      std::cerr << "ERROR: shmget() failed, " << strerror(errno) << std::endl << std::endl;
      exit(4);
    }
    // shmat to attach to shared memory
    unsigned char *str = (unsigned char*) shmat(id,(const void*)NULL,0);

   if (str == (unsigned char *)-1)  {
    std::cerr << "ERROR: shmat() failed, " << strerror(errno) << std::endl << std::endl;
    exit(5);
}   
    std::cout << "shmat() successful " << std::endl;

    //Write to the shared memory the process ID
    sprintf(str, "%d", getpid());

    //detach from shared memory
    shmdt(str);
}

