#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"
#include <unistd.h>

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid) : pidDir(pid) {
    this->processPid = Pid();
    //this->processCpuUtilization = CpuUtilization();
    //this->processCommand = Command();
    //this->processRamUtilization = Ram();
    this->processUser = User();
    //this->processUpTime = UpTime();
}

// TODO: Return this process's ID
int Process::Pid() { return this->pidDir; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() {
    //return std::stof(LinuxParser::CpuUtilization(this->processPid));
    return 0.0;
}

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(this->processPid); }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(this->processPid); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(this->processPid); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(this->processPid); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }