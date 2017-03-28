import cs50
import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: vigenere string")
        exit(1)
        
    k = str(sys.argv[1])
        
    for i in range(len(sys.argv[1])):
        if str.isalpha(sys.argv[1][i]) == False:
            print("Letters only!")
            exit(1)
            
    print("plaintext  : ", end = "")
    user_input = cs50.get_string()
    print("ciphertext : ", end = "")

    j = -1;
    
    for i in range(len(user_input)):
        if j+1 == len(k):
            j = 0
        else:
            j+=1
        
        if str.isalpha(user_input[i]) == False:
            j -= 1

        if str.isalpha(user_input[i]):
            if str.islower(user_input[i]):
                if k[j].isupper():
                    c = ord(user_input[i]) + ord(k[j].lower()) - 97
                else:
                    c = ord(user_input[i]) + ord(k[j]) - 97
                while c > 122:
                    diff = c - 122
                    c = 96 + diff
                    
            elif str.isupper(user_input[i]):
                if k[j].islower():
                    c = ord(user_input[i]) + ord(k[j].upper()) - 65
                else:
                    c = ord(user_input[i]) + ord(k[j]) - 65
                while c > 90:
                    diff = c - 90
                    c = 64 + diff
            
            c = chr(c)
        
        else:
            c = user_input[i]
        print(c, end="")
        
    print()
    exit(0)
    
main()