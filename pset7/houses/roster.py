from cs50 import SQL
from sys import argv, exit
import csv
import re

# Check if user enterd required argument
if len(argv) != 2:
    print("Usage: python roster.py house")
    exit(1)

db = SQL("sqlite:///students.db")

# Get data from students database and store it to data
data = db.execute('SELECT * FROM students WHERE house = ? ORDER BY last;', argv[1])

if data == []:
    print(f"House of {argv[1]} does not exist.")
    exit(1)

for row in data:
    # If student has middle name
    if row['middle'] is None:
        name = row['first'] + " " + row['last']
        print(f"{name}, born {row['birth']}")
        continue
    # If student has no middle name
    name = row['first'] + " " + row['middle'] + " " + row['last']
    print(f"{name}, born {row['birth']}")
