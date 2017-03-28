// a program that recreates this full-pyramid using hashes (#) for blocks

// include necessary header files
#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

// declaration of variable
int height;

// a function to prompt user input
string user_input()
{
    // print description of program
    printf("This program generates full-pyramid for you.\n");
    // ask for height of the half pyramid
    printf("Height : ");
    // store the value into height
    height = GetInt();
    // make sure that it is a positive integer that is lesser than 23
    if(height < 0 || height > 23)
    {
        // prompt user input again
        printf("Sorry, your number is too big or too small.\n");
        user_input();
    }
    return 0;
}

// main function
int main(void) 
{
    // prompt user input
    user_input();
    // generate full pyramid
    for(int a = 0; a < height; a++) 
    {
        for(int b = 0; b < height-a-1; b++)
        {
            printf(" ");
        }
        for(int c = 0; c < a+1; c++)
        {
            printf("#");
        }
        printf("  ");
        for(int d = 0; d < a+1; d++)
        {
            printf("#");
        }
        
        printf("\n");
    }
    return 0;
}
