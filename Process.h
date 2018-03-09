#ifndef PROCESS_H
#define PROCESS_H
#include <string>
using namespace std;


class Process{
    public:
        Process();
        Process(int, string, int, int);
        bool done = false;
        int priority;
        string PID;
        int burstTime;
        int arrivalTime;
        int allocatedBurstTime;
        void run();
};

#endif