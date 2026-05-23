

#ifndef NUMBERMASTERMIND_H
#define NUMBERMASTERMIND_H

#include "Game.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iomanip>
using namespace std;

struct GuessResult
{
    int exact;
    int misplaced;
};

class NumberMastermind : public Game
{
private:
    int digits;
    int maxAttempts;
    string secretNumber;
    int attemptsTaken;
    string playerName;

    string generateSecret()
    {
        vector<int> pool = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

        for (int i = 9; i > 0; i--)
        {
            int j = rand() % (i + 1);
            swap(pool[i], pool[j]);
        }
        string secret = "";

        int start = (pool[0] == 0) ? 1 : 0;
        secret += to_string(pool[start]);
        int count = 1;
        for (int i = 0; i < 10 && count < digits; i++)
        {
            if (i != start)
            {
                secret += to_string(pool[i]);
                count++;
            }
        }
        return secret;
    }

    bool isValidGuess(const string &guess)
    {
        if ((int)guess.size() != digits)
        {
            cout << "  Please enter exactly " << digits
                 << " digits.\n";
            return false;
        }
        for (char c : guess)
        {
            if (!isdigit(c))
            {
                cout << "  Only digits allowed!\n";
                return false;
            }
        }

        for (int i = 0; i < (int)guess.size(); i++)
            for (int j = i + 1; j < (int)guess.size(); j++)
                if (guess[i] == guess[j])
                {
                    cout << "  No repeated digits allowed!\n";
                    return false;
                }
        return true;
    }

    GuessResult evaluate(const string &guess)
    {
        GuessResult result = {0, 0};
        for (int i = 0; i < digits; i++)
        {
            if (guess[i] == secretNumber[i])
            {
                result.exact++;
            }
            else
            {

                for (int j = 0; j < digits; j++)
                {
                    if (i != j && guess[i] == secretNumber[j])
                    {
                        result.misplaced++;
                        break;
                    }
                }
            }
        }
        return result;
    }

    void drawFeedbackBar(const GuessResult &r)
    {
        cout << "  Feedback: ";
        for (int i = 0; i < r.exact; i++)
            cout << "✓ ";
        for (int i = 0; i < r.misplaced; i++)
            cout << "○ ";
        for (int i = 0; i < digits - r.exact - r.misplaced; i++)
            cout << "✗ ";
        cout << "  (" << r.exact << " correct, "
             << r.misplaced << " misplaced)\n";
    }

    void saveScore()
    {
        ofstream file("scores.txt", ios::app);
        if (file.is_open())
        {
            file << playerName << " | Digits: " << digits
                 << " | Score: " << score
                 << " | Attempts: " << attemptsTaken << "\n";
            file.close();
        }
    }

    void showLeaderboard()
    {
        ifstream file("scores.txt");
        if (!file.is_open())
            return;
        cout << "\n--- Leaderboard (all-time) ---\n";
        string line;
        int rank = 1;
        while (getline(file, line) && rank <= 10)
        {
            cout << "  " << rank++ << ". " << line << "\n";
        }
        file.close();
    }

    void chooseDifficulty()
    {
        cout << "\n  Choose difficulty:\n";
        cout << "    1. Easy   (3 digits, 8 attempts)\n";
        cout << "    2. Medium (4 digits, 8 attempts)\n";
        cout << "    3. Hard   (5 digits, 7 attempts)\n";
        cout << "  Your choice (1-3): ";
        int d;
        cin >> d;
        switch (d)
        {
        case 1:
            digits = 3;
            maxAttempts = 8;
            break;
        case 3:
            digits = 5;
            maxAttempts = 7;
            break;
        default:
            digits = 4;
            maxAttempts = 8;
            break;
        }
    }

public:
    NumberMastermind()
        : Game("Number Mastermind"),
          digits(4), maxAttempts(8),
          attemptsTaken(0), playerName("Player")
    {
        srand((unsigned)time(nullptr));
    }

    void showRules() override
    {
        cout << "\n========================================\n";
        cout << "       NUMBER MASTERMIND - RULES\n";
        cout << "========================================\n";
        cout << "  • Computer picks a secret number.\n";
        cout << "  • No digit repeats in the secret.\n";
        cout << "  • Guess the number within attempts.\n";
        cout << "  • After each guess you get:\n";
        cout << "      ✓ = right digit, right position\n";
        cout << "      ○ = right digit, wrong position\n";
        cout << "      ✗ = digit not in secret number\n";
        cout << "  • Fewer attempts = higher score!\n";
        cout << "  • Top scores saved to leaderboard.\n";
        cout << "========================================\n";
    }

    void play() override
    {
        showRules();
        resetGame();

        cout << "\n  Enter your name: ";
        cin >> playerName;

        chooseDifficulty();
        secretNumber = generateSecret();

        cout << "\n  Secret number generated! (" << digits
             << " digits, " << maxAttempts << " attempts)\n";
        cout << "  Good luck, " << playerName << "!\n\n";

        bool won = false;
        vector<pair<string, GuessResult>> history;

        while (attemptsTaken < maxAttempts)
        {
            int remaining = maxAttempts - attemptsTaken;
            cout << "  Attempt " << (attemptsTaken + 1)
                 << "/" << maxAttempts
                 << "  (remaining: " << remaining << ")\n";
            cout << "  Your guess: ";

            string guess;
            cin >> guess;

            if (!isValidGuess(guess))
                continue;

            attemptsTaken++;
            GuessResult result = evaluate(guess);
            history.push_back({guess, result});

            cout << "\n  --- History ---\n";
            for (auto &h : history)
            {
                cout << "  " << setw(digits + 1) << left
                     << h.first << "  ";
                drawFeedbackBar(h.second);
            }
            cout << "\n";

            if (result.exact == digits)
            {
                won = true;
                break;
            }
        }

        if (won)
        {
            int base = digits * 100;
            int bonus = (maxAttempts - attemptsTaken) * 20;
            score = base + bonus;
            cout << "  ★ Excellent! You cracked the code in "
                 << attemptsTaken << " attempt(s)!\n";
            cout << "  Score: " << base << " (base) + "
                 << bonus << " (speed bonus) = "
                 << score << "\n";
            saveScore();
        }
        else
        {
            cout << "  The secret number was: "
                 << secretNumber << "\n";
            cout << "  Better luck next time!\n";
            score = 0;
        }

        char view;
        cout << "\n  View leaderboard? (y/n): ";
        cin >> view;
        if (tolower(view) == 'y')
            showLeaderboard();

        cout << "\n========================================\n";
        cout << "      GAME OVER - Number Mastermind\n";
        cout << "  Final Score: " << score << "\n";
        cout << "========================================\n";
    }

    void resetGame() override
    {
        Game::resetGame();
        attemptsTaken = 0;
        secretNumber = "";
    }
};

#endif
