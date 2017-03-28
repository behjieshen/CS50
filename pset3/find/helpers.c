/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
 

// include necessary header files
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

/** 
// binary search function
bool search(int value, int values[], int n)
{
    // declaration/initialization of variables
    int low = 0;
    int high = n - 1;
    
    // while there is still something to search at
    while(low <= high)
    {
        // find mid
        int mid = low + (high-low)/2;
        // if the middle is the value, return true
        if(value == values[mid])
            return true;
        // else if the value is in the left part
        else if(value < values[mid])
            // search the left part
            high = mid - 1;
        // else if the value is in the right part
        else
            // search the right part
            low = mid + 1;
    }
    // return false if the loop does not return true
    return false;
}
**/

/**
 * Returns true if value is in array of n values, else false.
 */
 
// recursion binary search function
bool search(int values[], int low, int high, int value)
{
    // if there is nothing else to search, return false
    if(low < high == false)
        return false;
    // find mid
    int mid = (low + high) / 2;
    // if the middle is the value, return true
    if(values[mid] == value)
        return true;
    // else if value is in the left part
    else if(value < values[mid])
        // call the function with the values of the left part
        return search(values[], low, mid - 1, value);
    // else if the value is in the right part
    else
        // call the function with the values of the right part
        return search(values[], mid + 1, high, value);
}

/**
 * Sorts array of n values.
 */
 
// selection sort function
void sort(int values[], int n)
{
    // iterate through everything
    for(int i = 0; i < n - 1; i++)
    {
        // assign the i-th element as the smallest
        int smallest = values[i];
        // declaration of variables
        int tempIndex;
        int tempNumber;
        // iterate from the i-th element
        for(int j = i + 1; j < n; j++)
        {
            // if the i-th value is smaller, assign the number as smallest
            if(values[j] < smallest)
            {
                tempIndex = j;
                tempNumber = smallest;
                smallest = values[j];
                values[tempIndex] = tempNumber;
            }
        }
        // put smallest in the index of the current i-th element 
        values[i] = smallest;
    }
    return;
}