import csv
import sys

dna = list()

result = {
    'AGATC': 0,
    'TTTTTTCT': 0,
    'AATG': 0,
    'TCTAG': 0,
    'GATA': 0,
    'TATC': 0,
    'GAAA': 0,
    'TCTG': 0
}


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("ERROR!")
        sys.exit(1)

    # TODO: Read database file into a variable
    with open(sys.argv[1], 'r') as database:
        reader = csv.DictReader(database)
        # next(reader)
        # reader.readrow(['name'])
        for row in reader:
            dna.append(row)
            # print(dna[0][1])

    # AGATC = row['AGATC']
    # TTTTTTCT = row['TTTTTTCT']
    # AATG = row['AATG']
    # TCTAG = row['TCTAG']
    # GATA = row['GATA']
    # TATC = row['TATC']
    # GAAA = row['GAAA']
    # TCTG = row['TCTG']

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], 'r') as sequence:
        seqreader = csv.reader(sequence)
        seq = ' '.join(str(e) for e in seqreader)
        # print(seqreader)
        # seq = seqreader
        # print(seq)
        for i in result:
            result[i] += longest_match(seq, i)

    # TODO: Find longest match of each STR in DNA sequence

    # for row in reader:
    #     # data = row
    #     print(longest_match(seqreader, data))
    # TODO: Check database for matching profiles
    # print(dna)
    # print(len(dna))
    # for i in range(1, len(dna)+1):
    #     print(result.values(i))
    #     print(dna.values(i))
    # for item in result.values():
    #     if item == 'AGATC':
    # print(f"result: {result['AGATC']}")
    # print(f"dna: {dna[1]['AGATC']}")
    # print(dna[0])
    # print(list(dna[0].keys())[3])
    for a in result:
        result[a] = str(result[a])
    # print(result)
    # print(dna)
    # checklist = list()
    # for i in range(1, len(dna[0])):
    #     checklist.append(result[list(dna[0].keys())[i]])
    #     print(checklist)

    # for j in range(1, len(dna)+1):
    # print(dna[13])
    # print(f"{dict((list(dna[13].items())[1:])).items()}, {result.items()}")

    # print(f"{dict((list(dna[13].items())[1:])).items()}, {result.items()}")
    # print(dict((list(dna[13].items())[1:])).items() <= result.items())

    for row in range(0, len(dna)):
        if dict((list(dna[row].items())[1:])).items() <= result.items():
            print(dna[row]['name'])
            sys.exit(0)
    # print(dna[row]['name'])
    print("No match")

    # print(f"mã DNA đang check: {list(dna[0].keys())[1]}, {list(dna[0].keys())[2]}, {list(dna[0].keys())[3]}")
    # print(f"kết quả của mã DNA đang check: {result[list(dna[0].keys())[1]]}, {result[list(dna[0].keys())[2]]}, {result[list(dna[0].keys())[3]]}")
    # print(f"tên người đang check: {dna[0][list(dna[0].keys())[0]]}, {dna[1][list(dna[0].keys())[0]]}, {dna[2][list(dna[0].keys())[0]]}")
    # print(f"mã DNA của người đang check: {dna[1][list(dna[0].keys())[1]]}, {dna[1][list(dna[0].keys())[2]]}, {dna[1][list(dna[0].keys())[3]]}")

    # for row in dna:
    #     for j in range(1, len(dna[0])):
    #         if int(dna[row][list(dna[0].keys())[j]]) != int(result[list(dna[0].keys())[j]]):
    #             break
    #     print(dna[row]['name'])
    # for i in dna[][1]
    # for i in dna:
    # for i in dna[1]
    #     if int(result[dna[0][1]]) == int(dna[i][1]):
    #         print(i)
    #         print(i)
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
