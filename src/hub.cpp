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
        input += std::tolower(ch);
        ch = getch();
    }
    cbreak();
    return input;
}

int main(int argc, const char** argv) {
    std::vector<Word> thesaurus = initWords("thesauri/opening.thsrs");
    initscr();
    cbreak();
    std::string msg = "Greetings, what would you like to do?\n";
    while (true) {
        clear();
        printw(msg.c_str());
        std::string input = get_input();
        int argPos;
        std::vector<int> inputCodes = procInput(input, thesaurus, argPos);
        for (auto it = inputCodes.begin(); it != inputCodes.end(); ++it) {
            switch (*it)
            {
            case QUIT: {
                exit(EXIT_SUCCESS);
                break;
            }
            case VLC: {
                vlc(format(input), argPos);
                break;
            }
            default:
                break;
            }
        }
        thesaurus = initWords("thesauri/second.thsrs");
        msg = "Anything else?\n";
    }
}