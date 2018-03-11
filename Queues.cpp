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


void Queues::sort(){
    Q1->sort();
    Q2->sort();
}

void Queues::feedActiveQueue(steady_clock::time_point t1){ //need to pass in currentTime
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
                //putting things into active queue
                Queue* qActive = getActiveQueue();
                qActive->processQueue.push_back(qWaiting->processQueue[i]);
                cout<<"Time "<< current_time <<", " << qWaiting->processQueue[i].PID 
                    << ", Arrived"<< endl;
                qWaiting->processQueue.pop_front();
                mu.unlock();
                

                //push it into active queue
               // qExpired->processQueue.push_back(qActive->processQueue[0]);  //Feed other queues
               // qActive->processQueue.pop_front();
            }
        }
    }
    // if (int i =0; i < qWaiting->processQueue.size; i++){
    bool temp = false;
    // }
}

void Queues::start(){
    Queue* qWaiting = getWaitingQueue();
    Queue* qActive = getActiveQueue();
    Queue* qExpired = getExpiredQueue();
    bool doneTasks = false;
    //sortWaiting();
    steady_clock::time_point t1 = steady_clock::now();
    std::thread t(&Queues::feedActiveQueue, this, t1);
    t.detach();
    while(!doneTasks){
        
        while(!qActive->processQueue.empty()){
            qActive->processQueue[0].run(t1);
            //std::thread firstThread (q->processQueue[0].run);
            //firstThread.join();
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

void Queues::switchActiveQueue(){
    this->sort();
}