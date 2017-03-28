// a program that prompts the user for the length of his 
// or her shower in minutes (as a positive integer) and 
// then prints the equivalent number of bottles of water

// include necessary header files
#include <stdio.h>
#include <cs50.h>

// main function
int main(void)
{
    // prompt the user for the minutes that they take for shower
    printf("minutes: ");
    // record the input into min
    int min = GetInt();
    // multiply the inputted data by 12
    min *= 12;
    // print the result
    printf("bottles: %i\n", min);
}