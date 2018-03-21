#include "Queue.h"

Queue::Queue(){}

Queue::Queue(bool active){
    this->active = active;
}

void Queue::sort(){
    int i, j;
    size_t n = processQueue.size();
    Process* tempProcess;
    for (i = 0; i < n -1; i++)      
        // Last i elements are already in place   
        for (j = 0; j < n-i-1; j++){
                if (processQueue[j]->priority < processQueue[j+1]->priority){
                    tempProcess = processQueue[j];
                    processQueue[j] = processQueue[j+1];
                    processQueue[j+1] = tempProcess;
                }
        }
           
}