import random
from pathlib import Path

tests_dir = str(Path(__file__).parent)

count_tests = 10

for test_num in range(count_tests) :
    file_name = tests_dir + "/tests_in/test_" + f'{test_num+1:03}' + ".in"
    file = open(file_name, 'w')

    count = random.randint(7, 10)
    size  = [5, 20]

    file.write(str(count) + "\n")

    for j in range(count) :
        file.write(str(random.randint(size[0], size[1])) + " ")

    file.close()
    print("test ", test_num + 1, " generated")
