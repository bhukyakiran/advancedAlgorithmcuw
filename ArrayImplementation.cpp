#include <iostream>
using namespace std;


void printtheMatrix(int matrix[4][5], int rows, int cols) {
    cout << "Original Matrix:\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}


void convertToSparse(int matrix[4][5], int rows, int cols) {
    
    int nonZero = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] != 0)
                nonZero++;
        }
    }

    
    int rowArray[nonZero], colArray[nonZero], valArray[nonZero];

    
    int k = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] != 0) {
                rowArray[k] = i;
                colArray[k] = j;
                valArray[k] = matrix[i][j];
                k++;
            }
        }
    }

    
    cout << "\nSparse Matrix Representation:\n";
    cout << "Row:    ";
    for (int i = 0; i < nonZero; i++) cout << rowArray[i] << " ";
    cout << "\nColumn: ";
    for (int i = 0; i < nonZero; i++) cout << colArray[i] << " ";
    cout << "\nValue:  ";
    for (int i = 0; i < nonZero; i++) cout << valArray[i] << " ";
    cout << endl;
}

int main() {

    int Givenmatrix[4][5] = {
        {0, 0, 3, 0, 4},
        {0, 0, 5, 7, 0},
        {0, 0, 0, 0, 0},
        {0, 2, 6, 0, 0}
    };

    int rows = 4, cols = 5;

    
    printtheMatrix(Givenmatrix, rows, cols);

    
    convertToSparse(Givenmatrix, rows, cols);

    return 0;
}
