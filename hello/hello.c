#include <stdio.h>
#include <cs50.h>

int main(void)
{
    printf("Hello, world\n");

//prompt user
    string name = get_string("What is your name? ");
    printf("Hello, %s\n", name);


}