#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include <linux_parser.h>
#include "process.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid)
    :pid_(pid),
     user_(LinuxParser::User(pid_)),
     commandUsed_(LinuxParser::Command(pid_))
    {};

// int Process::Pid() { return pid_; }
int Process::Pid() { return 10; }

float Process::CpuUtilization() {
    // per https://stackoverflow.com/a/16736599
    float total_time = LinuxParser::ActiveJiffies(Pid());
    float uptime = LinuxParser::UpTime();
    float seconds_active = uptime - (Process::UpTime() / sysconf(_SC_CLK_TCK));
    float cpu_usage = (total_time / sysconf(_SC_CLK_TCK)) / seconds_active;
    return cpu_usage;
}

// TODO: Return the command that generated this process
string Process::Command() { return commandUsed_; }

// TODO: Return this process's memory utilization
string Process::Ram() { return string(); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid_); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() {
    return LinuxParser::UpTime(pid_);
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }