#include <iostream>
#define S 9

using namespace std;
int sudoku[S][S];

bool Row(int row, int num) {
   for (int col = 0; col < S; col++)
      if (sudoku[row][col] == num)
         return true;
   return false;
}

bool Column(int col, int num) {
   for (int row = 0; row < S; row++)
      if (sudoku[row][col] == num)
         return true;
   return false;
}

bool divideby3(int Row3, int Col3, int num) {
   for (int row = 0; row < 3; row++)
      for (int col = 0; col < 3; col++)
         if (sudoku[row + Row3][col + Col3] == num)
            return true;
   return false;
}

void printGrid() {
   for (int row = 0; row < S; row++) {
      for (int col = 0; col < S; col++) {
         if (col == 3 || col == 6)
            cout << "|";
         cout << sudoku[row][col] << " ";
      }
      if (row == 2 || row == 5) {
         cout << endl;
         for (int i = 0; i < S; i++)
            cout << "---";
      }
      cout << endl;
   }
}

bool Empty(int &row, int &col) {
   for (row = 0; row < S; row++)
      for (col = 0; col < S; col++)
         if (sudoku[row][col] == 0)
            return true;
   return false;
}

bool validplc(int row, int col, int num) {
   return !Row(row, num) && !Column(col, num) && !divideby3(row - row % 3, col - col % 3, num);
}

bool solveSudoku() {
   int row, col;

   if (!Empty(row, col))
      return true;

   for (int num = 1; num <= 9; num++) {
      if (validplc(row, col, num)) {
         sudoku[row][col] = num;
         if (solveSudoku())
            return true;
         sudoku[row][col] = 0;
      }
   }
   return false;
}

void readFromConsole() {
   cout << "\nEnter the specified value when prompted.\n";
   cout << "Enter 0 if the cell is empty.\n\n";

   int row, col;

   for (row = 0; row < 9; row++) {
      for (col = 0; col < 9; col++) {
         int enteredValue;

         cout << "Enter value for cell[" << row + 1 << "][" << col + 1 << "] --> ";
         cin >> enteredValue;

         if (!(enteredValue >= 0 && enteredValue <= 9)) {
            while (true) {
               cout << "Oops! You seem to have entered a wrong value! Try again.\n";
               cout << "Enter value for cell [" << row + 1 << "][" << col + 1 << "] --> ";
               cin >> enteredValue;

               if (enteredValue >= 0 && enteredValue <= 9)
                  break;
            }
         }

         sudoku[row][col] = enteredValue;
      }
      cout << "-------\n";
   }
   cout << endl;
}

int main() {
   readFromConsole();
   cout << "Input Sudoku Puzzle:" << endl;
   printGrid();

   if (solveSudoku() == true) {
      cout << "Solution:" << endl;
      printGrid();
   } else
      cout << "Sudoku has no solution. There might be an error in the initial puzzle." << endl;
}

