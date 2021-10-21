#include <stdio.h>
#include "dna.h"

void load_string(FILE *file, int *p, char *s, int t)
{
    if (fscanf(file, "%d", p) != 1)
    {
        fprintf(stderr, "erro ao ler string do teste %d\n", t);
    }

    char c;
    do
    {
        c = getc(file);
    } while (c != '\n');

    fgets(s, *p + 1, file);
}

int mlcs_w(char a[], int n, char b[], int m, int length[MAX_SIZE + 1][MAX_SIZE + 1])
{
    // checks if n or m is zero, if it the value equals to zero
    if (n == 0 || m == 0)
    {
        length[n][m] = 0;
    }
    // checks if the value is -1, if it is, the value is already calculated and just return
    else if (length[n][m] != -1)
    {
        return length[n][m];
    }
    // checks the values in the vectors, if is the same, add one to the final value
    else if (a[n - 1] == b[m - 1])
    {
        length[n][m] = mlcs_w(a, n - 1, b, m - 1, length) + 1;
    }
    else
    {
        // compares the bigger value
        int small_n = mlcs_w(a, n - 1, b, m, length);
        int small_m = mlcs_w(a, n, b, m - 1, length);

        if (small_n > small_m)
        {
            length[n][m] = small_n;
        }
        else
        {
            length[n][m] = small_m;
        }
    }

    return length[n][m];
}

int mlcs(char a[], int n, char b[], int m)
{

    int line, column, length[MAX_SIZE + 1][MAX_SIZE + 1];

    for (line = 0; line <= n; line++)
    {
        for (column = 0; column <= m; column++)
        {
            length[line][column] = -1;
        }
    }

    return mlcs_w(a, n, b, m, length);
}

int dlcs(char a[], int n, char b[], int m)
{

    int line, column, length[n + 1][m + 1];

    for (line = 0; line <= n; line++)
    {
        for (column = 0; column <= m; column++)
        {
            // checks ir n or m is zero, if it the value equals to zero
            if (line == 0 || column == 0)
            {
                length[line][column] = 0;
            }
            // checks if the value is -1, if it is, the value is already calculated and just return
            else if (a[line - 1] == b[column - 1])
            {
                length[line][column] = length[line - 1][column - 1] + 1;
            }

            else
            {   // checks the values in the vectors, if is the same, add one to the final value
                if (length[line - 1][column] > length[line][column - 1])
                {

                    length[line][column] = length[line - 1][column];
                }
                else
                {
                    length[line][column] = length[line][column - 1];
                }
            }
        }
    }

    return length[n][m];
}
