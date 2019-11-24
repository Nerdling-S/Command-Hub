#include "langUtils.hpp"
#include <fstream>
#include <ncurses.h>
#include <sstream>

// Pull file text as string
std::string fileInput(std::string file) {
    std::ifstream inFile(file.c_str()); // filestream
    std::stringstream inString;
    if (!inFile.is_open()) {
        return "";
    }
    inString << inFile.rdbuf(); // file -> string
    return inString.str();
}

// Decode string -> code-set pairs
std::vector<std::pair<int, std::set<std::string>>> decode(std::string data) {
    std::vector<std::pair<int, std::set<std::string>>> vec;
    std::istringstream dataStream(data);    
    std::string line;
    // Line-by-line loop
    while (getline(dataStream, line)) {
        std::string s_code = line.substr(0,line.find_first_of(':'));    // everything before ':' = code
        int code = std::stoi(s_code);   // string-to-int of code
        std::set<std::string> words;
        std::string word;
        unsigned int i = s_code.length() + 1;   // start from first letter character
        // Character-by-character loop
        while (i < line.length()) {
            if (line[i] == ',') {
                words.insert(words.end(), word);    // push word to back of set
                word = "";
            } else if (!std::ispunct(line[i])) {
                word += line[i];
            }
            i++;
        }
        words.insert(words.end(), word);    // push word to back of set
        // Pair code and words
        std::pair<int, std::set<std::string>> pair = std::make_pair(code, words);
        vec.push_back(pair);
    }
    return vec;
}