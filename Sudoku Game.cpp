#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

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
            if (grid[startRow + i][startCol + j] == num) {
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
                for (int num = 1; num <= 9; num++) {
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
            grid[i][j] = (i * 3 + i / 3 + j) % 9 + 1;
        }
    }
    random_shuffle(grid.begin(), grid.end());
    for (int i = 0; i < N; i++) {
        random_shuffle(grid[i].begin(), grid[i].end());
    }
}

void removeCells(vector<vector<int>>& grid, int toRemove) {
    while (toRemove > 0) {
        int i = rand() % N;
        int j = rand() % N;
        if (grid[i][j] != emptyValue) {
            grid[i][j] = emptyValue;
            toRemove--;
        }
    }
}

void printSudoku(vector<vector<int>>& sudoku) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << sudoku[i][j] << " ";
        }
        cout << endl;
    }
}

bool checkAccuracy(const vector<vector<int>>& solution, const vector<vector<int>>& grid) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] != emptyValue && grid[i][j] != solution[i][j]) {
                return false;
            }
        }
    }
    return true;
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


int main() {
    cout << "Welcome to Sudoku Game!" << endl;
    cout << "1. New Game" << endl;
    cout << "2. Options" << endl;
    cout << "3. Exit" << endl;

    int choice;
    cin >> choice;

    if (choice == 1) {
        vector<vector<int>> sudoku(N, vector<int>(N, 0));
        vector<vector<int>> sudoku_restore(N, vector<int>(N, 0));
        generateSudoku(sudoku);

        vector<vector<int>> solution = sudoku;
        solveSudoku(solution);


        int toRemove = N * N - 40;
        removeCells(sudoku, toRemove);

            for (int i = 0; i < N; i ++) {
                for (int j = 0; j < N; j ++){
                sudoku_restore[i][j]=sudoku[i][j];
                }
            }

        cout << "Random Sudoku Game: " <<endl;
        printSudoku(sudoku);

        while (true) {
                po:
            cout << "Enter row, column, and number (or -1 to exit): ";
            int row, col, num, i;
            cin >> row;
            if (row == -1) {
                break;
            }
            cin >> col >> num;

            for(i = 1; i <= 9; i ++){
                if(sudoku_restore[row][col]==i){
                        cout << "Invalid Sudoku configuration. you cannot change the sudoku board." << endl;
                        printSudoku(sudoku);
                        goto po;
                }
            }

            if (row >= 0 && row < N && col >= 0 && col < N) {
                if (num >= 1 && num <= 9) {

                    sudoku[row][col] = num;
                    cout << "Updated Sudoku Game:" << endl;
                    printSudoku(sudoku);

                if (isValidSudoku(sudoku)) {
                if (checkAccuracy(solution, sudoku)) {
                    cout << "Congratulations! Your solution is correct." << endl;
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
             else {
                cout << "Invalid coordinates. Please enter row and column between 0 and 8." << endl;
            }
        }
    }
    else if (choice == 2) {

        cout << "Options:" << endl;
        cout << "1. Easy" << endl;
        cout << "2. Medium" << endl;
        cout << "3. Hard" << endl;

        int option;
        cin >> option;

        vector<vector<int>> sudoku(N, vector<int>(N, 0));
        vector<vector<int>> sudoku_restore(N, vector<int>(N, 0));
        generateSudoku(sudoku);


        if (option == 1) {
            int toRemove = N * N - 50;
            removeCells(sudoku, toRemove);

            for (int i = 0; i < N; i ++) {
                for (int j = 0; j < N; j ++){
                sudoku_restore[i][j]=sudoku[i][j];

                }
            }

        } else if (option == 2) {
            int toRemove = N * N - 45;
            removeCells(sudoku, toRemove);
            for (int i = 0; i < N; i ++) {
                for (int j = 0; j < N; j ++){
                sudoku_restore[i][j]=sudoku[i][j];

                }
            }

        } else if (option == 3) {
            int toRemove = N * N - 30;
            removeCells(sudoku, toRemove);
                        for (int i = 0; i < N; i ++) {
                for (int j = 0; j < N; j ++){
                sudoku_restore[i][j]=sudoku[i][j];

                }
            }
        }

        vector<vector<int>> solution = sudoku;
        solveSudoku(solution);

        cout << "Random Sudoku Game:" << endl;
        printSudoku(sudoku);

                while (true) {


                        po2:
            cout << "Enter row, column, and number (or -1 to exit): ";
            int row, col, num, i;
            cin >> row;
            if (row == -1) {
                break;
            }
            cin >> col >> num;


            for(i = 1; i <= 9; i ++){
                if(sudoku_restore[row][col]==i){
                        cout << "Invalid Sudoku configuration. you cannot change the sudoku board." << endl;
                        printSudoku(sudoku);
                        goto po2;
                }
            }

            if (row >= 0 && row < N && col >= 0 && col < N) {
                if (num >= 1 && num <= 9) {
                    sudoku[row][col] = num;
                    cout << "Updated Sudoku Game:" << endl;
                    printSudoku(sudoku);


                if (isValidSudoku(sudoku)) {
                if (checkAccuracy(solution, sudoku)) {
                    cout << "Congratulations!! Your solution is correct." << endl;
                } else {
                    cout << "Keep trying!! Your solution is not correct yet." << endl;
                }
            } else {
                cout << "Invalid Sudoku configuration. Please check your entries." << endl;
            }

                }else if (num == 0) {
                    sudoku[row][col] = emptyValue;
                    cout << "Updated Sudoku Game:" << endl;
                    printSudoku(sudoku);
                } else {
                    cout << "Invalid number. Please enter a number between 1 and 9 to delete." << endl;
                }
            } else {
                cout << "Invalid coordinates. Please enter row and column between 0 and 8." << endl;
            }
        }

    }

     else if (choice == 3) {
        return 0;
    }

    return 0;
}

