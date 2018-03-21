#ifndef PROCESS_H
#define PROCESS_H
#include <string>
#include <chrono>
#include <fstream>
using namespace std;
using namespace std::chrono;

extern ofstream outputFile; //outPutFile declaration

class Process{
    public:
        Process();
        // Process(int, string, int, int);
        bool done = false;
        bool started = false;
        //int passes;
        int priority;
        string PID;
        int burstTime;
        int remainingTime;
        int arrivalTime;
        int timeQuantum;
        int waitingTime;
        void run(steady_clock::time_point, bool);
};

#endif