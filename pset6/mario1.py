# a reimplementation of mario.c in python

# import cs50 module
import cs50

# main function
def main():
    # a do-while loop(sort-of)
    while(True):
        # prompt for user input
        print("Height: ", end = "")
        # save user input in height
        height = cs50.get_int()
        # if it is a positive integer that is lesser than 24, break out of loop
        if(height > 0 and height < 24):
            break
    
    # generate full-pyramid
    for i in range(height):
        for j in range(height-i-1):
            print(" ", end = "")
        for k in range(i+1):
            print("#", end = "")
        print("  ",end = "")
        for l in range(i+1):
            print("#", end = "")
        print()
    
    # return exit code of 0
    exit(0)

# run main function
if __name__ == "__main__":
    main()
    