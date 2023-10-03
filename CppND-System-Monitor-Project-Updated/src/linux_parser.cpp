#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <filesystem>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == PrettyName) {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  filestream.close();

  return value;
}

string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  stream.close();

  return kernel;
}

vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);

  return pids;
}

float LinuxParser::MemoryUtilization() {
  string line;
  string key;
  string value;
  int memTotal = 1;
  int memAvailable = 1;
  bool valuesObtained = false;

  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == filterMemTotal) {
          memTotal = std::stoi(value);
        }
        else if (key == filterMemAvailable) {
          memAvailable = std::stoi(value);
          valuesObtained = true;
          break;
        }
      }
      if (valuesObtained == true) {
        break;
      }
    }
  }
  filestream.close();

  return (float(memTotal - memAvailable) / float(memTotal));
}

long LinuxParser::UpTime() {
  string line;
  string upTime;
  long upTimeSeconds;
  std::ifstream filestream(kProcDirectory + kUptimeFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    // Only take the first value which represent uptime of the system in seconds
    linestream >> upTime;
    upTimeSeconds = std::stol(upTime);

    return upTimeSeconds;
  }
  filestream.close();

  return 0;
}

vector<string> LinuxParser::CpuUtilization() {
  string line;
  string cpuString;

  vector<string> cpuData(8, NA);

  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> cpuString >> cpuData[0] >> cpuData[1] >> cpuData[2] >> cpuData[3] >> cpuData[4] >> cpuData[5] >> cpuData[6] >> cpuData[7];
  }
  stream.close();

  return cpuData;
}

int LinuxParser::TotalProcesses() {
  bool valuesObtained = false;
  int totalProcesses = 0;
  string line;
  string key;
  string value;

  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == filterProcesses) {
          totalProcesses = std::stoi(value);
          valuesObtained = true;
          break;
        }
      }
      if (valuesObtained == true) {
        break;
      }
    }
  }
  filestream.close();

  return totalProcesses;
}

int LinuxParser::RunningProcesses() {
  bool valuesObtained = false;
  int runningProcesses = 0;
  string line;
  string key;
  string value;

  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == filterProcs_running) {
          runningProcesses = std::stoi(value);
          valuesObtained = true;
          break;
        }
      }
      if (valuesObtained == true) {
        break;
      }
    }
  }
  filestream.close();

  return runningProcesses;
}

// Process Functions
string LinuxParser::Command(int pid) {
    //  /proc/[PID]/cmdline
  string line;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kCmdlineFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    return line;
  }
  filestream.close();
  
  return NA;
}

string LinuxParser::Ram(int pid) {
  // This will return the value associeated with the VmRSS key
  // Originally I used VmSize, but this can excede the physical system RAM.
  // Instead I use VmRSS to give exact physical memory as recommended in the code review.
  //  /proc/[PID]/status
  string line;
  string key;
  string value;

  string ram = NA;
  double ramMb;
  bool valuesObtained = false;

  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == filterVmSize) {
          ram = value;
          ramMb = std::stod(ram)/1024.0;
          valuesObtained = true;
          break;
        }
      }
      if (valuesObtained == true) {
        break;
      }
    }
  }
  filestream.close();

  std::ostringstream stream;
  //stream << std::fixed << std::setprecision(2) << ramMb;
  stream << std::fixed << std::setprecision(0) << ramMb;
  return stream.str();
}

string LinuxParser::Uid(int pid) {
  //  /proc/[PID]/status
  string line;
  string key;
  string value;

  string uid = NA;
  bool valuesObtained = false;

  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == filterUid) {
          uid = value;
          valuesObtained = true;
          break;
        }
      }
      if (valuesObtained == true) {
        break;
      }
    }
  }
  filestream.close();

  return uid;
}

string LinuxParser::User(int pid) {
  string uid = Uid(pid);

  //  /etc/passwd
  string line;
  string userName;
  string dummyVal;
  string userId;

  string userOfThisProcess = NA;
  bool valuesObtained = false;

  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> userName >> dummyVal >> userId) {
        if (userId == uid) {
          userOfThisProcess = userName;
          valuesObtained = true;
          break;
        }
      }
      if (valuesObtained == true) {
        break;
      }
    }
  }
  filestream.close();

  return userOfThisProcess;
}

long LinuxParser::UpTime(int pid) {
  long processStartTimeTicks;
  long processStartTimeSecs;

  string line;
  string cpuString;
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    vector<string> tokens;
    string token;
    std::istringstream tokenizer(line);

    while (tokenizer >> token) {
      tokens.emplace_back(token);
    }

    processStartTimeTicks = std::stol(tokens[21]);  // time the process started after system boot
  }
  stream.close();
  
  // Convert from ticks to seconds.
  processStartTimeSecs = static_cast<double>(processStartTimeTicks) / static_cast<double>(clockFrequency);

  return processStartTimeSecs;
}

float LinuxParser::CpuUtilization(int pid) {
  string line;
  string cpuString;
  vector<string> tokens;
  string filePath = kProcDirectory + to_string(pid) + kStatFilename;
  if (std::filesystem::exists(filePath)) {
    std::ifstream stream(filePath);
    if (stream.is_open()) {
      std::getline(stream, line);
      string token;
      std::istringstream tokenizer(line);

      int i = 0;
      // No need to read past token 21. We only care about 13-16 and 21.
      while (tokenizer >> token && i < 22) {
        if (i == 13 || i == 14 || i == 15 || i == 16 || i == 21) {
          //tokens.push_back(token);
          tokens.emplace_back(token);
        }
        i++;
      }
    }
    stream.close();

    float utime = std::stof(tokens[0]);  // time proc has been scheduled in user mode (in ticks)
    float stime = std::stof(tokens[1]);  // time proc has been scheduled in kernel mode (in ticks)
    float cutime = std::stof(tokens[2]); // time the proc's children have been scheduled in user mode (in ticks)
    float cstime = std::stof(tokens[3]); // time the proc's children have been scheduled in kernel mode (in ticks)

    float processUpTimeSecs = std::stof(tokens[4])/(float)clockFrequency;
    long systemUptime = LinuxParser::UpTime();
    double totalTime = utime + stime + cutime + cstime; // We exclude the child processes' time
    double elapsedTimeSinceProcStart = systemUptime - processUpTimeSecs;

    float processCpuUtilization = ((totalTime/clockFrequency)/elapsedTimeSinceProcStart);

    return processCpuUtilization;
  }
  // If the path doesn't exist, return 0.0 because it is no longer running or present in the proc directory.
  return 0.0;
}


