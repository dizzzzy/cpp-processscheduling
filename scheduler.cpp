// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <vector>
#include <string.h>
#include <string>
#include "Queue.h"
#include "Queues.h"
using namespace std;

int main () {
  string line;
  ifstream myfile ("input.txt");
  Queues qz; //queues
  Queue* Q1= new Queue(true);
  Queue* Q2= new Queue(false);
  if (myfile.is_open())
  {
    for (int i= 0; getline (myfile,line); i++)
    {
      if(i == 0){
      }else{
        cout << line << '\n';
        char * cstr = new char [line.length()+1];
        strcpy(cstr, line.c_str());

        // cstr now contains a c-string copy of str
        char * p = strtok (cstr," ");
        Process* process = new Process();
        for (int j = 0; p!=0; j++)
        {
          std::string::size_type sz;   // alias of size_t
          if(j== 0){
            process->PID = string(p);
          }
          if(j== 1){
            process->arrivalTime = stoi(string(p));
          }
          if(j== 2){
            process->burstTime = stoi(string(p));
            process->allocatedBurstTime = 50;
          }
          if(j== 3){
            process->priority = stoi(string(p));
          }
          std::cout << p << '\n';
          p = strtok(NULL," ");
        }
        Q1->processQueue.push_back(* process);
      }
    }
    qz.setActiveQueue(Q1);
    qz.setExpiredQueue(Q2);
    myfile.close();
  }
  else{
    cout << "Unable to open file"; 
  }

  qz.start();
  
  getchar();
  return 0;
}