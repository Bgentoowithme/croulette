#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h> // for sleep function
#include <time.h> // to use time as seed
#include <string.h> // for string compare function

#define straightup 35
#define twotoone 2
#define onetoone 1

int roulette[] = {0, 32, 15, 19, 4, 21, 2, 25, 17, 34, 6, 27, 13,  // printed twice so the graphics function properly
                  36, 11, 30, 8, 23, 10, 5, 24, 16, 33, 1, 20, 14,
                  31, 9, 22, 18, 29, 7, 28, 12, 35, 3, 26, 0, 32, 15, 19, 4, 21, 2, 25, 17, 34, 6, 27, 13,
                  36, 11, 30, 8, 23, 10, 5, 24, 16, 33, 1, 20, 14,
                  31, 9, 22, 18, 29, 7, 28, 12, 35, 3, 26};
int evens[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36};
int odds[] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35};
int reds[] = {32, 19, 21, 25, 34, 27, 36, 30, 23, 5, 16, 1, 14, 9, 18, 7, 12, 3};
int blacks[] = {15, 4, 2, 17, 6, 13, 11, 8, 10, 24, 33, 20, 31, 22, 29, 28, 35, 26};
int to18[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18};
int to36[] = {19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36};
int col1[] = {1, 4, 7, 10, 13, 16, 19, 22, 25, 28, 31, 34};
int col2[] = {2, 5, 8, 11, 14, 17, 20, 23, 26, 29, 32, 35};
int col3[] = {3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36};
int dozen1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
int dozen2[] = {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};
int dozen3[] = {25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36};

// function prototypes
void graphic(int lnum); // emulates the roulette wheel spinning
int win(char num[], int lnum, int bet, int *money, int *twin, int *tloss); // calculates the win/loss
void ansicolour(int colour); // to change terminal colour
void ansicolourbold(int colour); // to change terminal colour but in bold

