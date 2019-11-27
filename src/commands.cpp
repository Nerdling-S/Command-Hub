#include "commands.hpp"
#include <algorithm>
#include <filesystem>
#include <unistd.h>
#include <unordered_map>
#include <wait.h>
namespace filesystem = std::filesystem;

struct {
    std::string vlc = "/mnt/c/Program\\ Files\\ \\(x86\\)/VideoLAN/VLC/vlc.exe";
} commands;

struct {
    filesystem::path vids = "/mnt/c/Users/Seb/Desktop/Vids/";
    filesystem::path music = "/mnt/c/Users/Seb/Music/";
} folders;

std::string windowsify(std::string path) {
    return "file:///C:" + path.substr(6);
}

void vlc(std::vector<std::string> text, int argI) {
    std::vector<std::string> words;
    size_t i = argI;
    // Possible arguments
    for (; i < text.size(); i++) {
        words.push_back(text[i]);
    }
    // Find files that contain an argument
    std::unordered_map<std::string, int> fileCount;
    std::unordered_map<std::string, int> lastIndex;
    // In Vids
    for (auto& p : filesystem::recursive_directory_iterator(folders.vids)) {
        for (auto it = words.begin(); it != words.end(); ++it) {
            std::string lowerPath = p.path().generic_string();
            // Copied: converts lowerPath to lowercase
            std::transform(lowerPath.begin(), lowerPath.end(), lowerPath.begin(),
                [](unsigned char c){ return std::tolower(c); });
            int i = lowerPath.find(*it);
            if (i != std::string::npos) {
                std::string windowsString = windowsify(p.path().generic_string());
                std::pair<std::unordered_map<std::string, int>::iterator,bool> success = fileCount.insert(std::make_pair(windowsString, 1));
                if (success.second) {
                    lastIndex.insert(std::make_pair(windowsString, i));
                } else {
                    // If after last Index add twice
                    success.first->second += i > lastIndex[windowsString] ? 2 : 1;
                }
            }
        }
    }
    // In Music
    for (auto& p : filesystem::recursive_directory_iterator(folders.music)) {
        for (auto it = words.begin(); it != words.end(); ++it) {
            std::string lowerPath = p.path().generic_string();
            // Copied: converts lowerPath to lowercase
            std::transform(lowerPath.begin(), lowerPath.end(), lowerPath.begin(),
                [](unsigned char c){ return std::tolower(c); });
            int i = lowerPath.find(*it);
            if (i != std::string::npos) {
                std::string windowsString = windowsify(p.path().generic_string());
                std::pair<std::unordered_map<std::string, int>::iterator,bool> success = fileCount.insert(std::make_pair(windowsString, 1));
                if (success.second) {
                    lastIndex.insert(std::make_pair(windowsString, i));
                } else {
                    // If after last Index add twice
                    success.first->second += i > lastIndex[windowsString] ? 4 : 1;
                }
            }
        }
    }
    // Find file with highest hits
    std::string highest = fileCount.begin()->first;
    for (auto it = fileCount.begin(); it != fileCount.end(); ++it) {
        if (it->second > fileCount[highest]) {
            highest = it->first;
        }
    }
    runCommand(commands.vlc + " \"" + highest + "\"");
}

void runCommand(std::string command) {
    // execl("/bin/sh", "sh", "-c",
    pid_t cpid = fork();
    switch (cpid)
    {
    case -1: perror("fork");
        break;
    
    case 0: execl("/bin/sh", "sh", "-c", command.c_str(), (char*)NULL);
    
    default: waitpid(cpid, NULL, 0);
        break;
    }
}