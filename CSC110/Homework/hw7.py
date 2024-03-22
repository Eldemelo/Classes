# Ethan DeMelo | 6 November, 2023
# Homework 7

# Variation of Caesar Cipher function to allow upper-case letters and spaces in plaintext to encrypt
# Using a random number generator and a seed value

# Import libraries
import random

# Function to create a caesar cipher
def caesarRandom(plaintext, seedIn):
    alphabet=['a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z']
    # Create empty cyperText string for processing
    ciphertext = ""
    # Initialize seed and generate a random number with given seed
    random.seed(seedIn)
    # Converts text for use in encryption
    plaintext = plaintext.lower()
    plaintext = plaintext.replace(" ", "")
    for i in range(len(plaintext)):
        # get the ith letter from the plaintext
        letter = plaintext[i] 
        num = random.randint(0, (len(alphabet)-1))
        # find the number position of the ith letter
        num_in_alphabet = alphabet.index(letter) 
        # find the number position of the cipher by adding the shift 
        cipher_num = (num_in_alphabet + num) % len(alphabet) 
        # find the cipher letter for the cipher number you computed
        cipher_letter = alphabet[cipher_num] 
        # add the cipher letter to the ciphertext
        ciphertext += cipher_letter
    return ciphertext

def unCaesarRandom(cipherText, seedIn):
    # List of alphabet letters for reference during decryption
    alphabet = ['a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z']
    plaintext = ""
    # Generate random seed using parameter seedIn
    random.seed(seedIn)
    # For each letter in the cipherText, decrypt the value and append to a plaintext string
    for i in range(len(cipherText)):
        letter = cipherText[i]
        num = random.randint(0, (len(alphabet)-1))
        num_in_alphabet = alphabet.index(letter)
        plain_num = (num_in_alphabet -num) % len(alphabet)
        plain_letter = alphabet[plain_num]
        plaintext += plain_letter
    return plaintext

# Analysis
# This algorithm is better than the caesar cypher and the polyalphabetic cyper
# Because it randomizes each letter based on a seed. This encryption algoirth could be broken
# by creating code with a random number seed using the same seed and checking for a shift in the letters
# through manual processing