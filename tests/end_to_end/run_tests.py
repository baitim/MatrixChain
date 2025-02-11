import os
import glob
import subprocess
from pathlib import Path

proj_dir = str(Path(__file__).parent)
curr_dir = str(Path.cwd())
print(curr_dir)
print(proj_dir)

def run(answer_dir, exe_file):
    os.system("mkdir -p " + answer_dir)
    file_name = answer_dir + "/answer_" + f'{test_num+1:03}' + ".ans"
    os.system("touch " + file_name)
    os.system("echo -n > " + file_name)
    ans_file = open(file_name, 'w')
    command = exe_file + " < " + file
    ans_file.write(subprocess.check_output(command, shell=True).decode("utf-8"))
    ans_file.close()

matrix_chain_exe = curr_dir + "/../../src/matrix_chain"
answer_dir = proj_dir + "/answers"
tests_dir  = proj_dir + "/tests_in"

test_num = 0
files = list(map(str, glob.glob(tests_dir + "/test_*.in")))
files.sort()

for file in files :
    run(answer_dir, matrix_chain_exe)
    test_num += 1
    print("test",  test_num, "passed")