#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WINNING_POSITION 100
#define SIZE 10
#define NUM_SNAKES_LADDERS 6

int start[NUM_SNAKES_LADDERS];
int destination [NUM_SNAKES_LADDERS];
char *colors[NUM_SNAKES_LADDERS] = {"🔴", "🟠", "🟡", "🟢", "🔵", "🟣"};

struct Player{
    char name[50];
    int state;          //win or lose
    int playerPosition; // player position
};

void displayTitle(){
    printf("\n");
    printf("🎲🐍 WELCOME TO SNAKES AND LADDERS! 🪜🎲\n");
    printf("=========================================\n");
    printf("|   Roll the dice and test your luck!\t|\n");
    printf("|   Watch out for snakes! 🐍\t\t|\n");
    printf("|   Climb the ladders! 🪜\t\t|\n");
    printf("=========================================\n\n");
}

int rollDice(){
    return (rand() % 6) + 1;
}

// Generate snakes and ladders randomly
void generateSnakesAndLadders() {
    for (int i = 0; i < NUM_SNAKES_LADDERS; i++) {
        int s = (rand() % (WINNING_POSITION - 10)) + 2;  // Avoid very low/high positions
        int d = (rand() % (WINNING_POSITION - 10)) + 2;

        while (s == d) { // Ensure they aren't the same
            d = (rand() % (WINNING_POSITION - 10)) + 2;
        }

        start[i] = s;
        destination[i] = d;
    }
}

int snakeOrLadder(int position) {
    for (int i = 0; i < NUM_SNAKES_LADDERS; i++) {
        if (start[i] == position) {
            return destination[i];
        }
    }
    return position;
}

// Find color for a specific position
char *getPositionColor(int position) {
    for (int i = 0; i < NUM_SNAKES_LADDERS; i++) {
        if (start[i] == position || destination[i] == position) {
            return colors[i];  // Correctly assigns the color
        }
    }
    return "⬜"; // Default empty square
}

// Display board with snakes/ladders & players
void displayBoard(int p1, int p2) {
    printf("\n🎲 Snakes and Ladders Board 🎲\n");

    for (int a = 0; a < NUM_SNAKES_LADDERS; a++) {
        if (start[a] < destination[a]) {
            printf("Ladder: %2d → %2d %s\n", start[a], destination[a], colors[a]);
        } else {
            printf("Snake:  %2d → %2d %s\n", start[a], destination[a], colors[a]);
        }
    }

    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            int pos = (SIZE - 1 - i) * SIZE;

            if ((SIZE - 1 - i) % 2 == 0) {
                pos += j + 1;
                printf("> ");
            } else {
                pos += (SIZE - j);
                printf("< ");
            }

            char *tile = getPositionColor(pos);

            if (pos == p1 && pos == p2)
                printf("12 ");
            else if (pos == p1)
                printf("1  ");
            else if (pos == p2)
                printf("2  ");
            else
                printf("%s ", tile);
        }
        printf("\n");
    }
}

int main(){
    /*
        player1 and player2 will be set to 0, indicating that
        no one has won, game ends if player 1 OR player 2 wins
        the game
    */
    struct Player p1, p2;
    srand(time(NULL));
    int answer = 1;
    while (answer == 1){
        system("clear");
        int playerTurn = 1; // 1 for p1, 2 for p2

        displayTitle();
        printf("\n");

        printf("Enter Player 1's Name: ");
        scanf("%s", p1.name);
        printf("Enter Player 2's Name: ");
        scanf("%s", p2.name);

        getchar();

        p1.state = 0;
        p2.state = 0;

        p1.playerPosition = 1;
        p2.playerPosition = 1;

        printf("🎲🐍 Gameboard 🪜🎲\n");
        generateSnakesAndLadders();
        displayBoard(p1.playerPosition, p2.playerPosition);
        printf("\n\nPress Enter to Start\n");
        getchar();
        system("clear");

        while(p1.state == 0 && p2.state == 0){
            // Start Turn
            printf("\n");
            if (playerTurn == 1)
                printf("%s's [1] turn. Press ENTER to roll the dice...\n", p1.name);
            else
                printf("%s's [2] turn. Press ENTER to roll the dice...\n", p2.name);

            getchar();

            int dice = rollDice();
            int newPosition = 0; // New position of the player in case of snake or ladder

            system("clear");

            if(playerTurn == 1){
                printf("%s rolled a %d!\n", p1.name, dice);

                p1.playerPosition += dice;
                if(p1.playerPosition >= WINNING_POSITION){
                    p1.playerPosition = WINNING_POSITION;
                    p1.state = 1;
                }

                newPosition = snakeOrLadder(p1.playerPosition);
                if (newPosition != 0){
                    if (newPosition > p1.playerPosition)
                        printf("🎉 %s [1] climbed a ladder to %d!\n", p1.name, newPosition);
                    if (newPosition < p1.playerPosition)
                        printf("🐍 %s [1] was bitten by a snake and fell to %d!\n", p1.name, newPosition);
                    p1.playerPosition = newPosition;

                    newPosition = 0;
                }

            }
            else if(playerTurn == 2){
                printf("%s rolled a %d!\n", p2.name, dice);
                p2.playerPosition += dice;
                if(p2.playerPosition >= WINNING_POSITION){
                    p2.playerPosition = WINNING_POSITION;
                    p2.state = 1;
                }

                newPosition = snakeOrLadder(p2.playerPosition);
                if (newPosition != 0){
                    if (newPosition > p2.playerPosition)
                        printf("🎉 %s [2] climbed a ladder to %d!\n", p2.name, newPosition);
                    if (newPosition < p2.playerPosition) 
                        printf("🐍 %s [2] was bitten by a snake and fell to %d!\n", p2.name, newPosition);
                    p2.playerPosition = newPosition;

                    newPosition = 0;
                }
            }
            else
                printf("Debugging Purposes\n");

            displayBoard(p1.playerPosition, p2.playerPosition);

            if (playerTurn == 1)

                playerTurn++;
            else
                playerTurn--;
        }

        if (p1.state == 1)
            printf("%s Wins!\n", p1.name);
        else
            printf("%s Wins!\n", p2.name);

        if (p1.state == 1 || p2.state == 1){
            printf("Do you want to Play Again? [Press 1 to Play Again, Press Any Other Key to Stop]: ");
            scanf("%d", &answer);
        }

    }

    return 0;
}