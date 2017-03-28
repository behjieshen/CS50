import cs50
import sys

def main():
    if len(sys.argv) != 2:
        print("Usage: python caesar number")
        exit(1)
        
    k = int(sys.argv[1])
    print("plaintext:  ", end = "")
    string = cs50.get_string()
    count = k/26
    if k <= 26:
        count = 1
        
    if input != None:
        print("ciphertext: ", end = "")
        for i in range(len(string)):
            if str.isalpha(string[i]):
                letter = ord(string[i])
                if letter + k > 122:
                    while(True):
                        letter = letter + k - (26 * count)
                        if letter > 122:
                            letter = 96 + (letter - 122)
                        if letter <= 122:
                            break
                
                elif letter + k > 90 and letter < 96:
                    while(True):
                        letter = letter + k - (26 * count)
                        if letter > 90:
                            letter = 64 + (letter - 90)
                        if letter <= 90:
                            break
                            
                else:
                    letter += k
                
                letter = chr(letter)
                print(letter, end = "")
            else:
                print(string[i], end = "")
        print()
        exit(0)
        
if __name__ == "__main__":
    main()