int main() {
    int twin = 0;
    int tloss = 0;
    int money = 10;
    char playagain;
    struct lnumhistory {
        int runs; // keeps track of how many time program as been looped through so lastlnums knows how much of the array to display
        int lastlnums[1000]; // array to store previous lnums
    };

    struct lnumhistory a = {0,{}};
    // initialising the last of varibales and generates a seed
    do {
        int seed, bet;
        char TOC;
        char num[5] = "    ";
        do {
            printf("\nUse time as seed? (y/n): ");
            scanf(" %c", &TOC);
            
            if (TOC == 'y' || TOC == 'Y') {
                srand(time(NULL));
            } else if (TOC == 'n' || TOC =='N') {
                printf("Please enter a valid seed value to be used: \n");
                scanf("%d", &seed);
                srand(seed);
            } else {
                ansicolourbold(31);
                printf("PLEASE");
                ansicolour(0);
                printf(" enter a valid value and stop trying to break me :( ");
            }
        } while (TOC != 'y' && TOC != 'Y' && TOC && 'n' && TOC != 'N' );

        // uses the seed to generate a random number between 0 and 36
        int lnum = rand() % 36 + 0;
        a.lastlnums[a.runs] = lnum;
        a.runs++;

        // asks user for the bet and logic for if bet>money
        do {
            printf("bet? ");
            while (scanf("%d", &bet) != 1) {
                // Clear the input buffer
                while (getchar() != '\n');
                printf("please enter any postive integer: ");
            }
        } while (bet <= 0); // ensures the bet is positive
        
        if (money < bet){
            printf("You don't have enough ");
            // sets console text colour to red and bold
            ansicolourbold(31);
            printf("MONEY");
            // sets console text back to default
            ansicolour(0);
            printf("! Please come back once you've made some more :)\n");
            exit(EXIT_FAILURE);
        }

        // asks user to select a valid set to place their bets on
        do {
            printf("What are you placing bets on? ");
            scanf(" %s", num);
            
            if (!(strcmp(num, "r") == 0 || strcmp(num, "b") == 0 || strcmp(num, "o") == 0 || strcmp(num, "e") == 0 || strcmp(num, "to18") == 0 || strcmp(num, "to36") == 0 || strcmp(num, "col1") == 0 || strcmp(num, "col2") == 0 || strcmp(num, "col3") == 0 || strcmp(num, "doz1") == 0 || strcmp(num, "doz2") == 0 || strcmp(num, "doz3") == 0 || strcmp(num, "R") == 0 || strcmp(num, "B") == 0 || strcmp(num, "O") == 0 || strcmp(num, "E") == 0 || strcmp(num, "TO18") == 0 || strcmp(num, "TO36") == 0 || strcmp(num, "COL1") == 0 || strcmp(num, "COL2") == 0 || strcmp(num, "COL3") == 0 || strcmp(num, "DOZ1") == 0 || strcmp(num, "DOZ2") == 0 || strcmp(num, "DOZ3") == 0)) {
                ansicolourbold(31);
                printf("\nHEY!");
                ansicolour(0);
                printf("\nThat's an invalid bet!\n");
            }
        } while (!(strcmp(num, "r") == 0 || strcmp(num, "b") == 0 || strcmp(num, "o") == 0 || strcmp(num, "e") == 0 || strcmp(num, "to18") == 0 || strcmp(num, "to36") == 0 || strcmp(num, "col1") == 0 || strcmp(num, "col2") == 0 || strcmp(num, "col3") == 0 || strcmp(num, "doz1") == 0 || strcmp(num, "doz2") == 0 || strcmp(num, "doz3") == 0 || strcmp(num, "R") == 0 || strcmp(num, "B") == 0 || strcmp(num, "O") == 0 || strcmp(num, "E") == 0 || strcmp(num, "TO18") == 0 || strcmp(num, "TO36") == 0 || strcmp(num, "COL1") == 0 || strcmp(num, "COL2") == 0 || strcmp(num, "COL3") == 0 || strcmp(num, "DOZ1") == 0 || strcmp(num, "DOZ2") == 0 || strcmp(num, "DOZ3") == 0));

        // runs the "graphics" and win/loss logic
        printf("-----\n");
        graphic(lnum);
        printf("| %d |", lnum);
        printf("\n-----\n");
        win(num, lnum, bet, &money, &twin, &tloss);

        printf("\n Your money: %d\n", money);
        
        // print out the previously randomly generated numbers with colour (using ANSI escape codes)
        printf("Previous lnums: ");
        for (int i = 0; i < a.runs; i++) {
            if (a.lastlnums[i] == 0) {
                // print 0s in green
                ansicolour(32);
                printf("\033[0;32m%d \033[0m", a.lastlnums[i]);
            } else {
                // check if the number is red
                int isRed = 0;
                for (int j = 0; j < sizeof(reds) / sizeof(reds[0]); j++) {
                    if (a.lastlnums[i] == reds[j]) {
                        isRed = 1;
                        break; // used to improve performance so array stops checking once it's confirmed that lnum is indeed red
                    }
                }
                if (isRed) {
                    // print red numbers in red
                    ansicolour(31);
                    printf("\033[0;31m%d \033[0m", a.lastlnums[i]);
                } else {
                    // print other numbers in default colour
                    ansicolour(0);
                    printf("%d ", a.lastlnums[i]);
                }
            }
        }
        printf("\n");
        printf("\n total win %d\n total loss %d", twin , tloss);

        printf("\nDo you want to play again? (y/n): ");
        scanf(" %c", &playagain);
    } while (playagain == 'y' || playagain == 'Y');

    printf("Thanks for playing! Come again :)\n");
    return 0;
}

void graphic(int lnum) {
    int n = rand() % 36 + 0;
        do {
        printf("| %d |\r", roulette[n]); // refreshes said line (doesn't start a new one). loops through the roulette array. this only "emulates" the roulette spinning
        fflush(stdout);
        usleep(500000); // creates the spinning effect
        n++;
    } while (lnum != roulette[n]);
}

