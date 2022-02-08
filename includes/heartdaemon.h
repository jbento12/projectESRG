/**
 * @file heartdaemon.h
 * @author ERSG group 3
 * @brief 
 * @version 0.1
 * @date 2022-02-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef HEARTDAEMON_H
#define HEARTDAEMON_H

#include <iostream>
#include <unistd.h>
#include <mqueue.h>   /* mq_* functions */
#include <sys/stat.h>
#include <stdlib.h>
#include <string>
#include <signal.h>
#include <string.h>


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

    int32_t getHeartRate(void);
    int32_t getHeartStamp(void);
    void startHeart();
    void stopHeart();

    pid_t getPidDaemon(){return this->pidDaemon;};

private:
    pid_t pidDaemon;

    mqd_t msgq_id;
    int mq_recv_ret;
    unsigned int m_prio;
    unsigned int msg_num = 0;

    int32_t heartRate;
    int32_t heartStamp;
};

#endif // HEARTDAEMON_H
