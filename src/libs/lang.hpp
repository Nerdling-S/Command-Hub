#pragma once

#include "langUtils.hpp"
#include "word.hpp"
#include <string>
#include <vector>

enum {
    VLC = -2,
    NOT = -1,
    QUIT = 100
};

std::vector<Word> initWords(std::string);

std::vector<std::string> format(std::string);

bool takesArgs(int);

template <class RandomAccessIterator>
std::vector<int> toCodes(std::vector<std::string>, std::vector<Word>, RandomAccessIterator);

bool isModifier(int);

std::vector<int> modify(std::vector<int>);

void order(std::vector<int>&, std::vector<Word>);

template <class RandomAccessIterator>
std::vector<int> procInput(std::string, std::vector<Word>, RandomAccessIterator);