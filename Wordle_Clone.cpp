#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <cctype>
#include <algorithm>

using namespace std;

int main() {
    srand(time(NULL)); // create a random seed

    // initialzing variables
    vector<string> wordArray;
    ifstream wordlist ("words.txt");
    string word;
    int guessRemaining = 5;
    // get 5 letter words from text file and store in vector
    if (wordlist.is_open()) {
        while (getline(wordlist, word)) {
            if (word.length() == 5) {
                wordArray.push_back(word);
            }
        }
    }

    int randIndex = rand() % wordArray.size(); // create a random index to pick a word from the vector
    string secretWord = wordArray[randIndex];
    string guessWord = "";

    //intro
    cout << "Welcome to Wordle!" << endl;
    cout << "You have 5 guesses to get the correct word." << endl;
    cout << "Incorrect words allow you to narrow down on the correct letters using these rules: " << endl;
    cout << "'+' = correct. '-' = letter not present. '&' = misplaced letter." << endl << endl << endl;

    bool found = false;
    while (guessRemaining > 0) {
        cout << "Enter your guess(five letter word): ";
        cin >> guessWord;
        for (int i = 0; i < guessWord.length(); ++i) {
            guessWord[i] = tolower(guessWord[i]); // converting userinput to lowercase
        }
        if (secretWord == guessWord) {
            cout << "You Win!!" << endl;
            break;
        }
        else if (guessWord.length() != 5) {
            cout << "Enter a five letter word. " << endl << endl;
            continue;
        }
        found = false;
        for (const string& currentWord : wordArray) {
            if (guessWord == currentWord) {
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Word not found. " << endl << endl;
        }
        else {
            --guessRemaining;
            vector<char> letterOccurence; // vector for storing letters occuring in the user's guess
            cout << endl << guessWord << endl;
            for (int i = 0; i < guessWord.length(); ++i) {
                if (guessWord[i] == secretWord[i]) {
                    cout << "+";
                    continue;
                }
                bool letterPresent = false;
                for (int j = 0; j < secretWord.length(); ++j) {
                    //checking for letters in the wrong place and only showing one instance of misplaced letter ( S:infer G:radii &--&- instead of &--&& )
                    if (guessWord[i] == secretWord[j] && (find(letterOccurence.begin(), letterOccurence.end(), guessWord[i]) == letterOccurence.end())) {
                        cout << "&";
                        letterPresent = true; 
                        letterOccurence.push_back(guessWord[i]);
                        break;
                    }
                }
                if (letterPresent == false) {
                    cout << "-";
                }
            }
            cout << endl;
            cout << "You have " << guessRemaining << " guesses remaining." << endl << endl;
            //logic for game over
            if (guessRemaining == 0) {
                cout << "Game Over :(" << endl;
                cout << "The word was '" << secretWord << "' " << endl;
                break;
            }
        }
    }

    return 0;
}