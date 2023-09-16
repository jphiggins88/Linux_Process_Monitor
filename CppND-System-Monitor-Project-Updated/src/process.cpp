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
    // Don't need to call these when constructed. The ncurses DisplayProcesses calls each of these.
    // Dont need to store these in private member variables either.
    this->processPid = Pid();
    //this->processUser = User();
    //this->processUpTime = UpTime();
    //this->processCpuUtilization = CpuUtilization();
    //this->processCommand = Command();
    //this->processRamUtilization = Ram();
}

// TODO: Return this process's ID
int Process::Pid() { return this->pidDir; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() const {
    // processTotalUpTimeSeconds = systemUptime - (processStartTimeTicks / Hertz)
    long systemUptime = LinuxParser::UpTime();
    long clockFrequency = sysconf(_SC_CLK_TCK);
    

    vector<string> processCpuinfo = LinuxParser::CpuUtilization(this->processPid);
    long utime = std::stol(processCpuinfo[0]);  // time proc has been scheduled in user mode
    long stime = std::stol(processCpuinfo[1]);  // time proc has been scheduled in kernel mode
    //long cutime = std::stol(processCpuinfo[2]); // time the proc's children have been scheduled in user mode
    //long cstime = std::stol(processCpuinfo[3]); // time the proc's children have been scheduled in kernel mode
    long startTimeSec = std::stol(processCpuinfo[4]);  // time the process started after system boot

    double totalTime = utime + stime; // We exclude the child processes' time
    double elapsedTimeSinceProcStart = systemUptime - startTimeSec;

    float processCpuUtilization = 100 * ((totalTime/clockFrequency)/elapsedTimeSinceProcStart);
    return processCpuUtilization;
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
bool Process::operator<(Process const& proc2) const { return (this->CpuUtilization() > proc2.CpuUtilization()); }