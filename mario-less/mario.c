#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
//prompt user
    do
    {
        n = get_int("Height: ");
    }
    while
    (
        n < 1 || n > 8
    );
//start building pyramid
    for (int i = 0; i < n; i++)
    {
        for (int k = (n - 1); k > i; k--)
        {
            printf(" ");
        };
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        };
        printf("\n");
    }
}