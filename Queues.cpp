#include "Queues.h"
#include <thread>

Queues::Queues(){
}

Queue* Queues::getActiveQueue(){
    if(Q1->active){
        return Q1;
    }else{
        return Q2;
    }
}

void Queues::sort(){
    Q1->sort();
    Q2->sort();
}

void Queues::start(){
    Queue* qActive = getActiveQueue();
    Queue* qExpired = getExpiredQueue();
    bool doneTasks = false;
    while(!doneTasks){
        while(!qActive->processQueue.empty()){
            qActive->processQueue[0].run();
            //std::thread firstThread (q->processQueue[0].run);
            //firstThread.join();
            if(qActive->processQueue[0].done){ //process has no more time to run 
                qActive->processQueue.pop_front();
            }else{
                qExpired->processQueue.push_back(qActive->processQueue[0]);  //Feed other queues
                qActive->processQueue.pop_front();
            }
        }
        if(qExpired->processQueue.empty()){
            //no more taks to run
            doneTasks = true;
        }else{ //swap queues
            Queue* temp = qActive;
            qActive = qExpired;
            qExpired = temp;
        }

    }
    
        
    //run the first task in the active queue for 1s
    
}

void Queues::setActiveQueue(Queue* activeQueue){
    Q1 = activeQueue;
}

void Queues::setExpiredQueue(Queue* expiredQueue){
    Q2 = expiredQueue;
}

Queue* Queues::getExpiredQueue(){
    if(!Q1->active)
    {
        return Q1;
    }else{
        return Q2;
    }
}

void Queues::switchActiveQueue(){

    this->sort();
}