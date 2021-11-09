#include <sudoku.h>

int matrixFirstPosX = 120;
int matrixFirstPosY = 550;
int ended;
int matrix[DIM][DIM];
int bufferMatrix[DIM][DIM] = {{0, 6, 0, 1, 0, 4, 0, 5, 0},
                              {0, 0, 8, 3, 0, 5, 6, 0, 0},
                              {2, 0, 0, 0, 0, 0, 0, 0, 1},
                              {8, 0, 0, 4, 0, 7, 0, 0, 6},
                              {0, 0, 6, 0, 0, 0, 3, 0, 0},
                              {7, 0, 0, 9, 0, 1, 0, 0, 4},
                              {5, 0, 0, 0, 0, 0, 0, 0, 2},
                              {0, 0, 7, 2, 0, 6, 9, 0, 0},
                              {0, 4, 0, 5, 0, 8, 0, 7, 0}};
// int perfectMatrix[DIM][DIM] = {
//     {9, 6, 3, 1, 7, 4, 2, 5, 8},
//     {1, 7, 8, 3, 2, 5, 6, 4, 9},
//     {2, 5, 4, 6, 8, 9, 7, 3, 1},
//     {8, 2, 1, 4, 3, 7, 5, 9, 6},
//     {4, 9, 6, 8, 5, 2, 3, 1, 7},
//     {7, 3, 5, 9, 6, 1, 8, 2, 4},
//     {5, 8, 9, 7, 1, 3, 4, 6, 2},
//     {3, 1, 7, 2, 4, 6, 9, 8, 5},
//     {6, 4, 2, 5, 9, 8, 1, 7, 3}};

void baseSudoku()
{
    ended = 0;
    for (int i = 0; i < DIM; i++)
    {
        for (int j = 0; j < DIM; j++)
        {
            matrix[i][j] = bufferMatrix[i][j];
        }
    }

    setCursor(5, 435);
    printf("Complete correctamente el sudoku para ganar!\n\n");
    // changeCursorState(0);

    for (int i = 0; i < DIM; i++)
    {
        for (int j = 0; j < DIM; j++)
        {
            // if (matrix[i][j] != 0)
            // {
            // printMatrix(j, i, matrix[i][j]);
            printMatrix(j, i, matrix[i][j]);
            // }
        }
    }
    return;
}

void getMatrixPosition(int row, int col, int *x, int *y)
{
    *x = (row * CHAR_WIDTH * 3) + matrixFirstPosX;
    *y = (col * CHAR_HEIGHT) + matrixFirstPosY;
}

void printMatrix(int row, int col, int value)
{
    int x, y;
    getMatrixPosition(row, col, &x, &y);
    setCursor(x, y);
    printf(" %d ", value);
}

void sudoku(char c)
{
    if (ended)
        return;

    char buff[1];
    buff[0] = c;
    int size = 1;
    int value = strToInt(buff, &size);

    for (int i = 0; i < DIM; i++)
    {
        for (int j = 0; j < DIM; j++)
        {
            if (matrix[i][j] == 0)
            {
                matrix[i][j] = value;
                printMatrix(j, i, value);
                return;
            }
        }
    }
    message();
    return;
}

static int completeRow(int row[])
{
    int i;
    int flag[DIM] = {0};
    for (i = 0; i < DIM; i++)
    {
        if (row[i] > 0 && row[i] < 10)
        {
            if (flag[row[i] - 1] == 1)
            {
                return 0;
            }
            flag[row[i] - 1] = 1;
        }
        else
            return 0;
    }
    return 1;
}

static int subMatrix(int m[DIM][DIM], int row, int col)
{
    int i, j;
    int flag[DIM] = {0};

    for (i = row; i < (SUB_DIM + row); i++)
    {
        for (j = col; j < (SUB_DIM + col); j++)
        {
            if (m[i][j] > 0 && m[i][j] < 10)
            {
                if (flag[m[i][j] - 1] == 1)
                    return 0;
                else
                    flag[m[i][j] - 1] = 1;
            }
            else
                return 0;
        }
    }
    return 1;
}

static int sudokuChecking(int m[DIM][DIM])
{
    int i, j;
    int cols[DIM] = {0};
    int subMatrices;
    int rows;

    for (i = 0; i < DIM; i++)
    {
        rows = completeRow(m[i]);
        for (j = 0; j < DIM; j++)
        {
            if (i == 0 || i == 3 || i == 6)
            {
                if (j == 0 || j == 3 || j == 6)
                {
                    subMatrices = subMatrix(m, i, j);
                }
            }
            if (!subMatrices)
                return 0;
            cols[j] = m[j][i];
        }
        if (!completeRow(cols) || !rows)
        {
            return 0;
        }
    }
    return 1;
}

// static int cmpMatrix()
// {
//     for (int i = 0; i < DIM; i++)
//     {
//         for (int j = 0; j < DIM; j++)
//         {
//             if (matrix[i][j] != perfectMatrix[i][j])
//                 return 0;
//         }
//     }
//     return 1;
// }

void message()
{
    ended = 1;
    setCursor(5, 720);
    if (sudokuChecking(matrix) == 1)
    {
        printf("Felicitaciones usted ha completado correctamente el sudoku!!");
    }
    else
        printf("No ha completado bien el sudoku, intentelo nuevamente");

    return;
}