import random
import os
from pathlib import Path

compare_dir = str(Path(__file__).parent)
compare_in_dir = compare_dir + "/compare_in"
os.system("mkdir -p " + compare_in_dir)

count_tests = 10
for test_num in range(count_tests) :
    file_name = compare_in_dir + "/test_" + f'{test_num+1:03}' + ".in"
    print(file_name)
    file = open(file_name, 'w')

    count = 300
    size  = [1, 25]

    file.write(str(count) + "\n")

    for j in range(count) :
        file.write(str(random.randint(size[0], size[1])) + " ")

    file.write("\n")

    file.close()
    print("test ", test_num + 1, " generated")
