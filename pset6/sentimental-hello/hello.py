# Import get_string function from cs50 library
from cs50 import get_string

# Ask the user name and print "Hello" + user name
name = get_string("What is your name?\n")
print("Hello, " + name)