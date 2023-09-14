#include <string>
#include <iomanip>
#include <sstream>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long totalSeconds) {
    int secondsInHour = 3600;
    int secondsInMin = 60;
    long seconds = totalSeconds;

    int hours;
    int minutes;

    hours = seconds/secondsInHour;
    seconds = seconds%secondsInHour;

    minutes = seconds/secondsInMin;
    seconds = seconds%secondsInMin;

    std::stringstream ss_hours;
    ss_hours << std::setw(2) << std::setfill('0') << hours;

    std::stringstream ss_mins;
    ss_mins << std::setw(2) << std::setfill('0') << minutes;

    std::stringstream ss_secs;
    ss_secs << std::setw(2) << std::setfill('0') << seconds;

    return (ss_hours.str() + ":" + ss_mins.str() + ":" + ss_secs.str());
}