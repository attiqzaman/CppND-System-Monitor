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

int Process::Pid() { return pid_; }

float Process::CpuUtilization() {
    // per https://stackoverflow.com/a/16736599
    float total_time = LinuxParser::ActiveJiffies(Pid());
    float uptime = LinuxParser::UpTime();
    float seconds_active = uptime - (Process::UpTime() / sysconf(_SC_CLK_TCK));
    return (total_time / sysconf(_SC_CLK_TCK)) / seconds_active;
}

string Process::Command() { return commandUsed_; }

string Process::Ram() { return LinuxParser::Ram(pid_); }

string Process::User() { return LinuxParser::User(pid_); }

long int Process::UpTime() { return LinuxParser::UpTime(pid_); }

bool Process::operator<(Process& a) {
    return CpuUtilization() < a.CpuUtilization();
}