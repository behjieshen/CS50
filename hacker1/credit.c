// a program that checks if the credit number is Amex, Visa or MasterCard

// include necessary header files
#include <cs50.h>
#include <stdio.h>
#include <math.h>

// define and initialize variables
int counter = 0;
int track = 1;
int sum = 0;
bool amex = false;
bool mastercard = false;
bool visa = false;

// main function
int main()
{
    // ask user's input
    printf("Number: ");
    long long ori_number = GetLongLong();
    long long number = ori_number;
    long long checknumber = number;
    
    // while there is input, calculate the number of numbers that is given
    while(checknumber > 0)
    {
        checknumber /= 10;
        counter += 1;
    }
    
    // if the amount of numbers is 13(VISA) / 15(American Express) / 16(MasterCard/Visa) 
    if(counter == 13 || counter == 15 || counter == 16)
    {
        // 1.Create an array to store the number
        int array[counter * 2];
        for(int i = 0; i < counter; i++)
        {
            array[i] = number%10;
            number /= 10;
        }
        
        // 2. if the number count is 15 and the number start with 34/37, it is most likely an AMEX
        if(((array[counter-1] == 3 && array[counter-2] == 4) || (array[counter-1] == 3 && array[counter-2] == 7)) && counter == 15)
            amex = true;
        
        // 2. if the number is count is 16 and the number starts with 51/52/53/54/55, it is most likely a MasterCard
        else if((array[counter-1] == 5 && counter == 16) && ((array[counter-2] == 1) || (array[counter-2] == 2) || 
        (array[counter-2] == 3) || (array[counter-2] == 4) || (array[counter-2] == 5)))
            mastercard = true;
            
        // 2. if the number count is 13 and the number starts with a 4, it is most likely a Visa
        else if(array[counter-1] == 4 && ((counter == 16) || (counter == 13)))
            visa = true;
        
        // 2. else, the number given is not a credit card
        else {
            printf("INVALID");
            return 0;
        }
        
        // 3. Every 2nd number * 2
        for(int j = 1; j < counter; j+=2)
            array[j] *= 2;
        
        // 4. split to single digits for every non 1-digit number
        for(int k = 0; k < counter; k++)
        {
            if(array[k] > 10)
            {
                int remaining = array[k] % 10;
                array[counter + track] = remaining;
                track += 1;
                array[k] /= 10;
            }
            else if(array[k] == 10)
                array[k] = 1;
        }
        
        for(int m = 0; m < counter+track; m++)
            sum += array[m];
        
        // 5. check the company that created the credit card
        if(sum % 10 == 0)
        {
            if(amex == true)
                printf("AMEX");
            else if(mastercard == true)
                printf("MASTERCARD");
            else if(visa == true)
                printf("VISA");
        }
        else {
            printf("INVALID");
        }
    }
    else
        printf("INVALID");
        
    printf("\n");
    return 0;
}