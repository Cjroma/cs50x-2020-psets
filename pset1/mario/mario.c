#include <stdio.h>
#include <cs50.h>


void Pyramid(int i);

int main(void)
{
    bool badInput = true;
    do
    {
        int height = get_int("Height: "); // Obtain user input

        if (height >= 1 && height <= 8) // check if height is not less than 1 or not greater than 8
        {
            for (int i = 0; i < height; i++)
            {
                for (int k = height; k > i + 1; k--)
                {
                    printf(" ");
                }
                Pyramid(i);
                printf("  ");
                Pyramid(i);
                printf("\n");
            }
            badInput = false; // if height is not less than 1 or not greater than 8
        }
        else
        {
            badInput = true; // if height is less than 1 or greater than 8
        }
    }
    while (badInput);
}

void Pyramid(int i) // Fuction that print pyramid
{
    for (int j = 0; j < i + 1; j++)
    {
        printf("#");
    }
}