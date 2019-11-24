#include "libs/lang.hpp"
#include "commands.hpp"
#include <string>
#include <ncurses.h>
#include <vector>

std::string get_input() {
    std::string input;
    nocbreak();
    echo();
    int ch = getch();
    while (ch != '\n') {
        input += ch;
        ch = getch();
    }
    cbreak();
    return input;
}

int main(int argc, const char** argv) {
    std::vector<Word> thesaurus = initWords("../thesaurus.data");
    initscr();
    cbreak();
    while (true) {
        clear();
        printw("Greetings, what would you like to do?");
        std::string input = get_input();
        std::vector<int> inputCodes = procInput(input, thesaurus);
        for (auto it = inputCodes.begin(); it != inputCodes.end(); ++it) {
            switch (*it)
            {
            case QUIT:
                exit(EXIT_SUCCESS);
                break;
            
            default:
                break;
            }
        }
    }
}