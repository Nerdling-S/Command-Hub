#include "lang.hpp"
#include <algorithm>
#include <unordered_map>

// Initialise vector of Words from file:thesaurus.data
std::vector<Word> initWords(std::string file) {
    std::vector<Word> words;
    // Decode thesaurus.data -> pairs of codes and string-sets
    std::vector<std::pair<int, std::set<std::string>>> thesaurus = decode(fileInput(file));
    for (auto it = thesaurus.begin(); it != thesaurus.end(); ++it) {
        // Add a word with a code and list of synonyms
        words.push_back(Word(it->first, it->second));
    }
    return words;
}

// Split input into words
std::vector<std::string> format(std::string input) {
    std::vector<std::string> words;
    std::string word;
    // Loop over every character
    for (auto it = input.begin(); it != input.end(); ++it) {
        // If it's a space, end of word, otherwise add another character
        if (*it == ' ') {
            words.push_back(word);
            word = "";
        } else if (!std::ispunct(*it)) {
            word += *it;
        }
    }
    words.push_back(word);
    return words;
}

// Convert a phrase to a vector of codes
std::vector<int> toCodes(std::vector<std::string> text, std::vector<Word> wordList, std::vector<std::vector<std::string>::iterator> &argIts) {
    // meaningful words -> codes, 'useless' words discarded
    std::vector<int> codes;
    for (auto it = text.begin(); it != text.end(); ++it) {
        for (auto jt = wordList.begin(); jt != wordList.end(); ++jt) {
            int code = jt->is(*it);
            if (code != 0) {
                if (isModifier(code)) {
                    argIts.push_back(it);
                }
                codes.push_back(code);
                break;
            }
        }
    }
    return codes;
}

// Compare code with list of known modifiers
bool isModifier(int code) {
    std::set<int> mods {VLC};
    return mods.count(code);
}

// Calculate modifiers, such as 'not'
std::vector<int> modify(std::vector<int> codes) {
    std::vector<int> new_codes;
    for (auto it = codes.begin(); it != codes.end(); ++it) {
        if (isModifier(*it)) {
            new_codes.push_back((*it) * *(++it));
        } else {
            new_codes.push_back(*it);
        }
    }
    return new_codes;
}

// Order the codes, e.g. quit last
void order(std::vector<int> &codes, std::vector<Word> wordOrder) {
    std::unordered_map<int, int> code_order;
    std::vector<int> orderedCodes;
    for (unsigned int i = 0; i < wordOrder.size(); i++) {
        code_order.insert(std::make_pair(wordOrder[i].getCode(), i));
    }
    auto compareKeys = [=, &code_order](int a, int b){ return code_order[a] < code_order[b]; };
    std::sort(codes.begin(), codes.end(), compareKeys);
}

// Process input into a vector of command-codes
std::vector<int> procInput(std::string input, std::vector<Word> wordList, std::vector<std::vector<std::string>::iterator> &argIts) {
    std::vector<int> codes = toCodes(format(input), wordList, argIts);
    //codes = modify(codes);
    order(codes, wordList);
    return codes;
}