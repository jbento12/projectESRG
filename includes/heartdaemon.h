#ifndef HEARTDAEMON_H
#define HEARTDAEMON_H

#include <unistd.h>
#include <mqueue.h>   /* mq_* functions */
#include <sys/stat.h>
#include <stdlib.h>
#include <string>
#include <signal.h>
#include <string.h>
#include <iostream>

#define MSGQOBJ_NAME    "/daemonMessage"
#define MAX_MSG_LEN     10000
#define MSG_PRIO 1
#define MSG_PID_STR "DaemonPID"
#define MSG_HEART_RATE_STR "HeartRate"


using namespace std;

class HeartDaemon
{
public:
    HeartDaemon();
    ~HeartDaemon();

    bool open();
    bool close();
    int readFromMsg();

    uint32_t getHeartRate(void);
    void startHeart();
    void stopHeart();


private:
    pid_t pidDaemon;

    mqd_t msgq_id;
    int mq_recv_ret;
    unsigned int m_prio;
    unsigned int msg_num = 0;

    uint32_t heartRate;
};

#endif // HEARTDAEMON_H
