#ifndef QUEUE_H
#define QUEUE_H
#include <deque>
#include "Process.h"

class Queue{
    public:
        Queue();
        Queue(bool);
        std::deque<Process> processQueue; 
        bool active;
        void sort();
};

#endif