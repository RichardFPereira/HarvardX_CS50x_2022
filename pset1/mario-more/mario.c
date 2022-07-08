#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Variables
    int height = 0;
    int i = 0;

    //Print the roles for the pyramid height
    printf("How tall the pyramids should be?(Type a number between 1 and 8)\n");

    //verify if the number is between 1 and 8 or ask again
    while (height < 1 || height > 8)
    {
        height = get_int("Height: ");
    }

    //A counter to track prints
    int cnt = height - 1;

    //print the pyramid with the selected height
    while (cnt >= 0)
    {
        //looping to print the amount of space before the hash symbols
        for (i = 0; i < cnt; i++)
        {
            printf(" ");
        }

        //looping to print the amout of hash symbols after spaces in the beginning
        for (i = 0; i < (height - cnt); i++)
        {
            printf("#");
        }

        //Print the 'hole' between pyramid sides
        printf("  ");

        //Looping to print the second part of the pyramid
        for (i = 0; i < (height - cnt); i++)
        {
            printf("#");
        }

        printf("\n");
        cnt--;
    }
}