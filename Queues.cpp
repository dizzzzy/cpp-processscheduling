#include "Queues.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;
using namespace chrono;

Queues::Queues(){
}

Queue* Queues::getWaitingQueue(){
    return Q0;
}

Queue* Queues::getActiveQueue(){
    if(Q1->active){
        return Q1;
    }else{
        return Q2;
    }
}

Queue* Queues::getExpiredQueue(){
    if(!Q1->active)
    {
        return Q1;
    }else{
        return Q2;
    }
}


void Queues::feedExpiredQueue(steady_clock::time_point t1){ //need to pass in currentTime
    Queue* qActive = getActiveQueue();
    Queue* qWaiting = getWaitingQueue();
    //clock_t t1 = clock();
    //system_clock::time_point t1 = now();
    while(qWaiting->processQueue.size() != 0 ){
        for(int i=0; i< qWaiting->processQueue.size(); i++){
            steady_clock::time_point t2 = steady_clock::now();
            int64_t current_time = duration_cast<std::chrono::milliseconds>(t2 - t1).count();
            //cout<< current_time <<endl;
            if(current_time> qWaiting->processQueue[i].arrivalTime){
                //------race condition #1 ----- SHOULD USE MUTEX
                mu.lock();
                //putting things into expired queue
                Queue* qExpired = getExpiredQueue();
                qExpired->processQueue.push_back(qWaiting->processQueue[i]);
                outputFile<<"Time "<< current_time <<", " << qWaiting->processQueue[i].PID<< ", Arrived"<< endl;
                cout<<"Time "<< current_time <<", " << qWaiting->processQueue[i].PID<< ", Arrived"<< endl;
                qWaiting->processQueue.pop_front();
                mu.unlock();
                //----------------------------
            }
        }
    }
    // if (int i =0; i < qWaiting->processQueue.size; i++){
   // bool temp = false;
    // }
}

void Queues::start(){
    Queue* qWaiting = getWaitingQueue();
    Queue* qActive = getActiveQueue();
    Queue* qExpired = getExpiredQueue();
    bool doneTasks = false;
    string previousProcess = "";
    //sortWaiting();
    steady_clock::time_point t1 = steady_clock::now();
    std::thread t(&Queues::feedExpiredQueue, this, t1);
    t.detach();
    steady_clock::time_point t2 = steady_clock::now();
    int64_t current_time = duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    while(current_time < 1000){ //Scheduler has to wait for a second before starting to run tasks
        t2 = steady_clock::now();
        current_time = duration_cast<std::chrono::milliseconds>(t2 - t1).count();
        //cout<< current_time << endl; test waiting for 1 second
    }
    while(!doneTasks ){
        while(!qActive->processQueue.empty()){
            
            if( previousProcess == qActive->processQueue[0].PID){
                //it has ran twice in a row
                previousProcess = "";//reset the previousProcess
                qActive->processQueue[0].run(t1, true);//true is has ran 
            }else{ //it has NOT ran twice
                previousProcess = qActive->processQueue[0].PID;
                qActive->processQueue[0].run(t1, false);//retain previous run
            }
            if(qActive->processQueue[0].done){ //process has no more time to run 
                qActive->processQueue.pop_front();
                //cout<< 
            }else{
                qExpired->processQueue.push_back(qActive->processQueue[0]);  //Feed other queues
                qActive->processQueue.pop_front();
            }
        }
        //--------race conditon #1 can occur here------------
        mu.lock();
        if(qExpired->processQueue.empty() && qWaiting->processQueue.empty() && qActive->processQueue.empty()){
            //listing all three prevents race conditions
            //no more taks to run
            doneTasks = true;
        }else if(!qExpired->processQueue.empty() && qActive->processQueue.empty()){ //swap queues
            qExpired->sort();
            qActive->active = false;
            qExpired->active = true;
            Queue* temp = qActive;
            qActive = qExpired;
            qExpired = temp;
        }else{
            //the waiting queue put a tasks into the active queue right after the above 
            //while loop and before the mutex can lock
            //so bassically dont do anything and let it go back to it looking for tasks
            //in the active queue
        }
        mu.unlock();
        //--------------------------------------------------
        

    }
    
    //run the first task in the active queue for 1s
    
}

void Queues::setWaitingQueue(Queue* waitingQueue){
    Q0 = waitingQueue;
}


void Queues::setActiveQueue(Queue* activeQueue){
    Q1 = activeQueue;
}

void Queues::setExpiredQueue(Queue* expiredQueue){
    Q2 = expiredQueue;
}

