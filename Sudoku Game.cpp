#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <random>
#include <chrono>
#include <bits/stdc++.h>

using namespace std;

const int N = 9;
const int emptyValue = 0;

bool isSafe(vector<vector<int>>& grid, int row, int col, int num) {

    for (int x = 0; x < N; x++) {
        if (grid[row][x] == num || grid[x][col] == num) {
            return false;
        }
    }

    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }

    return true;
}

bool solveSudoku(vector<vector<int>>& grid) {
        for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (grid[row][col] == emptyValue) {
                vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
                random_shuffle(numbers.begin(), numbers.end());

                for (int i = 0; i < N; i++) {
                    int num = numbers[i];
                    if (isSafe(grid, row, col, num)) {
                        grid[row][col] = num;

                        if (solveSudoku(grid)) {
                            return true;
                        }

                        grid[row][col] = emptyValue;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

void generateSudoku(vector<vector<int>>& grid) {
    srand(time(0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            grid[i][j] = emptyValue;
        }
    }
    if (solveSudoku(grid)) {

    }
}

void removeCells(vector<vector<int>>& grid, int removeCount ) {
        while (removeCount > 0) {
            int row = rand() % N;
            int col = rand() % N;
            if (grid[row][col] != emptyValue) {
                grid[row][col] = emptyValue;
                removeCount--;
            }
        }
}

void printSudoku(vector<vector<int>>& sudoku) {
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0 && i != 0) {
            cout << "------+-------+------" << endl;
        }
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0 && j != 0) {
                cout << "| ";
            }
            cout << sudoku[i][j] << " ";
        }
        cout << endl;
    }
}

bool checkAccuracy(const vector<vector<int>>& solution, const vector<vector<int>>& grid) {
    int count = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] != emptyValue && grid[i][j] != solution[i][j]) {
                count++;
            }
        }
    }
    return count <= 1;
}

bool isValidSudoku(const vector<vector<int>>& grid) {

    for (int i = 0; i < N; i++) {
        vector<bool> rowCheck(N + 1, false);
        vector<bool> colCheck(N + 1, false);
        for (int j = 0; j < N; j++) {
            if (grid[i][j] != emptyValue) {
                if (rowCheck[grid[i][j]]) {
                    return false;
                }
                rowCheck[grid[i][j]] = true;
            }
            if (grid[j][i] != emptyValue) {
                if (colCheck[grid[j][i]]) {
                    return false;
                }
                colCheck[grid[j][i]] = true;
            }
        }
    }

    for (int i = 0; i < N; i += 3) {
        for (int j = 0; j < N; j += 3) {
            vector<bool> subgridCheck(N + 1, false);
            for (int x = i; x < i + 3; x++) {
                for (int y = j; y < j + 3; y++) {
                    if (grid[x][y] != emptyValue) {
                        if (subgridCheck[grid[x][y]]) {
                            return false;
                        }
                        subgridCheck[grid[x][y]] = true;
                    }
                }
            }
        }
    }

    return true;
}

bool isSudokuComplete(const vector<vector<int>>& sudoku) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (sudoku[i][j] == emptyValue) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    int difficultyLevel = 0;

    new1:
    cout << "Welcome to Sudoku Game!" << endl;
    cout << "1. New Game" << endl;
    cout << "2. Options" << endl;
    cout << "3. Exit" << endl;

    int choice;
    cin >> choice;

    if (cin.fail()) {
        cout << "You entered a character. Please enter a numeric option.\n" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        goto new1;
    }

    if (choice == 1) {
        if (difficultyLevel == 0) {
            cout << "Please select a difficulty level from Options first." << endl;
            goto new1;
        }

        vector<vector<int>> sudoku(N, vector<int>(N, 0));
        vector<vector<int>> sudoku_restore(N, vector<int>(N, 0));
        generateSudoku(sudoku);

        if (difficultyLevel == 1) {
            int removeCount =  N * N - 50;
            removeCells(sudoku, removeCount);
            for (int i = 0; i < N; i ++) {
                for (int j = 0; j < N; j ++){
                sudoku_restore[i][j]=sudoku[i][j];
                }
            }
            cout << "Easy Sudoku Game:" << endl;
        } else if (difficultyLevel == 2) {
            int removeCount =  N * N - 45;
            removeCells(sudoku, removeCount);
            for (int i = 0; i < N; i ++) {
                for (int j = 0; j < N; j ++){
                sudoku_restore[i][j]=sudoku[i][j];
                }
            }
            cout << "Medium Sudoku Game:" << endl;
        } else if (difficultyLevel == 3) {
            int removeCount =  N * N - 30;
            removeCells(sudoku, removeCount);
            for (int i = 0; i < N; i ++) {
                for (int j = 0; j < N; j ++){
                sudoku_restore[i][j]=sudoku[i][j];
                }
            }
            cout << "Hard Sudoku Game:" << endl;
        }

        vector<vector<int>> solution = sudoku;
        solveSudoku(solution);
        printSudoku(sudoku);


        while (!isSudokuComplete(sudoku)) {
                up2:
                new2:
            cout << "Enter row, column, and number (or -1 to exit): ";
            int row, col, num, i;
            cin >> row;
            if (row == -1) {
                break;
            }
            cin >> col >> num;
        if (cin.fail()) {
        cout << "\nYou entered a character. Please enter a numeric option.\n" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        goto new2;
    }

                row=row-1;
                col=col-1;
             if(row>=0 && row<=8 && col>=0 && col<=8){
            for(i = 1; i <= 9; i ++){
                if(sudoku_restore[row][col]==i){
                        cout << "Invalid Sudoku configuration. you cannot change the sudoku board." << endl;
                        printSudoku(sudoku);
                        goto up2;
                }
            }
        }
            if (row >= 0 && row < N && col >= 0 && col < N) {
                if (num >= 1 && num <= 9) {

                    sudoku[row][col] = num;
                    cout << "Updated Sudoku Game:" << endl;
                    printSudoku(sudoku);

                if (isValidSudoku(sudoku)) {
                if (checkAccuracy(solution, sudoku)) {
                    cout << "Congratulations!" << endl;
                } else {
                    cout << "Keep trying! Your solution is not correct yet." << endl;
                }
            } else {
                cout << "Invalid Sudoku configuration. Please check your entries." << endl;
            }
                }else if (num == 0) {
                    sudoku[row][col] = emptyValue;
                    cout << "Updated Sudoku Game:" << endl;
                    printSudoku(sudoku);
                } else {
                    cout << "Invalid number. Please enter a number between 1 and 9 or 0 to delete." << endl;
                }
            }
             else{
                cout << "Invalid coordinates. Please enter row and column between 1 and 9." << endl;
            }
        }
    }

     else if (choice == 2) {
        new3:
        cout << "Options:" << endl;
        cout << "1. Easy" << endl;
        cout << "2. Medium" << endl;
        cout << "3. Hard" << endl;

        int option;
        cin >> option;

        if (cin.fail()) {
        cout << "\nYou entered a character. Please enter a numeric option.\n" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        goto new3;
    }
        if (option == 1) {
            difficultyLevel = 1;
        } else if (option == 2) {
            difficultyLevel = 2;
        } else if (option == 3) {
            difficultyLevel = 3;
        } else {
            cout << "Invalid option. Please select a valid difficulty option (1, 2, or 3)." << endl;
        }
        goto new1;
    }

     else if (choice == 3) {
        return 0;
    }
    goto new1;
    return 0;
}
