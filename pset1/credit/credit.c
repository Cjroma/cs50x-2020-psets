#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>


int LuhnValidator(long l);
int length(long l);
int main(void)
{
    long cardNumber = get_long("Card Number: "); // Prompt user for card number.

    char card[1000];
    sprintf(card, "%li", cardNumber); // convert long to char
    char fNum[] = "543712"; // used to validate cards

    //check if card length is correct for mastercard , visa and validate if luhn algorithm is correct.
    if (length(cardNumber) == 16 && length(cardNumber) != 15 && LuhnValidator(cardNumber) == 0)
    {
        //check if card is mastercard
        if (fNum[0] == card[0] && (fNum[4] == card[1] || fNum[5] == card[1] ||
                                   fNum[2] == card[1] || fNum[1] == card[1] || fNum[0] == card[1]))
        {
            printf("MASTERCARD\n");
        }
        //check if card is visa
        else if (fNum[1] == card[0])
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    //check if card length is correct for mastercard , visa and validate if luhn algorithm is correct.
    else if (length(cardNumber) == 15 && LuhnValidator(cardNumber) == 0)
    {
        //check if its a valid amex card
        if ((fNum[2] == card[0] && fNum[3] == card[1]) || (fNum[2] == card[0] && fNum[1] == card[1]))
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }

}
// Check if Luhn Algorithm of card is correct.
int LuhnValidator(long l)
{
    long setTwoSum = 0;
    long setOneSum = 0;
    int temp = length(l);
    int temp1 = length(l);
    int ans = 0;
    char card[1000];
    char setOne[20];
    char setTwo[20];
    sprintf(card, "%li", l);

    for (int i = 0; i < length(l); i++)
    {
        // digits that weren’t multiplied by 2
        if (temp1 > 0 && temp >= 0)
        {
            setTwo[i] = card[--temp1];
            --temp1;
            long longTwo = atoll(&setTwo[i]);
            setTwoSum = setTwoSum + longTwo;
        }
        // second-to-last digits, multiply each digits by 2 add those products’ digits (i.e., not the products themselves) together.
        if (temp > 0 && temp1 >= 0)
        {
            --temp;
            setOne[i] = card[--temp];
            long longOne = atoll(&setOne[i]);
            longOne = longOne * 2;

            if (length(longOne) == 2)
            {
                long k = 1;
                for (int j = 10; j < 19; j++)
                {
                    if (longOne == j)
                    {
                        longOne = k;
                    }
                    k++;
                }
            }
            setOneSum = setOneSum + longOne;
        }
    }
    ans = (setOneSum + setTwoSum) % 10; // calculate if modulo of Total sum is 0 or nah
    return ans;
}


// just a length function
int length(long l)
{
    char card[256];
    sprintf(card, "%li", l);
    int length = strlen(card);

    return length;
}