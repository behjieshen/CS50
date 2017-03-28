# a program that a program that first asks the user how much change is owed and then 
# spits out the minimum number of coins with which said change can be made.

# import cs50 module
import cs50

# main function
def main():
    # declaration of variables
    penny = 1
    nickel = 5
    dime = 10
    quarter = 25
    count = 0
    p = 0
    n = 0
    d = 0
    q = 0
    
    # prompt user for float
    while(True):
        print("Money owed: ", end="")
        ask = cs50.get_float()
        if(ask > 0):
            break
    
    # change float into integer form
    owed = int(ask * 100)
    
    # calculate amount of quarters 
    while(owed >= quarter):
        owed -= quarter
        q+=1
    
    # calculate amount of dimes
    while(owed >= dime):
        owed -= dime
        d+=1
        
    # calculate amount of nickels
    while(owed >= nickel):
        owed -= nickel
        n+=1
    
    # calculate amount of pennies
    while(owed >= penny):
        owed -= penny
        p+=1
    
    """
    For Extended Feature
    print("Quarters : {}".format(q))
    print("Nickels : {}".format(n))
    print("Dimes : {}".format(d))
    print("Pennies : {}".format(p))
    """
    
    # calculate total number of coins
    count = p + d + n + q
    # print the number of coins
    print(count)
    # send an exit code of 0
    exit(0)

# run main function
if __name__ == "__main__":
    main()