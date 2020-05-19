from sys import argv, exit
import csv
import re
import cs50


def main():
    # Check if user entered required files
    if len(argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)
    try:
        # Open DNA sequence
        textFile = open(argv[2], 'r')
    except IOError:
        # Print and Exit if couldn't open file
        print(rf"Could not open {argv[2]}")
        exit(1)
    try:
        # Open DNA Database
        csvFile = open(argv[1], 'r')
    except IOError:
        # Print and Exit if couldn't open file
        print(rf"Could not open {argv[1]}")
        exit(1)

    # Store DNA sequence to a variable
    dnaSequence = textFile.read()

    # Will store STR squence from dna sequence file
    STRs = []
    # Read csv file and put quote to each data
    reader = csv.reader(csvFile, quoting=csv.QUOTE_ALL)
    # Reapeat until end row is reach
    for row in reader:
        matchedSTR = 0
        # Run if current row is first line of csv
        if row[0] == "name":
            # Store CSV first row to head
            head = row
            # Compute the longest run of consecutive repeats of the STR in the DNA sequence
            for i in range(len(row)-1):
                pattern = re.compile(rf'({head[i+1]})+')
                matches = pattern.finditer(dnaSequence)
                for match in matches:
                    seq = int((match.end() - match.start()) / len(head[i+1]))
                    if seq > 4:
                        STRs.append(seq)
                    elif len(head) == 4:
                        STRs.append(seq)
        else:
            # Search if STR in DNA sequence is in DNA database
            for i in range(len(row)-1):
                if int(STRs[i]) == int(row[i+1]):
                    matchedSTR += 1
            # Print people that matched DNA from database
            if matchedSTR == len(row)-1:
                print(row[0])
                exit(0)
    # Print No match
    print("No match")
    # Close text file
    textFile.close()
    # Close csv file
    csvFile.close()


main()
