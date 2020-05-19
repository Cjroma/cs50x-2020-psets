#include <stdio.h>
#include <cs50.h>

int main(void)
{
    string name = get_string("What's your name?\n"); // Get user input and store it in string variable name.
    printf("Hello, %s\n", name); 
}