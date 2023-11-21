#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int ROWS = 6;
const int COLS = 8;
const char TREASURE = 'T';
const char UNDISCOVERED = '#';
const char MINE = '*';
const char FLAG = 'F';

// Function prototypes
void initializeMap(char map[ROWS][COLS]);
void placeTreasure(char map[ROWS][COLS]);
void placeMines(char map[ROWS][COLS]);
void printBothMaps(char map[ROWS][COLS], char userMap[ROWS][COLS]);
void printMap(char map[ROWS][COLS]);
void printUserMap(char userMap[ROWS][COLS]);
bool isInsideMap(int row, int col);
void revealTile(char map[ROWS][COLS], int row, int col, char userMap[ROWS][COLS]);

int main() {
    srand(static_cast<unsigned>(time(0)));

    char map[ROWS][COLS];
    char userMap[ROWS][COLS];
    initializeMap(map);
    placeTreasure(map);
    placeMines(map);

    // Initialize user map
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            userMap[i][j] = UNDISCOVERED;
        }
    }

    printBothMaps(map, userMap);

    int row, col;

    do {
        cout << "Enter row and column to dig (e.g.: 2 3): ";
        cin >> row >> col;

        if (isInsideMap(row, col)) {
            revealTile(map, row, col, userMap);

            if (map[row][col] == TREASURE) {
                cout << "Congratulations! You found the treasure!\n";
                break;
            }
            else if (map[row][col] == MINE) {
                cout << "Oops! You hit a mine. Game over!\n";
                break;
            }
        }
        else {
            cout << "Please enter valid row and column numbers.\n";
        }

        printBothMaps(map, userMap);

    } while (true);

    return 0;
}

void initializeMap(char map[ROWS][COLS]) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            map[i][j] = UNDISCOVERED;
        }
    }
}

void placeTreasure(char map[ROWS][COLS]) {
    int treasureRow = rand() % ROWS;
    int treasureCol = rand() % COLS;
    map[treasureRow][treasureCol] = TREASURE;
}

void placeMines(char map[ROWS][COLS]) {
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (map[i][j] == TREASURE) {
                // Place mines only in the up, down, left, and right directions
                if (isInsideMap(i - 1, j) && map[i - 1][j] != TREASURE) map[i - 1][j] = MINE;
                if (isInsideMap(i + 1, j) && map[i + 1][j] != TREASURE) map[i + 1][j] = MINE;
                if (isInsideMap(i, j - 1) && map[i][j - 1] != TREASURE) map[i][j - 1] = MINE;
                if (isInsideMap(i, j + 1) && map[i][j + 1] != TREASURE) map[i][j + 1] = MINE;
            }
        }
    }

    // Place an additional random mine away from the treasure
    int randomRow, randomCol;
    do {
        randomRow = rand() % ROWS;
        randomCol = rand() % COLS;
    } while (map[randomRow][randomCol] != UNDISCOVERED || map[randomRow][randomCol] == TREASURE);
    map[randomRow][randomCol] = MINE;

    // Place flags around all mines, including the additional mine
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            if (map[i][j] == MINE) {
                if (isInsideMap(i - 1, j) && map[i - 1][j] != TREASURE) map[i - 1][j] = FLAG;
                if (isInsideMap(i + 1, j) && map[i + 1][j] != TREASURE) map[i + 1][j] = FLAG;
                if (isInsideMap(i, j - 1) && map[i][j - 1] != TREASURE) map[i][j - 1] = FLAG;
                if (isInsideMap(i, j + 1) && map[i][j + 1] != TREASURE) map[i][j + 1] = FLAG;
            }
        }
    }
}

void printBothMaps(char map[ROWS][COLS], char userMap[ROWS][COLS]) {
    system("cls");

    //cout << "Actual Map:\n";
    //printMap(map);

    cout << "The map has 1 treasure and 5 mines; enter the coordinates for digging. You win when you dig up the treasure and lose if you dig up the mines.And there are two rules:\n";
    cout << "1.There must be mines above, below and to the left of the treasure. \n";
    cout << "2.There are flags on the left and right below and above the mines, indicating the presence of mines in the vicinity.\n";
    cout << "Now start digging for the treasure!\n";
    cout << "-----------------\n";
    printUserMap(userMap);

    cout << "-----------------\n";
}

void printMap(char map[ROWS][COLS]) {
    cout << "  ";
    for (int j = 0; j < COLS; ++j) {
        cout << j << " ";
    }
    cout << "\n";

    for (int i = 0; i < ROWS; ++i) {
        cout << i << " ";
        for (int j = 0; j < COLS; ++j) {
            cout << map[i][j] << " ";
        }
        cout << "\n";
    }
}

void printUserMap(char userMap[ROWS][COLS]) {
    
    cout << "  ";
    for (int j = 0; j < COLS; ++j) {
        cout << j << " ";
    }
    cout << "\n";

    for (int i = 0; i < ROWS; ++i) {
        cout << i << " ";
        for (int j = 0; j < COLS; ++j) {
            cout << userMap[i][j] << " ";
        }
        cout << "\n";
    }
}

bool isInsideMap(int row, int col) {
    return row >= 0 && row < ROWS&& col >= 0 && col < COLS;
}

void revealTile(char map[ROWS][COLS], int row, int col, char userMap[ROWS][COLS]) {
    if (userMap[row][col] == UNDISCOVERED) {
        if (map[row][col] == FLAG) {
            userMap[row][col] = FLAG;
        }
        else if (map[row][col] == MINE || map[row][col] == TREASURE) {
            printBothMaps(map, userMap);
            for (int i = 0; i < ROWS; ++i) {
                for (int j = 0; j < COLS; ++j) {
                    if (map[i][j] == FLAG) {
                        userMap[i][j] = FLAG;
                    }
                    else {
                        userMap[i][j] = map[i][j];
                    }
                }
            }
        }
        else {
            userMap[row][col] = (map[row][col] == UNDISCOVERED) ? 'O' : UNDISCOVERED;
        }
    }
}
