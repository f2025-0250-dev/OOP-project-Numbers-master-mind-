# PuzzleChallenge Game Hub
## CSC-213 Object-Oriented Programming Project

---

## Files

| File | Purpose |
|------|---------|
| `Game.h` | Base class provided by instructor (abstract) |
| `WordScramble.h` | Game 1 - Word Scramble (derived from Game) |
| `NumberMastermind.h` | Game 2 - Number Mastermind (derived from Game) |
| `main.cpp` | Game Hub with polymorphic random selection |
| `words.txt` | Word list data file for WordScramble |
| `scores.txt` | Auto-generated leaderboard (Number Mastermind) |

---

## How to Compile & Run

```bash
g++ main.cpp -o GameHub
./GameHub
```

---

## Game 1: Word Scramble

A scrambled version of a programming-related word is shown.
The player must unscramble it.

- 3 lives per word
- Type `hint` for a clue (costs 1 life)
- Type `skip` to skip the word
- More lives remaining = more points
- Words loaded from `words.txt` (File Handling)

**OOP Concepts:** Inheritance, Encapsulation, Polymorphism,
Composition (WordEntry struct), File Handling

---

## Game 2: Number Mastermind

The computer picks a secret number with no repeated digits.
The player guesses it within a limited number of attempts.

- After each guess: ✓ = right digit right place, ○ = right digit wrong place
- 3 difficulty levels (3, 4, or 5 digits)
- Scores saved to `scores.txt` leaderboard (File Handling)
- Fewer attempts = higher bonus score

**OOP Concepts:** Inheritance, Encapsulation, Polymorphism,
Composition (GuessResult struct), File Handling (leaderboard)

---

## Polymorphism Demo

`main.cpp` stores all games in a `vector<Game*>`.
The random game feature uses `rand()` to pick an index
and calls `games[i]->play()` — virtual dispatch selects
the correct derived class at runtime.

---

## AI Disclosure

Claude (Anthropic) was used to assist in generating parts
of this code. All code has been reviewed and understood
by the student. This is disclosed inside each file header.
