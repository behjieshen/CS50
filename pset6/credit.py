import cs50

def main():
    counter = 0
    track = 1
    total = 0
    amex = False
    mastercard = False
    visa = False
    
    print("Number: ", end="")
    ori_number = cs50.get_int()
    number = ori_number
    string_number = str(number)
    counter = len(string_number)
        
    if counter == 13 or counter == 15 or counter == 16:
        array = []
        for i in range(counter):
            tmp = int(number % 10)
            array.append(tmp)
            number /= 10

        if ((array[counter-1] == 3 and array[counter-2 == 4]) or 
        (array[counter-1] == 3 and array[counter-2] == 7)) and counter == 15:
            amex = True;
        
        elif(array[counter-1] == 5 and counter == 16) and (array[counter-2] == 1 or 
        array[counter-2] == 2 or array[counter-2] == 3 or array[counter-2] == 4 or
        array[counter-2] == 5):
            mastercard = True
            
        elif array[counter-1] == 4 and (counter == 16 or counter == 13):
            visa = True
            
        else:
            print("INVALID")
            exit(1)
        
        for j in range(1,counter,2):
            array[j] *= 2
            
        for k in range(counter):
            if array[k] > 10:
                remaining = int(array[k] % 10) 
                array.append(int(array[k] / 10))
                array[k] = remaining
            elif array[k] == 10:
                array[k] = 1
            
        for m in range(len(array)):
            total += array[m]

        print(total)
        
        if total % 10 == 0:
            if amex:
                print("AMEX")
            elif mastercard:
                print("MASTERCARD")
            elif visa:
                print("VISA")
        else:
            print("INVALID")
    else:
        print("INVALID")
    exit(0)
    
if __name__ == "__main__":
    main()
        