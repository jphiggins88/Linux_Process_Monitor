#include "processor.h"
#include "linux_parser.h"

#include <unistd.h>
#include <string>

// Return the aggregate CPU allCpuUsageization
float Processor::Utilization() {

    t0_usage = getCpuUtilization();

    long totalUsage = t0_usage[0];
    long idleUsage = t0_usage[1];

    cpuPercentUtilization = ((float)totalUsage - (float)idleUsage) / (float)totalUsage;

    return cpuPercentUtilization;
}

std::vector<long> Processor::getCpuUtilization() {
    std::vector<std::string> allCpuUsage = LinuxParser::CpuUtilization();
    long cpuUser, cpuNice, cpuSys, cpuIdle, cpuIoWait, cpuIrq, cpuSoftirq, cpuSteal;
    long total, idleTotal, nonIdleTotal;

    cpuUser =       std::stol(allCpuUsage[0]);
    cpuNice =       std::stol(allCpuUsage[1]);
    cpuSys =        std::stol(allCpuUsage[2]);
    cpuIdle =       std::stol(allCpuUsage[3]);
    cpuIoWait =     std::stol(allCpuUsage[4]);
    cpuIrq =        std::stol(allCpuUsage[5]);
    cpuSoftirq =    std::stol(allCpuUsage[6]);
    cpuSteal =      std::stol(allCpuUsage[7]);

    nonIdleTotal = cpuUser + cpuNice + cpuSys + cpuIrq + cpuSoftirq + cpuSteal;
    idleTotal = cpuIdle + cpuIoWait;
    total = idleTotal + nonIdleTotal;

    std::vector<long> totalAndIdleStats = {total, idleTotal};
    return totalAndIdleStats;
}