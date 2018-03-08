#ifndef PROCESS_H
#define PROCESS_H
#include <string>
using namespace std;


class Process{
    public:
        Process();
        Process(int, string, int, int);
        int priority;
        string PID;
        int burstTime;
        int arrivalTime;
        
};

#endif