#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid) : pidDir(pid) {
    this->processPid = Pid();
    this->processUser = User();
    this->processUpTime = UpTime();
    this->processCpuUtilization = CpuUtilization();
    this->processCommand = Command();
    this->processRamUtilization = Ram(); 
}

int Process::Pid() { return this->pidDir; }

float Process::CpuUtilization() const {
    return LinuxParser::CpuUtilization(this->processPid);
}

string Process::Command() { return LinuxParser::Command(this->processPid); }

string Process::Ram() { return LinuxParser::Ram(this->processPid); }

string Process::User() { return LinuxParser::User(this->processPid); }

long int Process::UpTime() { return LinuxParser::UpTime(this->processPid); }

//bool Process::operator<(Process const& proc2) const { return (this->CpuUtilization() > proc2.CpuUtilization()); }
bool Process::operator<(Process const& proc2) const{
    return ( this->getProcessCpuUtilization() > proc2.getProcessCpuUtilization());
    //return ( this->getProcessRamUtilization() > proc2.getProcessRamUtilization());
}


// Getters
int Process::getPid() const{
    return this->processPid;
}

float Process::getProcessCpuUtilization() const{
    return this->processCpuUtilization;
}

std::string Process::getProcessCommand() const{
    return this->processCommand;
}

std::string Process::getProcessRamUtilization() const{
    return this->processRamUtilization;
}

std::string Process::getProcessUser() const{
    return this->processUser;
}

long int Process::getProcessUpTime() const{
    return this->processUpTime;
}
