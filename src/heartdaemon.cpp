#include "heartdaemon.h"


HeartDaemon::HeartDaemon()
{
 heartRate = 0;
 pidDaemon = 0;
}

HeartDaemon::~HeartDaemon()
{

}

bool HeartDaemon::open()
{
    /* opening the queue using default attributes  --  mq_open() */
    msgq_id = mq_open(MSGQOBJ_NAME, O_RDWR | O_CREAT , S_IRWXU | S_IRWXG, NULL);
    if (msgq_id == (mqd_t)-1) {
        perror("In mq_open()");
        return false;
    }
}


bool HeartDaemon::close()
{
    mq_close(this->msgq_id);
}


int HeartDaemon::readFromMsg()
{
    char str[MAX_MSG_LEN];
    int num;
     //--------------- get get message ------------
     mq_recv_ret = mq_receive(msgq_id, str, MAX_MSG_LEN, NULL);
     if (mq_recv_ret == -1) {
         perror("In mq_receive()");
         return mq_recv_ret;
     }

     // --------------- Scan message ---------------
     sscanf(str, "%s %d", str, &num);
     if(strcmp(MSG_PID_STR, str))       //verify if it is the PID
     {
         pidDaemon = num;
     }
     else if(strcmp(MSG_HEART_RATE_STR, str))   //verify if it is the PID
        {
            heartRate = num;
        }
        else
         {
             cout << "cant recognize Heart format\n";
         }
}






uint32_t HeartDaemon::getHeartRate(void)
{
    return this->heartRate;
}


void HeartDaemon::startHeart()
{
    //send "start" signal to daemon
    if(pidDaemon > 0)
        kill(pidDaemon, SIGUSR2);
}


void HeartDaemon::stopHeart()
{
    //send "stop" signal to daemon
    if(pidDaemon > 0)
        kill(pidDaemon, SIGUSR1);
}
