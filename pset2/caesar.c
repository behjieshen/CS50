// a program that ciphers the given text by the number specified

// include necessary header files
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// main function
int main(int argc, string argv[])
{
    // exit if the second argument is null
    if(argv[1] == NULL || argc != 2) {
        printf("Usage: caesar number\n");
        return 1;
    }
    // declare variable
    char letter;
    // change second argument into an integer
    int k = atoi(argv[1]);
    // store string into input
    string input = GetString();
    // 
    int count = k/26;
    
    if(k <= 26)
    {
        count = 1;
    }
    
    // input does not equal to null
    if(input != NULL)
    {
        // iterate through the length of input
        for(int i = 0; i < strlen(input); i++)
        {
            // if it is a letter
            if(isalpha(input[i]))
            {
                // store the letter in ASCII form
                letter = (int)input[i];
                
                // if it exceeds "z"
                if(letter + k > 122) {
                    do {
                        letter = letter + k -(26 * count); 
                        if(letter > 122)
                            letter = 96 +(letter - 122);
                    } while(letter > 122);
                }
                // if it exceeds "Z"
                else if(letter + k > 90 && letter < 96) {
                    do {
                        letter = letter + k -(26 * count);
                        if(letter > 90)
                            letter = 64 +(letter - 90);
                    } while(letter > 90);
                }
                // else add the number with the letter
                else
                    letter += k;
                // change letter into character form
                letter = (char) letter;
                // print letter
                printf("%c", letter);
            }
            // print if it is not a letter
            else
                printf("%c", input[i]);
        }
        //print a new line
        printf("\n");
        return 0;
    }
}