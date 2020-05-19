#include <cs50.h>
#include <stdio.h>

int main()
{
    int index[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}};
    printf("%i",index[1][1]);
}