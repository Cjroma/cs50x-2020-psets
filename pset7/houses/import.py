from cs50 import SQL
from sys import argv, exit
import csv
import re


if len(argv) != 2:
    print("Usage: python import.py data.csv")
    exit(1)

db = SQL("sqlite:///students.db")

try:
    # Open CSV file
    with open(argv[1], 'r') as file:
        reader = csv.DictReader(file)
        for row in reader:
            # Split name in first middle and last
            name = re.split(r"\s", row['name'])
            # Execute if name has middlename
            if len(name) == 3:
                db.execute('INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?);',
                           name[0], name[1], name[2], row['house'], row['birth'])
            # Execute if no middle name
            else:
                db.execute('INSERT INTO students (first, middle, last, house, birth) VALUES (?, ?, ?, ?, ?);',
                           name[0], None, name[1], row['house'], row['birth'])
except IOError:
    # Print if could not open file
    print("Could not open", argv[1])
    exit(1)