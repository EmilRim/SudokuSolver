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
            //   printf("VOUUU nulisss\n");
            return 1;
        }
        else
        {
            //   printf("ne nulisss\n");
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
           // printf("Skaicius jau yra eilutej\n");
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
           // printf("Skaicius jau yra stulpely\n");
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
       // printf("wtf kas cia per sudoku\n");
        return -1;
    }
    int temp;
    if (!fixed[*i][*j])
    {
       // printf("elementa %d esanti i=%d j=%d reikia backtrackinti\n", arr[*i][*j], *i, *j);
        temp = arr[*i][*j];
        for (int k = arr[*i][*j] + 1; k <= 9; ++k)
        {
            if (checkLine(arr, k, *i) && checkColumn(arr, k, *j) && checkSquare(arr, k, *j, *i))
            {
                arr[*i][*j] = k;
               // printf("SKAICIUS %d pakeistas i=%d, j=%d i skaiciu %d\n", temp, *i, *j, arr[*i][*j]);
                return 1;
            }
        }
        if (arr[*i][*j] == temp)
        {
           // printf("Nepavyko %d i=%d, j=%d rasti kito tinkamo skaiciaus, backtrackinam dar\n", arr[*i][*j], *i, *j);
            arr[*i][*j] = 0;
            return 0;
        }
    }
    else
    {
        //printf("elementas %d esantis i=%d j=%d yra fixed, todel griztam prie kito\n", arr[*i][*j], *i, *j);
        return 0;
    }
}
void readSudoku(int array[9][9], char line[10], int fixedNumbers[9][9])
{
  //  printf("iveskite sudoku\n");
    for (int i = 0; i < 9; i++)
    {
        char line[10];
        scanf("%[^\n]", line); fgetc(stdin);
       // scanf("%s", line);
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
    //printf("PRADEDAM\n");
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
                    // printf("teoriskai priskirtas naujas skaitmuo\n");
                   // printf("Sekmingai spirkyrem i=%d j=%d elementui %d\n", i, j, k);
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
                       // printf("IS MAIN backtracking elment %d i=%d, j=%d\n", array[i][j], i, j);
                        back = backTrack(array, fixedNumbers, &i, &j);
                    }
                    else
                    {
                        --j;
                       // printf("IS MAIN backtracking elment %d i=%d, j=%d\n", array[i][j], i, j);
                        back = backTrack(array, fixedNumbers, &i, &j);
                    }
                    // printf("uh oh i guess reikia backtrackinti dabar\n\n");
                    // printf("einam i backtracking su skaicium %d, kuris yra i=%d j=%d elementas\n", array[i][j], i, j);
                    // backTrack(array, fixedNumbers, i, j);
                } while (!back);
               // printSudoku(array);
                if (back == -1)
                {
                    printf("Nekorektiskas sudoku\n");
                   // printSudoku(array);
                    return 0;
                }
                //printf("dabar eile yra %d, stulpelis %d\n", i, j);
            }
        }
    }
    printSudoku(array);
    return 0;
}