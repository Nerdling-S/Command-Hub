#include "word.hpp"
#include <locale>

// Create a word with a code and set of synonyms
Word::Word(int code, std::set<std::string> syns) {
    code_ = code;
    syns_ = syns;
}

// Check if str is a synonym and return the code
int Word::is(std::string str) {
    std::string lowerStr;
    for (auto it = str.begin(); it != str.end(); ++it) {
        lowerStr.push_back(std::tolower(*it));
    }
    return syns_.count(lowerStr) ? code_ : 0;
}

int Word::getCode() {
    return code_;
}