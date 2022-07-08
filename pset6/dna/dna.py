import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("ERROR! Correct usage: python dna.py FILE.CSV FILE.TXT")

    # Read database file into a variable
    people = []
    with open(sys.argv[1]) as csvFile:
        # Check if the file is empty and close the program
        if csvFile == None:
            sys.exit("ERROR! Database file is empty.")
        reader = csv.DictReader(csvFile)
        # Creates a dict with people and DNA data
        for rows in reader:
            people.append(rows)

    # Read DNA sequence file into a variable
    with open(sys.argv[2]) as f:
        # Check if the file is empty and close the program
        if f == None:
            sys.exit("ERROR! Sequence file is empty")
        # Create a variable 'sequences' to receive the DNA sequence
        sequence = f.read()

    # Find longest match of each STR in DNA sequence
    with open(sys.argv[1]) as f:
        # Read row by row using ',' as delimiter
        csvReader = csv.reader(f, delimiter=',')
        subsequences = []
        # Pick up just the first and break the loop
        for row in csvReader:
            subsequences.append(row)
            break
    # Creat a new list with the STR subsequences we are looking for
    for row in subsequences:
        subsequences = row[1::]
    # lenght receives the size equals the amount of STR's we are searching
    lenght = len(subsequences)
    individual = []

    # number receives how many times each STR is found in sequence using longest_match() function
    # individual is a list to receive all STR's searched
    for x in range(lenght):
        number = longest_match(sequence, subsequences[x])
        individual.append(number)

    # Check database for matching profiles
    # x representes the index
    x = 0
    # person receives the person's name and the times each STR are repeated
    person = []
    # count verify if the STR we seek match with the individual STR for every STR envolved
    count = 0

    # Look for each row in people dict
    for row in people:
        # Append to person list the name of the person in current row
        person.append(row["name"])
        # Pick up each STR name for each person
        # And append this STR value to the person list
        # Now person list has the person name and all STR's values for this person
        for i in range(lenght):
            sub = subsequences[x]
            x += 1
            person.append(row[sub])

        # Compare all STR's for each person with the STR found in longest_match()
        # If the person's STR are equal to the STR we need to search print person's name and close the program
        for i in range(lenght):
            if (person[i+1]) == str((individual[i])):
                count += 1
                if count == lenght:
                    sys.exit(person[0])

        # Reset variables to a new person
        count = 0
        person = []
        x = 0
    # If after the loope we don't find the person, print "No match" and close the file
    sys.exit("No match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
