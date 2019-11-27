#include "libs/lang.hpp"
#include "commands.hpp"
#include <algorithm>
#include <ncurses.h>
#include <string>
#include <random>
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

struct {
    std::vector<std::string> first {"Greetings, what would you like to do?", "Oh Great Master, what is your command?",  "What do you wish of me?"};
    std::vector<std::string> other {"Anything else?", "So, what'll it be, Master?", "What d'ya want now!"};
    std::vector<std::string> goodbye {"Well, l can't do any more damage around this Popsicle stand. l'm... outta here!", "You ain't never had a friend like me!"};
    std::string greetFirst() {
        std::vector<std::string> out;
        // Copied
        std::sample(first.begin(), first.end(),
            std::back_inserter(out),
            1, std::mt19937{std::random_device{}()});
        return out[0] + "\n";
    }
    std::string greetNext() {
        std::vector<std::string> out;
        // Copied
        std::sample(other.begin(), other.end(),
            std::back_inserter(out),
            1, std::mt19937{std::random_device{}()});
        return out[0] + "\n";
    }
    std::string bidFarewell() {
        std::vector<std::string> out;
        // Copied
        std::sample(goodbye.begin(), goodbye.end(),
            std::back_inserter(out),
            1, std::mt19937{std::random_device{}()});
        return out[0] + "\n";
    }
} greeting;

int main(int argc, const char** argv) {
    std::vector<Word> thesaurus = initWords("thesauri/opening.thsrs");
    initscr();
    cbreak();
    std::string msg = greeting.greetFirst();
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
                clear();
                printw(greeting.bidFarewell().c_str());
                refresh();
                nanosleep((const struct timespec[]){{1, 0}}, (struct timespec*)NULL);
                endwin();
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
        msg = greeting.greetNext();
    }
}