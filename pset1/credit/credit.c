#include <stdio.h>
#include <cs50.h>

int main(void)
{

    //Variables
    long card_number = 0;
    long card = 0;
    int digits = 1;
    int i, dig;
    int product;
    int sum = 0;
    int valid = 0;

    //Verify if the number isn't negative
    while (card_number <= 0)
    {
        card_number = get_long("Number: ");
    }
    card = card_number;

    //Count the number of digits
    while (card >= 10)
    {
        card = card / 10;
        digits ++;
    }

    //Ensures that the number of digits is between 13 and 16 and isn't 14
    if (digits < 13 || digits > 16 || digits == 14)
    {
        printf("INVALID\n");
    }

    //Declare an array with 'digits' length
    int array[digits];
    card = card_number;
    i = digits - 1;

    //Fulfill the array with card number
    while (card > 0)
    {
        dig = card % 10;
        array[i] = dig;
        i --;
        card = card / 10;
    }

    //Luhn’s Algorithm check for 13 digits
    //Variable valid receives 1 if the algorithm is valid or remain 0 if it isn't
    if (digits == 13)
    {
        i = digits - 2;
        while (i > 0)
        {
            product = array[i] * 2;
            if (product > 9)
            {
                product = product % 10;
                product++;
            }
            sum = sum + product;
            i = i - 2;
        }
        i = digits - 1;
        while (i >= 0)
        {
            product = array[i];
            sum = sum + product;
            i = i - 2;
        }
        if (sum % 10 == 0)
        {
            valid = 1;
        }
    }

    //Luhn’s Algorithm check for 16 digits
    //Variable valid receives 1 if the algorithm is valid or remain 0 if it isn't
    if (digits == 16)
    {
        i = digits - 2;
        while (i >= 0)
        {
            product = array[i] * 2;
            if (product > 9)
            {
                product = product % 10;
                product++;
            }
            sum = sum + product;
            i = i - 2;
        }
        i = digits - 1;
        while (i > 0)
        {
            product = array[i];
            sum = sum + product;
            i = i - 2;
        }

        if (sum % 10 == 0)
        {
            valid = 1;
        }
    }

    //Print invalid if the algorithm isn't valid for 13 digits
    if (valid == 0 && digits == 13)
    {
        printf("INVALID\n");
    }

    //Verify if it's an AMEX card
    if (digits == 15)
    {
        card = card_number / 10000000000000;
        if (card == 34 || card == 37)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }

    //Verify if it's a VISA card with 13 digits
    if (digits == 13 && valid == 1)
    {
        card = card_number / 1000000000000;
        if (card == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }


    //Verify if it's a VISA card with 16 digits or a MASTERCARD
    if (digits == 16)
    {
        card = card_number / 1000000000000000;
        if (card == 4 && valid == 1)
        {
            printf("VISA\n");
        }
        else
        {
            card = card_number / 100000000000000;
            if (card == 51 || card == 52 || card == 53 || card == 54 || card == 55)
            {
                printf("MASTERCARD\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
    }
}