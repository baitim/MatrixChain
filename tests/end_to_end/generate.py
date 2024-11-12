import random
import os

to_curr_dir = os.path.dirname(os.path.realpath(__file__))

count_tests = 10

for test_num in range(count_tests) :
    file_name = to_curr_dir + "/tests_in/test_" + f'{test_num+1:03}' + ".in"
    file = open(file_name, 'w')

    count = random.randint(7, 10)
    size  = [5, 20]

    test_str = str(count) + " " + "\n"

    for j in range(count) :
        test_str += str(random.randint(size[0], size[1])) + " "

    file.write(test_str)

    file.close()
    print("test ", test_num + 1, " generated")
