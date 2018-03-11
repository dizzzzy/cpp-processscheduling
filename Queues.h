#ifndef QUEUES_H
#define QUEUES_HsetWaitingQueue
#include "Queue.h"
#include <mutex>
using namespace std::chrono;

class Queues{
    private:
        Queue* Q0; //waiting queue
        Queue* Q1; //active queue
        Queue* Q2; //expired queue
        std::mutex mu;
    public:
        Queues();
        Queue* getWaitingQueue();
        Queue* getActiveQueue();
        Queue* getExpiredQueue();
        void start();
        void feedActiveQueue(steady_clock::time_point);
        void sort();
        void setWaitingQueue(Queue*);
        void setActiveQueue(Queue*);
        void setExpiredQueue(Queue*);
        void switchActiveQueue();
};

#endif