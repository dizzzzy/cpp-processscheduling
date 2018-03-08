#include "Process.h"

Process::Process(){}

Process::Process(int priority, string PID, int burstTime, int arrivalTime){
    this->priority = priority;
    this->PID = PID;
    this->burstTime = burstTime;
    this->arrivalTime = arrivalTime;
}
