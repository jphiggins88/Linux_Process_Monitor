#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <vector>

class Processor {
 public:
    float Utilization();

    std::vector<long> getCpuUtilization();

 private:
    std::vector<long> t0_usage;
    std::vector<long> t0minus_usage;

    float cpuPercentUtilization;
};

#endif