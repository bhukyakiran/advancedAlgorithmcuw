#include <iostream>
using namespace std;


void readMatrix(int matrix[][5], int rows, int cols) {
    cout << "Enter the elements of the matrix (" << rows << "x" << cols << "):\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cin >> matrix[i][j];
        }
    }
}


void printMatrix(int matrix[][5], int rows, int cols) {
    cout << "\nOriginal Matrix:\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}


void convertToSparse(int matrix[][5], int rows, int cols) {
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

    
    cout << "\n the given Sparse Matrix Representation:\n";
    cout << "Row:    ";
    for (int i = 0; i < nonZero; i++) cout << rowArray[i] << " ";
    cout << "\nColumn: ";
    for (int i = 0; i < nonZero; i++) cout << colArray[i] << " ";
    cout << "\nValue:  ";
    for (int i = 0; i < nonZero; i++) cout << valArray[i] << " ";
    cout << endl;
}

int main() {
    int rows = 4, cols = 5;
    int matrix[4][5];

    
    readMatrix(matrix, rows, cols);

   
    printMatrix(matrix, rows, cols);

    
    convertToSparse(matrix, rows, cols);

    return 0;
}
