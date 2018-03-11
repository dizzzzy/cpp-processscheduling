#ifndef PROCESS_H
#define PROCESS_H
#include <string>
#include <chrono>
using namespace std;
using namespace std::chrono;

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
        void run(steady_clock::time_point);
};

#endif