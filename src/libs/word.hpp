#pragma once

#include <string>
#include <set>

class Word {
private:
    int code_;
    std::set<std::string> syns_;
public:
    Word(int, std::set<std::string>);
    int is(std::string);
    int getCode();
};