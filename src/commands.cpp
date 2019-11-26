#include "commands.hpp"
#include <filesystem>
#include <unistd.h>
#include <unordered_map>
namespace filesystem = std::filesystem;

struct {
    std::string vlc = "C:\\Program Files (x86)\\VideoLAN\\VLC\\vlc.exe";
} commands;

struct {
    filesystem::path vids = "C:\\Users\\Seb\\Desktop\\Vids\\";
} folders;

void vlc(std::vector<std::string> text, std::vector<std::string>::iterator it) {
    std::vector<std::string> words;
    // Possible arguments
    for (; it != it+4; ++it) {
        words.push_back(*it);
    }
    // Find files that contain an argument
    std::unordered_map<std::string, int> file_count;
    for (auto& p : filesystem::recursive_directory_iterator(folders.vids)) {
        for (auto it = words.begin(); it != words.end(); ++it) {
            if (p.path().generic_string().find(*it) != std::string::npos) {
                std::pair<std::unordered_map<std::string, int>::iterator,bool> success = file_count.insert(std::make_pair(p.path().generic_string(), 1));
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