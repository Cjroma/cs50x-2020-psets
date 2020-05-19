from cs50 import get_int
import re


def main():
    # Prompt user for card number
    number = get_int("Number: ")
    # Call luhn algorithm fuction, execute if card is valid
    if luhnAlgorithm(number) == 0:

        # Convert card number to string
        cardAsStr = str(number)

        # Check if card is MASTERCARD
        if re.search("^(51|52|53|54|55).*", cardAsStr) and len(cardAsStr) == 16:
            print("MASTERCARD")
        # Check if card is VISA
        elif re.search("^4.*", cardAsStr) and len(cardAsStr) == 16:
            print("VISA")
        # Check if card is AMEX
        elif re.search("^(34|37).*", cardAsStr) and len(cardAsStr) == 15:
            print("AMEX")
        # If not any of the above print INVALID
        else:
            print("INVALID")
    # If not valid card
    else:
        print("INVALID")

# Calculate card number and determine if valid or not


def luhnAlgorithm(n):
    setOne = 0
    s = 0
    setTwo = 0
    temp = n

    # Add not multiplied number
    while temp != 0:
        setOne += int(temp % 10)
        temp /= 100
    # Add multiplied number
    while n != 0:
        n /= 10
        if int(n % 10) >= 5:
            i = str(int((n % 10)) * 2)
            setTwo += int(i[0]) + int(i[1])
        else:
            setTwo += int((n % 10)) * 2
        n /= 10
    return (setOne + setTwo) % 10


main()
