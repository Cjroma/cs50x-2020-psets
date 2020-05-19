#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

void cipherMe(string key);

// Start and end of uppercase letter as integer
const int upStart = 65, upEnd = 90;

// Start and end of lowercase letter as integer
const int lowStart = 97, lowEnd = 122;

int main(int argc, string argv[])
{

    // Check if key is present in command-line
    if (argc == 2)
    {

        string key = argv[1];

        // Get the length of cipher key
        int length = strlen(key);

        bool isLetter = true;

        // Check if key length is valid
        if (length == 26)
        {
            // Check if key only contain alphabetic characters
            for (int i = 0; i < length; ++i)
            {
                if (!isLetter)
                {
                    break;
                }
                else if ((key[i] >= upStart && key[i] <= upEnd)  || (key[i] >= lowStart && key[i] <= lowEnd))
                {
                    isLetter = true;

                    // Check for repeated letter in key (case-insensitive)
                    for (int j = 0; j < length; ++j)
                    {
                        if (toupper(key[i]) == toupper(key[j]) && i != j)
                        {
                            printf("Key must not contain repeated characters.\n");
                            return 1;
                        }
                    }
                }
                else
                {
                    isLetter = false;
                    printf("Key must only contain alphabetic characters.\n");
                    return 1;
                }
            }
            cipherMe(key);
            return 0;
        }
        else
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
}

// Cipher the plaintext
void cipherMe(string key)
{
    // Get plaintext from user
    string plainText = get_string("Plaintext: ");

    // Length of plaintext
    int pLength = strlen(plainText);

    // Will store ciphered text
    char cipherText[pLength];

    for (int i = 0; i < pLength; i++)
    {
        // Substitute the letter to equivalent cipher letter then convert to uppercase
        if (plainText[i] >= upStart && plainText[i] <= upEnd)
        {
            cipherText[i] = toupper(key[plainText[i] - upStart]);
        }
        // Substitute the letter to equivalent cipher letter then convert to lowercase
        else if (plainText[i] >= lowStart && plainText[i] <= lowEnd)
        {
            cipherText[i] = tolower(key[plainText[i] - lowStart]);
        }
        // None letters
        else
        {
            cipherText[i] =  plainText[i];
        }
    }
    cipherText[pLength] = '\0';
    printf("ciphertext: %s\n", cipherText);
}
