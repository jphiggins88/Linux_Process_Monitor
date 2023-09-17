#ifndef SYSTEM_PARSER_H
#define SYSTEM_PARSER_H

#include <fstream>
#include <regex>
#include <string>
#include <unistd.h>

namespace LinuxParser {
const long clockFrequency = sysconf(_SC_CLK_TCK);

// Paths
const std::string kProcDirectory{"/proc/"};
const std::string kCmdlineFilename{"/cmdline"};
const std::string kCpuinfoFilename{"/cpuinfo"};
const std::string kStatusFilename{"/status"};
const std::string kStatFilename{"/stat"};
const std::string kUptimeFilename{"/uptime"};
const std::string kMeminfoFilename{"/meminfo"};
const std::string kVersionFilename{"/version"};
const std::string kOSPath{"/etc/os-release"};
const std::string kPasswordPath{"/etc/passwd"};

// Keys to search for
const std::string filterVmRss{"VmRSS:"}; // This was recommended in Udacity code review over VmSize
const std::string filterVmSize{"VmSize:"}; // Not used. The key above was recommended in code review
const std::string PrettyName{"PRETTY_NAME"};
const std::string filterMemTotal{"MemTotal:"};
const std::string filterMemAvailable{"MemAvailable:"};
const std::string filterProcesses{"processes"};
const std::string filterProcs_running{"procs_running"};
const std::string filterUid{"Uid:"};

const std::string NA{"na"};

// System
float MemoryUtilization();
long UpTime();
std::vector<int> Pids();
int TotalProcesses();
int RunningProcesses();
std::string OperatingSystem();
std::string Kernel();

// CPU
enum CPUStates {
  kUser_ = 0,
  kNice_,
  kSystem_,
  kIdle_,
  kIOwait_,
  kIRQ_,
  kSoftIRQ_,
  kSteal_,
  kGuest_,
  kGuestNice_
};
std::vector<std::string> CpuUtilization();
long Jiffies();
long ActiveJiffies();
long ActiveJiffies(int pid);
long IdleJiffies();

// Processes
std::string Command(int pid);
std::string Ram(int pid);
std::string Uid(int pid);
std::string User(int pid);
long int UpTime(int pid);
float CpuUtilization(int pid);
};  // namespace LinuxParser

#endif