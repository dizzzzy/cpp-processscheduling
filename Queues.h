#ifndef QUEUES_H
#define QUEUES_H
#include "Queue.h"

class Queues{
    private:
        Queue* Q1; //active queue
        Queue* Q2; //expired queu
    public:
        Queues();
        Queue* getActiveQueue();
        Queue* getExpiredQueue();
        void start();
        void sort();
        void setActiveQueue(Queue*);
        void setExpiredQueue(Queue*);
        void switchActiveQueue();
};

#endif