#include "Process.h"
#include <thread>
#include <iostream>
#include <math.h>
ofstream outputFile; //outputFile definition


Process::Process(){}

void Process::run(steady_clock::time_point t1, bool successiveRun){
    if(this->priority < 100){
        this->timeQuantum = (140 - this->priority) * 20;
    }else{
        this->timeQuantum = (140 - this->priority) * 5;
    }
    steady_clock::time_point t2 = steady_clock::now();
    int64_t current_time = duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    if(this->timeQuantum >= this->remainingTime){
        this->waitingTime = current_time - arrivalTime - (burstTime - remainingTime);
        if(!this->started){
            outputFile<<"Time "<< current_time <<", " << this->PID<< ", Started, Granted "<< this->remainingTime<< endl;
            cout<<"Time "<< current_time <<", " << this->PID<< ", Started, Granted "<< this->remainingTime<< endl;
            this->started = true;
        }else{
            outputFile<<"Time "<< current_time <<", " << this->PID<< ", Resumed, Granted "<< this->remainingTime<< endl;
            cout<<"Time "<< current_time <<", " << this->PID<< ", Resumed, Granted "<< this->remainingTime<< endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(this->remainingTime));
        t2 = steady_clock::now();
        current_time = duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        outputFile<<"Time "<< current_time <<", " << this->PID<< ", Terminated "<< endl;
        cout<<"Time "<< current_time <<", " << this->PID<< ", Terminated "<< endl;
        this->remainingTime == 0;
        this->done = true;
    }else{
        this->waitingTime = current_time - arrivalTime - (burstTime - remainingTime);
        cout<<"--- Time "<< current_time <<", " << this->PID<< ", Waiting time: " << waitingTime <<endl;
        if(!this->started){
            outputFile<<"Time "<< current_time <<", " << this->PID<< ", Started, Granted "<< this->timeQuantum<< endl;
            cout<<"Time "<< current_time <<", " << this->PID<< ", Started, Granted "<< this->timeQuantum<< endl;
            this->started = true;
        }else{
            outputFile<<"Time "<< current_time <<", " << this->PID<< ", Resumed, Granted "<< this->timeQuantum<< endl;
            cout<<"Time "<< current_time <<", " << this->PID<< ", Resumed, Granted "<< this->timeQuantum<< endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(this->timeQuantum));
        t2 = steady_clock::now();
        current_time = duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        outputFile<<"Time "<< current_time <<", " << this->PID<< ", Paused "<< endl;
        cout<<"Time "<< current_time <<", " << this->PID<< ", Paused "<< endl;
        this->remainingTime -= this->timeQuantum;
    }   
    //this->passes += 1;
    if(successiveRun && !this->done){
        int bonus = ceil((this->waitingTime * 10)/(current_time - this->arrivalTime));
        cout<< "Bonus: "<< bonus<< endl;
        this->priority = max(100, min(this->priority - bonus + 5, 139));
        outputFile<<"Time "<< current_time <<", " << this->PID << ", priority updated to " << this->priority << endl;
        cout<<"Time "<< current_time <<", " << this->PID << ", priority updated to " << this->priority << endl;
    }
}