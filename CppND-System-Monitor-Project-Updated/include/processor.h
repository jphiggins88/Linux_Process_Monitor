#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <vector>

class Processor {
 public:
    float Utilization();  // TODO: See src/processor.cpp

    std::vector<long> getCpuUtilization();

  // TODO: Declare any necessary private members
 private:
    std::vector<long> t0_usage;
    std::vector<long> t0minus_usage;

    float cpuPercentUtilization;
};

#endif