import names
import random

with open("names.txt", "w") as file:
    for i in range(100):
        file.write(f"{names.get_full_name()} {random.randint(1, 100)} {random.randint(1, 10)}\n")

