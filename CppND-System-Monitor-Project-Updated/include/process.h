#ifndef PROCESS_H
#define PROCESS_H

#include <string>


class Process {
 public:
   Process(int pid);

   int Pid();
   std::string User();
   std::string Command();
   float CpuUtilization() const;
   std::string Ram();
   long int UpTime();
   bool operator<(Process const& a) const;

   int getPid() const;
   float getProcessCpuUtilization() const;
   std::string getProcessCommand() const;
   std::string getProcessRamUtilization() const;
   std::string getProcessUser() const;
   long int getProcessUpTime() const;

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