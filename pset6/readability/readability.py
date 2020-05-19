from cs50 import get_string
import re


def main():
    # Promt user for text
    text = get_string("Text: ")
    letter = 0
    word = 1
    sentence = 0

    # Scan every character from text
    for c in text:
        # Count letter(s) from text
        if re.match("[a-zA-Z]", c):
            letter += 1
        # Count word(s) from text
        elif c == " ":
            word += 1
        # Count sentence(s) from text
        elif re.match("[.!?]", c):
            sentence += 1

    # Compute avg letter(s) per 100 words
    L = round((letter/word) * 100, 2)
    # Compute avg sentence(s) per 100 words
    S = round((sentence/word) * 100, 2)
    # Compute Coleman-Liau index
    index = round(0.0588 * L - 0.296 * S - 15.8)

    # If index is less than 1
    if index < 1:
        print("Before Grade 1")
    # If index is 16 or greater
    elif index >= 16:
        print("Grade 16+")
    # If not of the above
    else:
        print(f"Grade {index}")


main()
