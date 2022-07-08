from cs50 import get_string

# Ask the user the card number and print invalid if it isn't a number between 13 and 16 digits
card = get_string("Type your card number: ")
if len(card) < 13 or len(card) > 16:
    print("INVALID")
    

def luhnsAlgorithm(card):
    y = ""
    # Invert the card number order
    card = card[::-1]
    # Loop to multiply digits occording to Luhn's Algorithm
    for i in card[1::2]:
        i = int(i)
        i = i * 2
        y = y + str(i)
    x = 0
    # Convert string to int and sum digits
    for i in y:
        i = int(i)
        x += i
    y = ""
    # Sum digits not multiplied according to Luhn's Algorithm
    for i in card[::2]:
        y = y + i
    # Convert string to int and sum digits
    for i in y:
        i = int(i)
        x += i
    # Divide by 10 until only one digit left to check if the last digit in that sum is a 0
    while x > 0:
        x /= 10
    # If the last digit is 0 return True (valid card according Lunh's Algorithm)
    if x == 0:
        return True
    # Return false if card number isn't valid
    else:
        return False


isValid = luhnsAlgorithm(card)
# If the card is valid check for the card brand
if isValid == True:
    # American Express check: 15 digits
    if len(card) == 15:
        print("AMEX")
    # Mastercard check: 16 digits and first two digits are 51, 52, 53, 54 or 54
    elif len(card) == 16 and (card[0] == '5'):
        if int(card[1]) > 0 and int(card[1]) < 6:
            print("MASTERCARD")
    # Visa check: 13 or 16 digits and first digit is 4
    elif (len(card) == 13 or len(card) == 16) and card[0] == '4':
        print("VISA")