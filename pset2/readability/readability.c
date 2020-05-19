#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

int main(void)
{
    // Promt user for text
    string text = get_string("Text: ");
    float letter = 0;
    float word = 1;
    float sentence = 0;
    int index = 0;

    for (int i = 0, length = strlen(text); i < length; ++i)
    {
        // Count how many letter(s) in text
        if ((text[i] >= 65 && text[i] <= 90) || (text[i] >= 97 && text[i] <= 122))
        {
            ++letter;
        }
        // Count how many word(s) in text
        if (text[i] == 32)
        {
            ++word;
        }
        // Count how many sentence(s) in text
        if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            ++sentence;
        }
    }

    // Average letter(s) per 100 words
    letter = (letter / word) * 100;

    // Average sentence(s) per 100 words
    sentence = (sentence / word) * 100;

    // Compute Coleman-Liau index
    index = round((0.0588 * letter) - (0.296 * sentence) - 15.8);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}