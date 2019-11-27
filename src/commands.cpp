#include "commands.hpp"
#include <algorithm>
#include <filesystem>
#include <unistd.h>
#include <unordered_map>
namespace filesystem = std::filesystem;

struct {
    std::string vlc = "C:/Program Files (x86)/VideoLAN/VLC/vlc.exe";
} commands;

struct {
    filesystem::path vids = "/mnt/c/Users/Seb/Desktop/Vids/";
} folders;

std::string windowsify(std::string path) {
    return "C:" + path.substr(7);
}

void vlc(std::vector<std::string> text, int argI) {
    std::vector<std::string> words;
    size_t i = argI;
    // 5 after it, or less. Essentially SegFault protection
    size_t n = i+5 < text.size() ? 5 : i+4 < text.size() ? 4 : i+3 < text.size() ? 3 : i+2 < text.size() ? 2 : 1;
    // Possible arguments
    for (; i != n; i++) {
        words.push_back(text[i]);
    }
    // Find files that contain an argument
    std::unordered_map<std::string, int> file_count;
    for (auto& p : filesystem::recursive_directory_iterator(folders.vids)) {
        for (auto it = words.begin(); it != words.end(); ++it) {
            std::string lowerPath = p.path().generic_string();
            // Copied: converts lowerPath to lowercase
            std::transform(lowerPath.begin(), lowerPath.end(), lowerPath.begin(),
                [](unsigned char c){ return std::tolower(c); });
            if (lowerPath.find(*it) != std::string::npos) {
                std::string windowsString = windowsify(p.path().generic_string());
                std::pair<std::unordered_map<std::string, int>::iterator,bool> success = file_count.insert(std::make_pair(windowsString, 1));
                if (!success.second) {
                    success.first->second++;
                }
            }
        }
    };
    // Find file with highest hits
    std::string highest = file_count.begin()->first;
    for (auto it = file_count.begin(); it != file_count.end(); ++it) {
        if (it->second > file_count[highest]) {
            highest = it->first;
        }
    }

    execl("/mnt/c/Windows/system32/cmd.exe", "cmd.exe",
        "/C", commands.vlc, highest, (char *)NULL);
}