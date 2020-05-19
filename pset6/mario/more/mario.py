from cs50 import get_int


def main():
    # Repeat until user enter positive number not greater than 8
    while True:
        height = get_int("Height: ")
        if height >= 1 and height <= 8:
            break
    # Call fuction pyramid
    pyramid(height, 0)

# Print Pyramid


def pyramid(h, s):
    if h != 0:
        # Hard to explain
        pyramid(h-1, s+1)
        # Print blocks
        print(" " * s + "#" * h + "  " + "#" * h)


main()

