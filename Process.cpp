#include "Process.h"
#include <chrono>
#include <thread>

Process::Process(){}

Process::Process(int priority, string PID, int burstTime, int arrivalTime){
    this->priority = priority;
    this->PID = PID;
    this->burstTime = burstTime;
    this->arrivalTime = arrivalTime;
}

void Process::run(){
    //check if time left for execution is smaller than burst time
        //if so then execute for the rest of execution time
    //else
        //execute for the burstTime
    if(this->allocatedBurstTime > this->burstTime){
            std::this_thread::sleep_for(std::chrono::milliseconds(this->burstTime));
            this->burstTime == 0;
            this->done = true;
    }else{
            std::this_thread::sleep_for(std::chrono::milliseconds(this->allocatedBurstTime));
            this->burstTime = this->burstTime - this->allocatedBurstTime;
    }   
}