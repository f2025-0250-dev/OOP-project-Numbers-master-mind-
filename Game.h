#ifndef GAME_H
#define GAME_H
#include <string>
using namespace std;
class Game
{
protected:
    string name;
    int score;

public:
    Game(string gameName) : name(gameName), score(0) {}
    virtual ~Game() {}
    string getName() const { return name; }
    int getScore() const { return score; }
    virtual void play() = 0;
    virtual void showRules() = 0;
    virtual void resetGame()
    {
        score = 0;
    }
};
#endif
