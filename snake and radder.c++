#include <iostream>
#include <map>
#include <cstdlib>   // For rand() and srand()
#include <ctime>     // For time()

using namespace std;

// Function to roll the dice
int rollDice() {
    return rand() % 6 + 1; // Generates a random number between 1 and 6
}

// Function to initialize the snakes and ladders on the board
void initializeBoard(map<int, int> &snakes, map<int, int> &ladders) {
    // Snakes: Maps head position to tail position
    snakes[16] = 6;
    snakes[47] = 26;
    snakes[49] = 11;
    snakes[56] = 53;
    snakes[62] = 19;
    snakes[64] = 60;
    snakes[87] = 24;
    snakes[93] = 73;
    snakes[95] = 75;
    snakes[98] = 78;

    // Ladders: Maps bottom position to top position
    ladders[1] = 38;
    ladders[4] = 14;
    ladders[9] = 31;
    ladders[21] = 42;
    ladders[28] = 84;
    ladders[36] = 44;
    ladders[51] = 67;
    ladders[71] = 91;
    ladders[80] = 100;
}

// Function to check for snakes or ladders
int checkSnakesAndLadders(int playerPosition, map<int, int> &snakes, map<int, int> &ladders) {
    if (snakes.find(playerPosition) != snakes.end()) {
        cout << "Oops! You landed on a snake at position " << playerPosition << ". Sliding down to " << snakes[playerPosition] << "." << endl;
        return snakes[playerPosition];  // Move down to the tail of the snake
    } else if (ladders.find(playerPosition) != ladders.end()) {
        cout << "Yay! You found a ladder at position " << playerPosition << ". Climbing up to " << ladders[playerPosition] << "." << endl;
        return ladders[playerPosition];  // Move up to the top of the ladder
    }
    return playerPosition;
}

// Function for the main game logic
void playGame() {
    srand(time(0)); // Initialize random seed

    int player1Position = 0;
    int player2Position = 0;
    bool player1Turn = true;
    map<int, int> snakes;
    map<int, int> ladders;

    initializeBoard(snakes, ladders);

    while (true) {
        int diceRoll = rollDice();
        cout << "Player " << (player1Turn ? 1 : 2) << " rolled a " << diceRoll << "." << endl;

        if (player1Turn) {
            player1Position += diceRoll;
            if (player1Position > 100) player1Position -= diceRoll; // Prevents overshooting beyond 100
            player1Position = checkSnakesAndLadders(player1Position, snakes, ladders);
            cout << "Player 1 is now on position " << player1Position << "." << endl;
            if (player1Position == 100) {
                cout << "Congratulations! Player 1 wins!" << endl;
                break;
            }
        } else {
            player2Position += diceRoll;
            if (player2Position > 100) player2Position -= diceRoll; // Prevents overshooting beyond 100
            player2Position = checkSnakesAndLadders(player2Position, snakes, ladders);
            cout << "Player 2 is now on position " << player2Position << "." << endl;
            if (player2Position == 100) {
                cout << "Congratulations! Player 2 wins!" << endl;
                break;
            }
        }

        player1Turn = !player1Turn; // Switch turns
        cout << "---------------------------------" << endl;
    }
}

// Main function
int main() {
    cout << "Welcome to Snakes and Ladders!" << endl;
    playGame();
    return 0;
}
