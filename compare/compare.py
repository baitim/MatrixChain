import os
import glob
import subprocess
import matplotlib.pyplot as plt
from pathlib import Path

curr_dir = str(Path.cwd())
cmp_matrix_chain_exe = curr_dir + "/../build/Release/compare/cmp_matrix_chain"

files = list(map(str, glob.glob("compare_in/test_*.in")))
files.sort()

name_out_file = "compare.out"
os.system("touch " + name_out_file)
os.system("echo -n > " + name_out_file)
out_file = open(name_out_file, 'w')
out_file.write("file\t\t\t\t\tratio\n")

test_num = 0
ratios = []
counts = []
for file in files :
    command = cmp_matrix_chain_exe + " < " + file
    result = subprocess.check_output(command, shell=True).decode("utf-8").strip()
    count_str, ratio_str = result.split()
    count = int(count_str)
    ratio = float(ratio_str)

    time_str = file + "\t" + f'{ratio:<7}' + "\n"

    out_file.write(time_str)

    counts.append(count)
    ratios.append(ratio)
    test_num += 1
    print("test",  test_num, "passed")

out_file.close()

combined = list(zip(counts, ratios))
sorted_combined = sorted(combined)
sorted_x, sorted_y = zip(*sorted_combined)
sorted_x = list(sorted_x)
sorted_y = list(sorted_y)


plt.plot(sorted_x, sorted_y, marker='o', label='naive/fast')
plt.title("Ratios")

plt.xlabel('count')
plt.ylabel('ratio')

plt.legend()
plt.savefig("ratios.png")