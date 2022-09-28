# TODO
# input loop
while True:
    # except invalid answer
    try:
        name = int(input("Height: "))
        if name > 0 and name < 9:
            break
    except ValueError:
        # print error
        print("Error")

# range
for i in range(name):
    print(" "*(name-1-i), end="")
    print("#"*(i+1))

