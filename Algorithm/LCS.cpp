#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void LCSTableMaker(int** table, char* str1, char* str2, int len1, int len2);
void LCSPrint(int** table, char* str1, char* str2, int len1, int len2);
int GetBigger(int n1, int n2);

int main(int args, char* argv[])
{
    int len1 = strlen(argv[1]), len2 = strlen(argv[2]);
    int** lcsTable;

    lcsTable = (int**)calloc(len1 + 1, sizeof(int*));
    lcsTable[0] = (int*)calloc((len1 + 1) * (len2 + 1), sizeof(int));
    for (int i = 1; i <= len1; i++)
    {
        lcsTable[i] = lcsTable[i - 1] + (len2 + 1);
    }

    LCSTableMaker(lcsTable, argv[1], argv[2], len1, len2);
    LCSPrint(lcsTable, argv[1], argv[2], len1, len2);

    free(lcsTable[0]);
    free(lcsTable);
    return 0;
}

void LCSTableMaker(int** table, char* str1, char* str2, int len1, int len2)
{
    for (int i = 1; i <= len1; i++)
    {
        for (int j = 1; j <= len2; j++)
        {
            if (str1[i - 1] == str2[j - 1])
            {
                table[i][j] = table[i - 1][j - 1] + 1;
            }
            else
            {
                table[i][j] = GetBigger(table[i - 1][j], table[i][j - 1]);
            }
        }
    }
}

void LCSPrint(int** table, char* str1, char* str2, int len1, int len2)
{
    printf("Number of matched char : %d\n", table[len1][len2]);

    char* matched = (char*)calloc(len1, sizeof(char));
    int i = len1, j = len2;

    while (i != 0 && j != 0)
    {
        if (table[i][j] > table[i - 1][j] && table[i][j] > table[i][j - 1] && table[i][j] > table[i - 1][j - 1])
        {
            matched[i - 1] = str1[i - 1];
            i--;
            j--;
        }
        else if (table[i][j] > table[i][j - 1] && table[i][j] == table[i - 1][j])
        {
            i--;
        }
        else
        {
            j--;
        }
    }

    int spacedCount1 = 0, spacedCount2 = 0, point = -1;
    int* space1 = (int*)calloc(len1, sizeof(int));
    int* space2 = (int*)calloc(len2, sizeof(int));
    int secondSpace = 0;

    for (int i = 0; i < len1; i++)
    {
        if (matched[i] != 0)
        {
            if (matched[i] != str2[i - spacedCount2 + spacedCount1])
            {
                int k = 1;
                int check = 0;
                int scnt = 0;

                if (i > 0)
                {
                    for (int j = i - 1; j > point; j--)
                    {
                        if (i - k - spacedCount2 + spacedCount1 >= 0)
                        {
                            if (matched[i] == str2[i - k - spacedCount2 + spacedCount1])
                            {
                                if (i - k - spacedCount2 + spacedCount1 == 0)
                                {
                                    secondSpace = k;
                                    scnt = k;
                                }
                                else
                                {
                                    space2[(point - spacedCount2 + spacedCount1 == -1 ? 0 : point - spacedCount2 + spacedCount1)] = k;
                                    scnt = k;
                                }
                                check = 1;
                            }
                        }
                        k++;
                    }
                }

                if (check == 0)
                {
                    k = 1;
                    for (int j = i + 1; j < len2 + (spacedCount2 - spacedCount1); j++)
                    {
                        if (i + k - spacedCount2 < len2)
                        {
                            if (matched[i] == str2[i + k - spacedCount2 + spacedCount1])
                            {
                                space1[(point == -1 ? 0 : point)] += k;
                                spacedCount1 += k;
                                break;
                            }
                        }
                        k++;
                    }
                }
                else
                {
                    spacedCount2 += scnt;
                }
            }
            else
            {
                int cnt = 1;
                for (int j = point - spacedCount2 + spacedCount1 + 1; j < i - spacedCount2 + spacedCount1; j++)
                {
                    if (matched[i] == str2[j])
                    {
                        space2[point - spacedCount2 + spacedCount1] += (i - point) - cnt;
                        spacedCount2 += ((i - point) - cnt);
                        break;
                    }
                    cnt++;
                }
            }
            point = i;
        }
    }

    int firstSpace = 0;
    if (space1[0] > 0 && matched[0] != 0 && matched[0] != str2[0])
    {
        for (int j = 0; matched[0] != str2[j]; j++)
        {
            printf("-");
            space1[0]--;
            firstSpace++;
        }
    }

    for (int i = 0; i < len1; i++)
    {
        printf("%c", str1[i]);
        if (space1[i] != 0)
        {
            for (int j = 0; j < space1[i]; j++)
            {
                printf("-");
            }
        }
    }
    printf("\n");

    if (firstSpace > 0)
    {
        for (int j = 0; j < firstSpace; j++)
        {
            printf(" ");
        }
    }

    for (int i = 0; i < len1; i++)
    {
        printf("%c", (matched[i] != 0 ? '|' : ' '));
        if (space1[i] != 0)
        {
            for (int j = 0; j < space1[i]; j++)
            {
                printf(" ");
            }
        }
    }
    printf("\n");

    if (secondSpace > 0)
    {
        for (int j = 0; j < secondSpace; j++)
        {
            printf("-");
        }
    }

    for (int i = 0; i < len2; i++)
    {
        printf("%c", str2[i]);
        if (space2[i] != 0)
        {
            for (int j = 0; j < space2[i]; j++)
            {
                printf("-");
            }
        }
    }
    printf("\n");
}

int GetBigger(int n1, int n2)
{
    return (n1 > n2 ? n1 : n2);
}