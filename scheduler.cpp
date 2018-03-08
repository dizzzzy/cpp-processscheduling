// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <vector>
#include <string.h>
#include <string>
#include "Queue.h"
using namespace std;

int main () {
  string line;
  ifstream myfile ("input.txt");
  Queue Q1(true);
  Queue Q2(false);
  if (myfile.is_open())
  {
    for (int i= 0; getline (myfile,line); i++)
    {
      if(i == 0){
      }else{
       // Q1.processQueue.push_back();
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
          }
          if(j== 3){
            process->priority = stoi(string(p));
          }
          std::cout << p << '\n';
          p = strtok(NULL," ");
        }
        Q1.processQueue.push_back(* process);
      }
    }
    myfile.close();
  }
  else{
    cout << "Unable to open file"; 
  }

  
  getchar();
  return 0;
}