// a program that first asks the user how much change is owed and then 
// spits out the minimum number of coins with which said change can be made.

// include necessary header files
#include <stdio.h>
#include <cs50.h>
#include <math.h>

// initialization of variables
float ask;
float penny = 1;
float nickel = 5;
float dime = 10;
float quarter = 25;
int p = 0;
int n = 0;
int d = 0;
int q = 0;
int count;

// main function
int main(void) {
    // make sure that user input a float
    do {
        printf("Money owed: $");
        ask = GetFloat();
    }while(ask < 0);
    
    // make it in the form of cents
    float owed = roundf(ask * 100);
    
    // calculate quarters
    while(owed >= quarter) {
        owed -= quarter;
        q++;
    }
    
    // calculate dimes
    while(owed >= dime) {
        owed -= dime;
        d++;
    }
    
    // calculate nickels
    while(owed >= nickel) {
        owed -= nickel;
        n++;
    }
    
    // calculate pennies
    while(owed >= penny) {
        owed -= penny;
        p++;
    }
    
    // For extended feature
    /**
    printf("Quarters: %i\n", q);
    printf("Nickels: %i\n", n);
    printf("Dimes: %i\n", d);
    printf("Pennies: %i\n", p);
    **/
    
    // add all of them together
    count = p + d + n + q;
    
    //print the number of coins
    printf("%i\n", count);
    
    return 0;
}
