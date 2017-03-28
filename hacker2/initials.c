// a program that return only the capitalized words

// include necessary headers
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

// main function
int main(void) 
{
    // store the string
    string stringGiven = GetString();
    // initialize an array with the length of the string
    char initialized[strlen(stringGiven)];
    // keep track of the array's elements
    int keepTrackOfArray = 0;
    // if the first char is a letter, set the array's 1st element as the first char of the string                                   
    if(isalpha(stringGiven[0]))
    {
        initialized[0] = stringGiven[0];
        keepTrackOfArray += 1;
    }
    // loop and assign the suitable words to the array
    for(int i = 0; i < strlen(stringGiven); i++)
    {
        // if it is only 1 space apart
        if(isspace(stringGiven[i]) && isalpha(stringGiven[i+1]))
        {
            // assign the next letter as an element of the array
            initialized[keepTrackOfArray] = stringGiven[i+1];
            keepTrackOfArray += 1;
        }
    }
    // loop to capitalize the letters in the array
    for(int i = 0; i < keepTrackOfArray; i++)
    {
        printf("%c", toupper(initialized[i]));
    }
    printf("\n");
    
    return 0;
}