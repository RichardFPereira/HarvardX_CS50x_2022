#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Aks the user's name
    string name = get_string("What's your name?\n");

    //Print Hello + name
    printf("Hello, %s!\n", name);
}