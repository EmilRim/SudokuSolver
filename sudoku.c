#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int checkIfNull(int);
int checkLine(int[9][9], int, int);
int checkColumn(int[9][9], int, int);
int checkSquare(int[9][9], int, int, int);
int backTrack(int[9][9], int[9][9], int *, int *);
void readSudoku(int array[9][9], char line[10], int fixedNumbers[9][9]);
void printSudoku(int[9][9]);


int checkIfNull(int num)
{
    for (int i = 0; i < 9; ++i)
    {
        if (num == 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}
int checkLine(int arr[9][9], int x, int row)
{
    for (int i = 0; i < 9; ++i)
    {
        if (arr[row][i] == x)
        {
            return 0;
        }
    }
    return 1;
}
int checkColumn(int arr[9][9], int x, int col)
{
    for (int i = 0; i < 9; ++i)
    {
        if (arr[i][col] == x)
        {
            return 0;
        }
    }
    return 1;
}
int checkSquare(int arr[9][9], int x, int col, int row)
{

    // Find the top-left corner of the 3x3 box
    int box_start_row = (row / 3) * 3;
    int box_start_col = (col / 3) * 3;

    // Check each cell in the 3x3 box
    for (int i = box_start_row; i < box_start_row + 3; i++)
    {
        for (int j = box_start_col; j < box_start_col + 3; j++)
        {
            if (arr[i][j] == x)
            {
                return 0; // Number found in box
            }
        }
    }

    return 1; // Number not found in box
}
int backTrack(int arr[9][9], int fixed[9][9], int *i, int *j)
{
    if (*i < 0 || *j < 0)
    {
        return -1;
    }
    int temp;
    if (!fixed[*i][*j])
    {
        temp = arr[*i][*j];
        for (int k = arr[*i][*j] + 1; k <= 9; ++k)
        {
            if (checkLine(arr, k, *i) && checkColumn(arr, k, *j) && checkSquare(arr, k, *j, *i))
            {
                arr[*i][*j] = k;
                return 1;
            }
        }
        if (arr[*i][*j] == temp)
        {
            arr[*i][*j] = 0;
            return 0;
        }
    }
    else
    {
        return 0;
    }
}
void readSudoku(int array[9][9], char line[10], int fixedNumbers[9][9])
{
    for (int i = 0; i < 9; i++)
    {
        char line[10];
        scanf("%[^\n]", line); fgetc(stdin);
        for (int j = 0; line[j] != '\0'; ++j)
        {
            array[i][j] = line[j] - '0'; // Convert char to int by subtracting ASCII value of '0'
        }
    }
    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            if (!checkIfNull(array[i][j]))
            {
                fixedNumbers[i][j] = 1;
            }
            else
            {
                fixedNumbers[i][j] = 0;
            }
        }
    }
}

void printSudoku(int array[9][9])
{
    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            printf("%d", array[i][j]);
        }
        printf("\n");
    }
}
int main()
{
    char line[10];
    int array[9][9], fixedNumbers[9][9];
    int i;

    readSudoku(array, line, fixedNumbers);

    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            for (int k = 1; k <= 9; ++k)
            {
                if (checkIfNull(array[i][j]) && checkLine(array, k, i) && checkColumn(array, k, j) && checkSquare(array, k, j, i))
                {

                    array[i][j] = k;
                    break;
                }
            }
            if (array[i][j] == 0)
            {
                int back = 0;
                do
                {
                    if (j == 0)
                    {
                        --i;
                        j = 8;
                        back = backTrack(array, fixedNumbers, &i, &j);
                    }
                    else
                    {
                        --j;
                        back = backTrack(array, fixedNumbers, &i, &j);
                    }
                } while (!back);
                if (back == -1)
                {
                    printf("Nekorektiskas sudoku\n");
                    return 0;
                }
            }
        }
    }
    printSudoku(array);
    return 0;
}
