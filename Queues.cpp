#include "Queues.h"

Queues::Queues(){
    this->Q1.active = true;
    this->Q2.active = false;
};

Queues::getActiveQueue(){
    if(Q1.active == true){
        return &Q1;
    }
}