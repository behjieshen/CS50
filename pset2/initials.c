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
    // assign the first letter as the first element
    initialized[0] = stringGiven[0];
    // keep track of the array's elements
    int keepTrackOfArray = 1;
    
    // loop and assign the suitable words to the array
    for(int i = 0; i < strlen(stringGiven); i++)
    {
        // if it is a space
        if(isspace(stringGiven[i]))
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