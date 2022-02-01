#include <stdio.h>
#include <mqueue.h>   /* mq_* functions */
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

/* name of the POSIX object referencing the queue */
#define MSGQOBJ_NAME    "/daemonMessage"
/* max length of a message (just for this process) */
#define MAX_MSG_LEN     70
//define message priority
#define MSG_PRIO 1


int main(int argc, char *argv[]) {
    mqd_t msgq_id;
	char buffer[MAX_MSG_LEN];    
    unsigned int m_prio = 1;
    unsigned int msg_num = 0;
    /* opening the queue using default attributes  --  mq_open() */
    msgq_id = mq_open(MSGQOBJ_NAME, O_RDWR | O_CREAT, S_IRWXU | S_IRWXG, NULL);
    if (msgq_id == (mqd_t)-1) {
        perror("In mq_open()");
        exit(1);
    }
    
    
	
	
	while(1)
	{
		sprintf(buffer, "Ora boas num - %d HEHE", msg_num);
		
	    	mq_send(msgq_id, buffer, strlen(buffer) + 1, m_prio);
		msg_num++;
		sleep(1);
	}
	
    /* closing the queue        -- mq_close() */
    mq_close(msgq_id);     
    return 0;
}
