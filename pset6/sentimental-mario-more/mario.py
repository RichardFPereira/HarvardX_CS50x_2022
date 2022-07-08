from cs50 import get_int

# Get user height and if it's not a numb between 1 and 8 ask again
while True:
    height = get_int("Enter the pyramid's height (number between 1 and 8 inclusive): ")
    if height > 0 and height < 9:
        break

count = 1

# Loop to print the pyramid
for x in range(height):

    # Print left side spaces
    for y in range(height - count):
        print(" ", end="")

    # Print left side hashes
    for y in range(count):
        print("#", end="")

    # Print middle spaces
    print("  ", end="")

    # Print right hashes
    for y in range(count):
        print("#", end="")
        
    # New line and count increment
    print(end="\n")
    count += 1