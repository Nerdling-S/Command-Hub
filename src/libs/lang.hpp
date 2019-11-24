#pragma once

#include "langUtils.hpp"
#include "word.hpp"
#include <string>
#include <vector>

enum {
    VLC = -1,
    QUIT = 100
};

std::vector<std::string> args;

std::vector<Word> initWords();

std::vector<std::string> format(std::string);

std::vector<int> toCodes(std::vector<std::string>, std::vector<Word>);

bool isModifier(int);

std::vector<int> modify(std::vector<int>);

void order(std::vector<int>&, std::vector<Word>);

std::vector<int> procInput(std::string, std::vector<Word>);