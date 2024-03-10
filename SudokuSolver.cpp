#include <iostream>
#include <vector>
using namespace std; 

void printSudoku(int arr[9][9]) {
    cout << "-----------------" << endl;
    for (int row = 0; row < 9; row++) {
        for (int cell = 0; cell < 9; cell++) {
            cout << arr[row][cell] << " ";
        }
        cout << endl;
    }
    cout << "-----------------" << endl;
}

bool canPlace(int arr[9][9], int row, int col, int n){

    if (arr[row][col] != 0){
        return false; 
    }
    
    bool status = true; 
    int gridx = (col / 3) * 3;
    int gridy = (row / 3) * 3;  

    for (int i = 0; i < 9; i++){
        if (arr[row][i] == n){
            status = false; 
            break; 
        }

        if (arr[i][col] == n){
            status = false; 
            break; 
        }

        if (arr[gridy + i / 3][gridx + i % 3] == n){
            status = false; 
            break; 
        }

    }  

    return status; 

    }

vector<int> findPlacebles(int arr[9][9], int row, int col){

    vector<int> cps = {};
    for (int i = 1; i <= 9; i++){
        if (canPlace(arr, row, col, i)){
            cps.push_back(i);
        }
    }

return cps;
}

void copyArray(int arr[9][9], int arrCpy[9][9]){

    for (int y = 0; y < 9; y ++){
        for (int x = 0; x < 9; x++){
            arrCpy[y][x] = arr[y][x];
        }
    }
}

void nextEmpty(int arr[9][9], int row, int col, int &nextRow, int &nextCol){

    int index = 9 * 9;
    
    for(int i = row * 9 + col + 1; i < 9 * 9; i++){
        if (arr[i / 9][i % 9] == 0){
            index = i; 
            break;
        }
    }

    nextRow = index / 9; 
    nextCol = index % 9; 
}

bool solveSudoku(int arr[9][9], int row, int col) {
    if (row > 8) {
        return true;
    }

    if (arr[row][col] != 0) {
        int nextRow = row;
        int nextCol = col;
        nextEmpty(arr, row, col, nextRow, nextCol);
        return solveSudoku(arr, nextRow, nextCol);
    }

    vector<int> placeables = findPlacebles(arr, row, col);

    if (placeables.size() == 0) {
        return false;
    }

    for (int i = 0; i < placeables.size(); i++) {
        int n = placeables[i];
        int arrCpy[9][9];
        copyArray(arr, arrCpy);
        arrCpy[row][col] = n;
        int nextRow, nextCol;
        nextEmpty(arrCpy, row, col, nextRow, nextCol);
        if (solveSudoku(arrCpy, nextRow, nextCol)) {
            copyArray(arrCpy, arr);
            return true;
        }
    }

    return false;
}


int main() {
    // Example Board
    int board[9][9] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    printSudoku(board); // Prints the original board

    if (solveSudoku(board, 0, 0)) {
        cout << "Sudoku Solved!" << endl;
        printSudoku(board); // Prints the final board
    } else {
        cout << "No solution found." << endl;
    }

    return 0;
}