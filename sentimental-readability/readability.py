# TODO

from cs50 import get_string

string = get_string("Text: ")
# def
letter = 0
word = 0
sentence = 0
# check letters
for c in string:
    if c == '\n':
        exit()
    if c.lower().isalpha() == True:
        letter += 1
    if c == " ":
        word += 1
    if c == "." or c == "!" or c == "?":
        sentence += 1
# calculate Coleman-Liau index
word += 1
L = (letter/word)*100
S = (sentence/word)*100

grade = round(0.0588 * L - 0.296 * S - 15.8)

# print result
if grade >= 16:
    print("Grade 16+")
elif grade < 1:
    print("Before Grade 1")
else:
    print("Grade", grade)