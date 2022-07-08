from cs50 import get_string

text = get_string("Insert the text: ")
letters = 0
words = 1
sentences = 0

# Looping char by char in text string
for string in text:
    # Uppercase each char and check if it is a letter
    if string.upper() >= 'A' and string.upper() <= 'Z':
        letters += 1
    # Look for spaces to detect words (words begin in one to include first word)
    elif string == " ":
        words += 1
    # Look for sentences by reconizing period, question mark or exclamation mark
    elif string == "!" or string == "?" or string == ".":
        sentences += 1

# Average of letter in 100 words
L = 100 / words * letters

# Average of sentences in 100 words
S = 100 / words * sentences

# Coleman-Liau index
index = round(0.0588 * L - 0.296 * S - 15.8)

if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print("Grade ", index)