#include "applicationInterface.h"
#include "training.h"
#include "manageDB.h"
#include "gui.h"
#include <pthread.h>


class applicationInterface
{

public:
    applicationInterface();
    ~applicationInterface();
    void initSemaphores();
    void initMutexes();
    void initConditionVariables();
    void initSignal();
    void initSharedMemory();
    static void *tIdle(void*);
    void setupThread(int, pthread_attr_t *, struct sched_param *);
    bool initThreads();
};

