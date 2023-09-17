#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
   
   // Constructor
   Process(int pid);

   int Pid();
   std::string User();
   std::string Command();
   float CpuUtilization() const;
   std::string Ram();
   long int UpTime();
   //bool operator<(Process const& a) const;
   bool operator<(Process& a);

   // getters
   int getPid();
   float getProcessCpuUtilization();
   std::string getProcessCommand();
   std::string getProcessRamUtilization();
   std::string getProcessUser();
   long int getProcessUpTime();

  // TODO: Declare any necessary private members
 private:
   int pidDir;
   int processPid;
   float processCpuUtilization;
   std::string processCommand;
   std::string processRamUtilization;
   std::string processUser;
   long int processUpTime;
};

#endif