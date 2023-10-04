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

float Process::CpuUtilization() const { return LinuxParser::CpuUtilization(this->processPid); }

string Process::Command() {
    // Shorten the string to a manageable size before returning
    return LinuxParser::Command(this->processPid).substr(0, 37) + "...";
}

string Process::Ram() { return LinuxParser::Ram(this->processPid); }

string Process::User() { return LinuxParser::User(this->processPid); }

long int Process::UpTime() {
    long systemUptime = LinuxParser::UpTime();
    long processUptime = LinuxParser::UpTime(this->processPid);
    return systemUptime - processUptime;
}


bool Process::operator<(Process const& proc2) const{
    return ( this->getProcessCpuUtilization() > proc2.getProcessCpuUtilization());
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