int win(char num[5], int lnum, int bet, int *money, int *twin, int *tloss) {
    printf("num is %s", num); // debug print
    
    if ((strncmp(num, "e", 1) != 0 || strncmp(num, "o", 1) != 0 || strncmp(num, "r", 1) != 0 || strncmp(num, "b", 1) != 0 || strncmp(num, "to18", 4) != 0 || strncmp(num, "to36", 4) != 0 || strncmp(num, "col1", 4) != 0 || strncmp(num, "col2", 4) != 0 || strncmp(num, "col3", 4) != 0 || strncmp(num, "doz1", 4) != 0 || strncmp(num, "doz2", 4) != 0 || strncmp(num, "doz3", 4) != 0) && atoi(num) == lnum) {
        printf("\ncongrats");
        *money = *money + straightup * bet;
        *twin = *twin + bet * straightup;
        return *twin;
        return *money;
    } else if (strncmp(num, "e", 1) == 0) {
        for (int i = 0; i < sizeof(evens) / sizeof(evens[0]); i++) {
            if (evens[i] == lnum) {
                printf("\nCurrent money: %d, Bet: %d", *money, bet); // Debug print
                printf("\ncongrats");
                *money = *money + bet * onetoone;
                *twin = *twin + bet * onetoone;
                printf("\nUpdated money: %d", *money); // Debug print
                return *money;
                return *twin;
            }
        }
    } else if (strncmp(num, "o", 1) == 0) {
        for (int i = 0; i < sizeof(odds) / sizeof(odds[0]); i++) {
            if (odds[i] == lnum) {
                printf("\ncongrats");
                *money = *money + bet * onetoone;
                *twin = *twin + bet * onetoone;
                return *money;
                return *twin;
            }
        }
    } else if (strncmp(num, "r", 1) == 0) {
        for (int i = 0; i < sizeof(reds) / sizeof(reds[0]); i++) {
            if (reds[i] == lnum) {
                printf("\nCurrent money: %d, Bet: %d", *money, bet); // Debug print
                printf("\ncongrats");
                *money = *money + bet * onetoone;
                *twin = *twin + bet * onetoone;
                printf("\nUpdated money: %d", *money); // Debug print
                return *money;
                return *twin;
            }
        }
    } else if (strncmp(num, "b", 1) == 0) {
        for (int i = 0; i < sizeof(blacks) / sizeof(blacks[0]); i++) {
            if (blacks[i] == lnum) {
                printf("\ncongrats");
                *money = *money + bet * onetoone;
                *twin = *twin + bet * onetoone;
                return *money;
                return *twin;
            }
        }
    } else if (strncmp(num, "to18", 4) == 0) {
        for (int i = 0; i < sizeof(to18) / sizeof(to18[0]); i++) {
            if (to18[i] == lnum) {
                printf("\ncongrats");
                *money = *money + bet * onetoone;
                *twin = *twin + bet * onetoone;
                return *money;
                return *twin;
            }
        }
    } else if (strncmp(num, "to36", 4) == 0) {
        for (int i = 0; i < sizeof(to36) / sizeof(to36[0]); i++) {
            if (to36[i] == lnum) {
                printf("\ncongrats");
                *money = *money + bet * onetoone;
                *twin = *twin + bet * onetoone;
                return *money;
                return *twin;
            }
        }
    } else if (strncmp(num, "col1", 4) == 0) {
        for (int i = 0; i < sizeof(col1) / sizeof(col1[0]); i++) {
            if (col1[i] == lnum) {
                printf("\ncongrats");
                *money = *money + bet * twotoone;
                *twin = *twin + bet * twotoone;
                return *money;
                return *twin;
            }
        }
    } else if (strncmp(num, "col2", 4) == 0) {
        for (int i = 0; i < sizeof(col2) / sizeof(col2[0]); i++) {
            if (col2[i] == lnum) {
                printf("\ncongrats");
                *money = *money + bet * twotoone;
                *twin = *twin + bet * twotoone;
                return *money;
                return *twin;
            }
        }
    } else if (strncmp(num, "col3", 4) == 0) {
        for (int i = 0; i < sizeof(col3) / sizeof(col3[0]); i++) {
            if (col3[i] == lnum) {
                printf("\ncongrats");
                *money = *money + bet * twotoone;
                *twin = *twin + bet * twotoone;
                return *money;
                return *twin;
            }
        }
    } else if (strncmp(num, "doz1", 4) == 0) {
        for (int i = 0; i < sizeof(dozen1) / sizeof(dozen1[0]); i++) {
            if (dozen1[i] == lnum) {
                printf("\ncongrats");
                *money = *money + bet * twotoone;
                *twin = *twin + bet * twotoone;
                return *money;
                return *twin;
            }
        }
    } else if (strncmp(num, "doz2", 4) == 0) {
        for (int i = 0; i < sizeof(dozen2) / sizeof(dozen2[0]); i++) {
            if (dozen2[i] == lnum) {
                printf("\ncongrats");
                *money = *money + bet * twotoone;
                *twin = *twin + bet * twotoone;
                return *money;
                return *twin;
            }
        }
    } else if (strncmp(num, "doz3", 4) == 0) {
        for (int i = 0; i < sizeof(dozen3) / sizeof(dozen3[0]); i++) {
            if (dozen3[i] == lnum) {
                printf("\ncongrats");
                *money = *money + bet * twotoone;
                *twin = *twin + bet * twotoone;
                return *money;
                return *twin;
            }
        }
    } 
    printf("\nbetter luck next time");
    printf("\nCurrent money: %d, Bet: %d", *money, bet); // Debug print
    *money = *money - bet;
    *tloss = *tloss + bet;
    printf("\nUpdated money: %d", *money); // Debug print
    return *money;
    return *tloss;
}

void ansicolour(int colour) {
    printf("\033[0;%dm", colour);
}

void ansicolourbold(int colour) {
    printf("\033[1;%dm", colour);
}
