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
}

int Process::Pid() { return this->pidDir; }

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

string Process::Command() { return LinuxParser::Command(this->processPid); }

string Process::Ram() { return LinuxParser::Ram(this->processPid); }

string Process::User() { return LinuxParser::User(this->processPid); }

long int Process::UpTime() { return LinuxParser::UpTime(this->processPid); }

bool Process::operator<(Process const& proc2) const { return (this->CpuUtilization() > proc2.CpuUtilization()); }