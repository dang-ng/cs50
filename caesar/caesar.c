#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>



int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (isdigit(argv[1][i]) == 0)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        };
    }

    int k = atoi(argv[1]);
    string prompt = get_string("plaintext:  ");

    printf("ciphertext: ");

    for (int j = 0; j < strlen(prompt); j++)
    {
        if (prompt[j] < 65 || prompt[j] > 122)
        {
            printf("%c", (char)prompt[j]);
        }
        else if (isupper(prompt[j]))
        {
            printf("%c", ((prompt[j] - 'A') + k) % 26 + 'A');
        }
        else if (islower(prompt[j]))
        {
            printf("%c", ((prompt[j] - 'a') + k) % 26 + 'a');
        }
    }
    printf("\n");

}
