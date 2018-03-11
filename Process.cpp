#include "Process.h"
#include <thread>
#include <iostream>



Process::Process(){}

Process::Process(int priority, string PID, int burstTime, int arrivalTime){
    this->priority = priority;
    this->PID = PID;
    this->burstTime = burstTime;
    this->arrivalTime = arrivalTime;
}

void Process::run(steady_clock::time_point t1){
    //check if time left for execution is smaller than burst time
        //if so then execute for the rest of execution time
    //else
        //execute for the burstTime
    //Time 2000, P1, Resumed, Granted 1000  
    //Time 3000, P1, Paused 
    if(this->allocatedBurstTime >= this->burstTime){
            steady_clock::time_point t2 = steady_clock::now();
            int64_t current_time = duration_cast<std::chrono::milliseconds>(t2 - t1).count();
            cout<<"Time "<< current_time <<", " << this->PID<< ", Resumed, Granted "<< this->burstTime<< endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(this->burstTime));
            t2 = steady_clock::now();
            current_time = duration_cast<std::chrono::milliseconds>(t2 - t1).count();
            cout<<"Time "<< current_time <<", " << this->PID<< ", Terminated "<< endl;
            this->burstTime == 0;
            this->done = true;
    }else{
        steady_clock::time_point t2 = steady_clock::now();
        int64_t current_time = duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        cout<<"Time "<< current_time <<", " << this->PID<< ", Resumed, Granted "<< this->allocatedBurstTime<< endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(this->allocatedBurstTime));
        t2 = steady_clock::now();
        current_time = duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        cout<<"Time "<< current_time <<", " << this->PID<< ", Paused "<< endl;
        this->burstTime -= this->allocatedBurstTime;
    }   
}