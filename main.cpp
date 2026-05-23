// AI Disclosure: Code written with assistance from Claude (Anthropic) - logic and structure by student

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Game.h"
#include "WordScramble.h"       // our group - game 1
#include "NumberMastermind.h"   // our group - game 2
#include "WordSearch.h"         // integrated from another group
using namespace std;

void printBanner()
{
    cout << "\n========================================\n";
    cout << "      PUZZLE CHALLENGE GAME HUB         \n";
    cout << "        CSC-213 OOP Project              \n";
    cout << "========================================\n";
}

void printMenu(const vector<Game*>& games)
{
    cout << "\n  Available Games:\n\n";
    for (int i = 0; i < (int)games.size(); i++)
        cout << "  " << (i + 1) << ". " << games[i]->getName() << "\n";

    cout << "  " << (games.size() + 1) << ". Random Game\n";
    cout << "  0. Quit\n\n";
    cout << "  Choose: ";
}

int main()
{
    srand((unsigned)time(nullptr));
    printBanner();

    // -----------------------------------------------
    // Polymorphism: all games stored as Game* pointers
    // -----------------------------------------------
    vector<Game*> games;
    games.push_back(new WordScramble());        // our group
    games.push_back(new NumberMastermind());    // our group
    games.push_back(new WordSearch());          // integrated from another group

    int choice;
    bool running = true;

    while (running)
    {
        printMenu(games);
        cin >> choice;

        if (choice == 0)
        {
            running = false;
        }
        else if (choice == (int)games.size() + 1)
        {
            // Random game using polymorphism
            int randIndex = rand() % games.size();
            cout << "\n  Randomly selected: " << games[randIndex]->getName() << "!\n";
            games[randIndex]->play();
        }
        else if (choice >= 1 && choice <= (int)games.size())
        {
            // Direct selection using polymorphism
            games[choice - 1]->play();
        }
        else
        {
            cout << "  Invalid choice. Try again.\n";
        }

        if (running)
        {
            cout << "\n  Press Enter to return to menu...";
            cin.ignore();
            cin.get();
        }
    }

    // Clean up memory
    for (Game* g : games) delete g;

    cout << "\n  Thanks for playing! Goodbye.\n\n";
    return 0;
}
