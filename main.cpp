#include <cstdlib>
#include <string>
#include <sstream>
#include <windows.h>
using namespace std;

void FailBox(const char *cmd) {
    stringstream ss;
    ss << "Failed to execute the command line \"" << cmd << "\".  ";
    ss << "GLE = " << GetLastError() << ".";
    MessageBox(nullptr, ss.str().c_str(), "Error", MB_ICONERROR);
}

void UsageBox() {
    MessageBox(nullptr, "Usage: hideconsole.exe CMD", "Usage", MB_OK);
}

// Grumble, grumble it's stupid to have to reinvent the wheel like this
string shellEscape(const char *arg) {
    stringstream builder;
    char ch;
    builder << '\'';
    while(ch = *arg++) {
        if(ch == '\'') {
            builder << "''\"''";
        } else {
            builder << ch;
        }
    }
    builder << '\'';
    return builder.str();
}

int main(int argc, char *argv[]) {
    if(argc < 2) {
        UsageBox();
        return 1;
    }
    
    stringstream cmdline;
    char *exePath = argv[1];
    while(*++argv) {
        cmdline << shellEscape(*argv) << ' ';
    }
    
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    memset(&si, 0, sizeof(si));
    si.cb = sizeof(si);
    memset(&pi, 0, sizeof(pi));
    DWORD flags = CREATE_NO_WINDOW;
    BOOL cpSuccess = CreateProcess(
        exePath, (char*)/*HACK*/cmdline.str().c_str(), nullptr, nullptr, FALSE, flags, nullptr,  nullptr, &si, &pi
    );
    
    if(!cpSuccess) {
        FailBox(cmdline.str().c_str());
        return -1;
    }
    
    return 0;
}
