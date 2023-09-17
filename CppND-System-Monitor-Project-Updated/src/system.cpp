#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>
#include <iostream>

#include "process.h"
#include "processor.h"
#include "system.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

Processor& System::Cpu() {
    return cpu_;
}

vector<Process>& System::Processes() {
    // Get all Processes and add to the processes_ vector.
    vector<int> pids = LinuxParser::Pids();
    // Loop through the vector and obtain information about each process.
    for (const auto& pid : pids) {
        // Modifying how processes are created and stored.
        // When a process is created from its pid, all information is obtained at that time and stored inside the process objects attributes.
        // This is so we can take a snapshot of that process at that moment.
        // This should fix the issue of trying to obtain information from that process later by calling the process functions.
        // Previously, if a process existed at t0, it was added to the list.
        // Occasionally the process would be removed, and calling that process's functions at t0+n would result in a segmentation fault or some kind of memmory error.

        // add the process object to the processes_ vector
        // Using emplace_back allows us to skip creating a temporary object then storing it in the vector.
        // We can construct the object in-place in the vector. The pid is passed into the constructor.
        processes_.emplace_back(pid);
    }

    std::sort(processes_.begin(), processes_.end());

    return processes_;
}

std::string System::Kernel() {
    return LinuxParser::Kernel();
}

float System::MemoryUtilization() {
    return LinuxParser::MemoryUtilization();
}

std::string System::OperatingSystem() {
    return LinuxParser::OperatingSystem();
}

int System::RunningProcesses() {
    return LinuxParser::RunningProcesses();
}

int System::TotalProcesses() {
    return LinuxParser::TotalProcesses();
}

long int System::UpTime() {
    return LinuxParser::UpTime();
}